/*
* Copyright (C) 2013 by Francois Coulombe
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:

* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.

* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include "gcl/WorkerThread.h"
#include "gcl/Exception.h"
#include "gcl/Log.h"
#include "gcl/ThreadManager.h"

#include <future>

using namespace GCL;
#define ENABLE_THREAD_LOGGING 0
#if ENABLE_THREAD_LOGGING
#define WTLog(...) KLogD(__VA_ARGS__)
#else
#define WTLog(...)
#endif
WorkerThread::WorkerThread(const std::string& name)
	: mName(name)
	, mKeepProcessing(true)
	, mWorkFinished(false)
{
	mThread = std::thread(&WorkerThread::Update, this);
}

WorkerThread::~WorkerThread()
{
	if (mWorkFinished)
	{
		if (mThread.joinable())
			mThread.join();
		return;
	}
	Flush();
	mKeepProcessing = false;
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mRunMutex.notify_one();
	}

	if (mThread.joinable())
		mThread.join();
}

void WorkerThread::Update()
{
	//SetThreadName(_name.c_str());

	try
	{
		while(mKeepProcessing)
		{
			Command cmd;
#if USE_WINDOWS_QUEUE
			if(mKeepProcessing && !mCommandQueue.try_pop(cmd) )
			{
				std::unique_lock<std::mutex> lock(mMutex);
				while(mKeepProcessing &&  !mCommandQueue.try_pop(cmd) )
					mRunMutex.wait(lock);
			}
#else
			if(mKeepProcessing && !mCommandQueue.try_dequeue(cmd) )
			{

				WTLog("Couldn't dequeue");
				std::unique_lock<std::mutex> lock(mMutex);
				while(mKeepProcessing &&  !mCommandQueue.try_dequeue(cmd) )
				{
					WTLog("still waiting");
					mRunMutex.wait(lock);
				}
			}

#endif
			if(cmd)
			{
				static size_t k = 0;
				k++;
				WTLog("Executing command: %d", (int)k);
				cmd();
				WTLog("Finished Executing command");
			}
		}
		mWorkFinished = true;
	}
	catch (GCLException& e)
	{
		KLogE("The worker thread: %s has hit an exception: %s", mName.c_str(), e.what());
		(void)e;
		mWorkFinished = true;
		ThreadManager::Throw(std::current_exception());
	}
	catch (std::exception& )
	{
		KLogE("The worker thread: %s has hit an exception", mName.c_str());
		mWorkFinished = true;
		ThreadManager::Throw(std::current_exception());
	}
	catch (...)
	{
		KLogE("The worker thread: %s has hit an exception", mName.c_str());
		mWorkFinished = true;
		ThreadManager::Throw(std::current_exception());
	}

}


void WorkerThread::SendCommandAsync(Command& cmd)
{
#if USE_WINDOWS_QUEUE
	mCommandQueue.push(cmd);
#else
	mCommandQueue.enqueue(cmd);
#endif
	{
		std::lock_guard<std::mutex> lock(mMutex);
		mRunMutex.notify_one();
	}
}

void WorkerThread::SendCommandAsync(const Command& cmd)
{
#if USE_WINDOWS_QUEUE
	mCommandQueue.push(cmd);
#else
	mCommandQueue.enqueue(cmd);
#endif

	{
		std::lock_guard<std::mutex> lock(mMutex);
		mRunMutex.notify_one();
	}
}

void WorkerThread::SendCommandSync(const Command& cmd)
{
	std::promise<void> completionPromise;
	std::future<void> completionFuture = completionPromise.get_future();
#if USE_WINDOWS_QUEUE
	mCommandQueue.push([&](){
		cmd(); 
		completionPromise.set_value();});
#else
	mCommandQueue.enqueue([&](){
		//We need to pass the ownership of promise to this scope since there's a chance
		//for the promise to run out of scope before the end of set_value which causes a deadlock
		std::promise<void> localCompletionPromise = std::move(completionPromise);
		cmd();
		localCompletionPromise.set_value();});
#endif
		{
			std::lock_guard<std::mutex> lock(mMutex);
			mRunMutex.notify_one();
		}

	completionFuture.wait();
}

void WorkerThread::Flush()
{
	SendCommandSync([](){});
}

