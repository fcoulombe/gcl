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

#include <sstream>
#include <gcl/UnitTest.h>
#include <gcl/Path.h>

using namespace GCL;
namespace PathTest
{
void Test();
void Test()
{
	TEST_START
	std::stringstream s;

	//path to first slash test
	{
		const std::string path ="/Users/francoiscoulombe/src/kinevox/build/clang-i386-64bit/lib/renderer/unittest/renderer_test";
		const std::string dirNameOfPath ="/Users/francoiscoulombe/src/kinevox/build/clang-i386-64bit/lib/renderer/unittest";
		std::string dirName = Path::PathToFirstSlash(path);
		s.str("");
		s<<dirName<<std::endl<<" == "<<std::endl << dirNameOfPath ;
		AssertMsg_Test(dirName==dirNameOfPath, s.str().c_str());
	}

	//path from first slash test
	{
		const std::string path ="/Users/francoiscoulombe/src/kinevox/build/clang-i386-64bit/lib/renderer/unittest/renderer_test";
		const std::string dirNameOfPath ="renderer_test";
		std::string dirName = Path::PathFromFirstSlash(path);
		std::stringstream s;
		s.str("");
		s<<dirName<<std::endl<<" == "<<std::endl << dirNameOfPath ;
		AssertMsg_Test(dirName==dirNameOfPath, s.str().c_str());
	}

	//get CWD test
	{
		const std::string cwd = Path::Cwd();
		s.str("");
		s<<Path::PathFromFirstSlash(cwd)<<std::endl<<" == "<<std::endl << "unittest" ;
		AssertMsg_Test(Path::PathFromFirstSlash(cwd)=="unittest", s.str().c_str());
	}


	//get application path test
	{
		const std::string applicationPath = Path::GetApplicationPath();
#ifdef OS_WIN32
		const std::string applicationNAme = "gcl_test.exe";
#else
		const std::string applicationNAme = "gcl_test";
#endif
		s.str("");
		s<<Path::PathFromFirstSlash(applicationPath)<<std::endl<<" == "<<std::endl << applicationNAme ;
		AssertMsg_Test(Path::PathFromFirstSlash(applicationPath)==applicationNAme, s.str().c_str());
	}

	//file extension test
	{
		const char *dummyPath = "/bleh/blah/blig/somefile.tga";
		const std::string ext = Path::GetFileNameExtension(dummyPath);
		AssertMsg_Test(ext == "tga", ext.c_str());

		const char *dummyPath2 = "/bleh/blah/blig/somefile";
		const std::string ext2 = Path::GetFileNameExtension(dummyPath2);
		AssertMsg_Test(ext2 == "", ext2.c_str());
	}
}
}
