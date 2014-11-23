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
#include <gcl/StringUtil.h>

using namespace GCL;
namespace StringUtilTest
{
void Test();
void Test()
{
	TEST_START

    // Trim Test
    std::string testTrimFront("\t \n\rTestString\t");
    Assert_Test(StringUtil::TrimFront(testTrimFront) == "TestString\t");
    std::string testTrimEnd("\tTestString\r\t \n");
    Assert_Test(StringUtil::TrimEnd(testTrimEnd) == "\tTestString");
    std::string testTrim("\r\t \nTestString\r\t \n");
    Assert_Test(StringUtil::Trim(testTrim) == "TestString");
    // Explode Test
	std::string explodeTest = "some string to explode";
	const std::string explodedTest[] = { std::string("some"),
										std::string("string"),
										std::string("to"),
										std::string("explode")};
	std::vector<std::string> res;
	StringUtil::Explode(explodeTest, res, ' ');

	std::stringstream s;
	s<<res.size()<<" == 4";
	AssertMsg_Test(res.size()==4, s.str().c_str());
	for (size_t i=0; i<res.size();++i)
	{
		std::stringstream s2;
		s2<<res[i] << std::endl << "==" << std::endl << explodedTest[i];

		AssertMsg_Test(res[i] ==  explodedTest[i], s2.str().c_str());
	}
}
}
