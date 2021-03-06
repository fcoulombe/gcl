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
#include <vector>
#include <iostream>
#include "gcl/Exception.h"

namespace GCL
{

//global data to all unit tests of an executable
struct UnitTestConfig
{
	UnitTestConfig()
	: mIsInteractive(false)
	{}
	bool mIsInteractive;
}gTestConfig;

size_t sNumTestFailures=0;
class TestCounter
{
public:
	struct Failure
	{
		Failure(const char *cond, const char *file, size_t line, const char *function, const char *msg)
		{
			mCond = cond;
			mFile = file;
			mLine = line;
			mFunction = function;
			mMsg = (msg);
		}
		const char *mCond;
		const char *mFile;
		size_t mLine;
		const char *mFunction;
		std::string mMsg;
	private:
	};
	TestCounter(const char *file)
	{
		mFileName = file;
		std::cout.precision(10);
	}

	virtual ~TestCounter()
	{
		if (failedTest.size())
		{
			for (size_t i=0; i<failedTest.size(); ++i)
			{
#ifndef OS_WIN32
				std::cerr << failedTest[i].mFile << ":" << failedTest[i].mLine << ": error: Test Has Failed for "<< failedTest[i].mCond;
#else
				std::cerr << failedTest[i].mFile << "(" << failedTest[i].mLine << "): error: Test Has Failed for "<< failedTest[i].mCond;
#endif
				if (failedTest[i].mMsg.length())
					std::cerr << " Msg: " << failedTest[i].mMsg;
				std::cerr << std::endl;
				sNumTestFailures++;
			}
			std::cout << "[FAILED] " << mFileName  << std::endl;
		}
		else
		{
			std::cout << "[PASSED] " << mFileName  << std::endl;
		}
		std::cout.flush();
		std::cerr.flush();
		failedTest.clear();
	}
	std::string mFileName;
	std::vector<Failure> failedTest;
};


/*
GCLINLINE void iAssert_Test(TestCounter testCounter, bool hasFailed, const char *message, const char *file, size_t line, const char *fucntion)
{
	if (hasFailed)
		testCounter.failedTest.push_back(Failure(message, file, line, fucntion));
}*/

}

#define TEST_START TestCounter testCounter(__FILE__);
#define Assert_Test(x) if (!(x)) {   testCounter.failedTest.push_back(TestCounter::Failure(#x, __FILE__, __LINE__, __FUNCTION__, "")); }
#define AssertMsg_Test(x, msg) if (!(x)) { testCounter.failedTest.push_back(TestCounter::Failure(#x, __FILE__, __LINE__, __FUNCTION__, msg)); }

#include "gcl/PixelBuffer.h"
namespace GCL
{
namespace UnitTest
{
bool ImageComp(const char *filename)
{
	std::string otherFileName = TEXTURE_PATH"/comp/";
	otherFileName += filename;
	PixelBuffer original(otherFileName);
	PixelBuffer output(filename);
	return (original == output);
}
}
}

inline void ParseArguments(int argc, char **argv)
{
	  if (argc>1)
	  {
		  if (strcmp(argv[1], "--interactive")==0)
		  {
			  GCL::gTestConfig.mIsInteractive = true;
		  }
	  }
}

#define SUITE_INIT(argc, argv) \
	ParseArguments(argc, argv);\
	try {\
		\

#define SUITE_TERMINATE \
		}\
		catch (GCLException & e)\
		{\
			std::stringstream str;\
			str << "[FAILED] " << argv[0] << std::endl;\
			str << e.what();\
			std::cerr << str.str();\
            std::cout.flush();\
std::cerr.flush();\
			return -1;\
		}\
		catch (std::exception &e)\
		{\
			std::cerr << "[FAILED] " << e.what() << std::endl;\
            std::cout.flush();\
            std::cerr.flush();\
			return -1;\
		}\
		catch (...)\
		{\
			std::cerr << "[FAILED] not sure what happened" << std::endl;\
            std::cout.flush();\
            std::cerr.flush();\
            return -1;\
		}\
		\


