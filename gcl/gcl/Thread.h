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

#pragma once

#include <thread>
#include <gcl/Exception.h>
namespace GCL
{
	class GCLException;
/*	class ThreadManager
	{

		ThreadManager()
		{

		}
		static ThreadManager &Instance() 
		{
			static ThreadManager instance;
			return instance;
		}
		void RegisterThread(Thread *t)
		{
			mThreadMap.insert(std::pair(t->GetThreadId(), t));
		}
		void UnRegisterThread(Thread *t)
		{
			mThreadMap.erase(t->GetThreadId());
		}
		void Join(std::thread::id threadId)
		{
			mThreadMap[threadId]->Join();
		}
	private:
		std::map<std::thread::id, Thread *> mThreadMap;
	};*/
	class Thread
	{
	public:
		Thread()
			: mIsRunning(false)
		{
			//ThreadManager::Instance().RegisterThread(this);
		}
		virtual ~Thread()
		{
			if (mThread.joinable())
				mThread.join();
			//ThreadManager::Instance().UnRegisterThread(this);
		}
		void Start()
		{
			mThread = std::thread(ThreadHelper, std::ref(*this));
		}
		std::thread::id GetThreadId() const { return mThread.get_id(); }
		void Join()
		{
			mThread.join();
		}

		virtual void Run()=0;

		static void YieldThread()
		{
			std::this_thread::yield();
		}
		static void ReThrowException()
		{
			if( FatalExceptionTransfer!=nullptr )
			{
				std::rethrow_exception(FatalExceptionTransfer);
			}
		}

	private:
		std::thread mThread;
		volatile bool mIsRunning;
		static std::exception_ptr FatalExceptionTransfer; //used to catch exception
		static void ThreadHelper( Thread &myThread)
		{
			myThread.mIsRunning = true;
			try
			{
				myThread.Run();
			}
			catch (GCLException& )
			{
				FatalExceptionTransfer = std::current_exception();
			}
			catch (std::exception& )
			{
				FatalExceptionTransfer = std::current_exception();
			}
			catch (...)
			{
				FatalExceptionTransfer = std::current_exception();
			}
			myThread.mIsRunning = false;
		}
	};


}
