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
#include "gcl/ThreadManager.h"

#include <future>

using namespace GCL;

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
				std::unique_lock<std::mutex> lock(mMutex);
				while(mKeepProcessing &&  !mCommandQueue.try_dequeue(cmd) )
					mRunMutex.wait(lock);
			}

#endif
			if(cmd)
				cmd();
		}
		mWorkFinished = true;
	}
	catch (GCLException& e)
	{
		(void)e;
		mWorkFinished = true;
		ThreadManager::Throw(std::current_exception());
	}
	catch (std::exception& )
	{
		mWorkFinished = true;
		ThreadManager::Throw(std::current_exception());
	}
	catch (...)
	{
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
		cmd();
		completionPromise.set_value();});
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

