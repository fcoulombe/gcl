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

#include <gcl/Thread.h>
#include <gcl/ThreadManager.h>

using namespace GCL;
namespace ThreadTest
{
class TestThread : public Thread
{
	void Run()
	{

	}
};
//test if we can catch an exception
class ExceptionThread : public Thread
{
	void Run()
	{
		GCLAssert(false);
	}
};

class ExpectionPropagateThread : public Thread
{
	void Run()
	{
		while (rand() % 1000 != 59) //randomly assert
		{
		}

		GCLAssert(false);
	}
};
void Test();
void Test()
{
	TEST_START
	std::stringstream s;

	{
		TestThread thread;
		thread.Start();

		thread.Join();
	}
	{
		try
		{
			ExceptionThread thread;
			thread.Start();

			while (true)
			{
				ThreadManager::ReThrowException();
				Thread::YieldThread();
			}
		}
		catch(...)
		{

		}
	}
	{
		//try
		{
			ExpectionPropagateThread threads[50];
			for (size_t i=0; i<50; ++i)
				threads[i].Start();

			while (true)
			{
				ThreadManager::ReThrowException();
				Thread::YieldThread();
			}
		}
		//catch(...)
		{

		}
	}
}
}
