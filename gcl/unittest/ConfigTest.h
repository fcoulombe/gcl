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

#include <gcl/UnitTest.h>
#include <gcl/Config.h>

using namespace GCL;
namespace ConfigTest
{
void Test();
void Test()
{
	TEST_START
	Config &tempConfig = Config::Instance();
    Assert_Test(tempConfig.GetInt("DEFAULT_VIEWPORT_HEIGHT")==480);
    Assert_Test(tempConfig.GetInt("DEFAULT_VIEWPORT_WIDTH")==640);

	const std::string &tempString =tempConfig.GetString("TEST_STRING"); 
	Assert_Test(tempString=="TestString");
	const std::string &tempString2 =tempConfig.GetString("TEST_BROKEN_STRING"); 
	Assert_Test(tempString2=="Test String");
}
}
