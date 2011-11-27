/*
 * Copyright (C) 2011 by Francois Coulombe
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

#include <gcl/UnitTest.h>
#include <gcl/Exception.h>

using namespace GCL;
namespace ExceptionTest
{


void ExceptionTestFunction2()
{
	throw GCLException();
}
void ExceptionTestFunction1()
{
	ExceptionTestFunction2();
}
void ExceptionTestFunction3()
{
	throw GCLException("Message Exception");
}

void Test()
{
	TEST_START
	try
	{
		ExceptionTestFunction1();
		Assert_Test(false); //should never hit this
	}
	catch (GCLException &e)
	{
		Assert_Test(strncmp("",e.message(), strlen(""))==0);
#ifdef OS_MACOSX
		AssertMsg_Test(strncmp("\n0   gcl_test",e.stacktrace(), strlen("\n0   gcl_test"))==0, e.stacktrace());
#endif
	}
	try
	{
		ExceptionTestFunction3();
	}
	catch (GCLException &e)
	{
		const char *testString = "Message Exception";
		Assert_Test(strncmp(testString,e.message(), strlen(testString))==0);
	}
	catch (...)
	{
		Assert_Test(false);
		std::cerr << "an exception went in" << std::endl;
	}
}
}
