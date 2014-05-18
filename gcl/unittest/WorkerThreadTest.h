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

#include <sstream>

#include <gcl/UnitTest.h>

#include <gcl/WorkerThread.h>
#include <gcl/ThreadManager.h>

using namespace GCL;
namespace WorkerThreadTest
{
void Test();
void Test()
{
	TEST_START
	std::stringstream s;

	{
		WorkerThread thread("TestWorkerThread");
		bool testAsync = false;
		bool testSync = false;
		thread.SendCommandAsync([&]() { testAsync = true; });
		thread.SendCommandSync([&]() {testSync = true; });
		Assert_Test(testAsync);
		Assert_Test(testSync);
	}
	{
		try
		{
			WorkerThread thread("TestWorkerThread");
			thread.SendCommandAsync([]() {GCLAssert(false);});

			while (true)
			{
				ThreadManager::ReThrowException();
				Thread::YieldThread();
			}
		}
		catch(...)
		{
			ThreadManager::ClearException();
		}
	}
	{
		WorkerThread thread("TestWorkerThread");
		size_t count =0;
		for (size_t i=0; i<100; ++i)
			thread.SendCommandAsync([&]() { count++; });
		thread.Flush();
		Assert_Test(count == 100);
	}
	{
		WorkerThread thread("TestWorkerThread");
		size_t count =0;
		for (size_t i=0; i<100; ++i)
			thread.SendCommandAsync([&]() { count++; });
		thread.SendCommandSync([&]() { });
		Assert_Test(count == 100);
	}
	{
		WorkerThread thread("TestWorkerThread");
		size_t count =0;
		for (size_t i=0; i<100; ++i)
			thread.SendCommandSync([&]() { count++; });
		thread.SendCommandSync([&]() { });
		Assert_Test(count == 100);
	}
}
}
