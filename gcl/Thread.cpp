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
//============================================================================

#include "gcl/Thread.h"
#include "gcl/ThreadManager.h"

//============================================================================

using namespace GCL;

//============================================================================

GCL::Thread::Thread() : mIsRunning(true)
{
	ThreadManager::RegisterThread(this);
}

GCL::Thread::~Thread()
{
	if (mThread.joinable())
		mThread.join();
	ThreadManager::UnRegisterThread(this);
}

void GCL::Thread::Start()
{
	mThread = std::thread(ThreadHelper, std::ref(*this));
}

void GCL::Thread::Join()
{
	mThread.join();
}

void GCL::Thread::Kill()
{
	mIsRunning = false;
}

void GCL::Thread::YieldThread()
{
	std::this_thread::yield();
	ThreadManager::ReThrowException();
}

void GCL::Thread::ThreadHelper( Thread &myThread )
{
	try
	{
		myThread.Run();
	}
	catch (GCLException& e)
	{
		(void)e;
		ThreadManager::Throw(std::current_exception());
	}
	catch (std::exception& )
	{
		ThreadManager::Throw(std::current_exception());
	}
	catch (...)
	{
		ThreadManager::Throw(std::current_exception());
	}
	myThread.mIsRunning = false;
}
