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
//============================================================================

#include "gcl/StringUtil.h"
#include "gcl/Assert.h"
//============================================================================

using namespace GCL;

//============================================================================

void StringUtil::Explode(const std::string& str, std::vector<std::string> &ret, const char ch)
{
	std::string next = "";
	std::vector<std::string> &result = ret;
	GCLAssertMsg(str.length(), "you are trying to explode an empty string");

	for (std::string::const_iterator it = str.begin(); it != str.end(); ++it)
	{
		if (*it == ch || *it == 0)
		{
			if (next.length() > 0)
			{
				result.push_back(next);
				next = "";
			}
		}
		else
		{
			//std::cout << *it << std::endl;
			next += *it;
		}
	}
	result.push_back(next);

}
//============================================================================
