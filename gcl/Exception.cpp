/*
 * Copyright (C) 2011 by Jeffrey Lim
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

#include "gcl/Exception.h"
#include <execinfo.h>
#include <sstream>
#include <cstring>

#include <cxxabi.h>
//============================================================================

using namespace GCL;
//#include <iostream>
//============================================================================


const std::string GCLException::Demangle(const char *i_symbol)
{
	std::string retStr;
	size_t sz = 200; // just a guess, template names will go much wider
	char *function = static_cast<char *>(malloc(sz));
	sprintf(function, "%s", i_symbol);
	char *begin = 0, *end = 0;
	// find the parentheses and address offset surrounding the mangled name
	for (char *j = function; *j; ++j)
	{
		if (*j == '(')
		{
			begin = j;
		}
		else if (*j == '+')
		{
			end = j;
		}
	}
	if (begin && end)
	{
		begin++;
		//*begin++ = '';
		*end = 0;
		// found our mangled name, now in [begin, end)

		int status;
		char *ret = abi::__cxa_demangle(begin, function, &sz, &status);
		if (ret)
		{
			// return value may be a realloc() of the input
			function = ret;
		}
		else
		{
			// demangling failed, just pretend it's a C function with no args
			//strncpy(function, begin, sz);
			//strncat(function, "()", sz);
			function[sz-1] = ' ';
		}
		retStr = i_symbol;
		retStr += ":";
		retStr += function;
	}
	else
	{
		// didn't find the mangled name, just print the whole line
		retStr = i_symbol;
	}
	free(function);
	return retStr;

}

void GCLException::Initialize(const std::string &message, const std::string &file, int line )
{
	char **strings;
	size_t i;
	static const size_t STACK_SIZE = 100;
	void *array[STACK_SIZE];
	size_t size;

	size = backtrace (array, STACK_SIZE);
	strings = backtrace_symbols (array, size);


	if (file.length())
	{
		std::stringstream trace;
		//std::cout << std::endl << "file: " << file << ":" << line << std::endl;
		trace << file;
		trace << ":";
		trace << line << ": ";
		mFileInfo = trace.str();
	}
	std::stringstream messageStream;

	//printf ("Obtained %zd stack frames.\n", size);
	if (message.length())
	{
		messageStream << message;
	}

	mMessage = messageStream.str();

	std::stringstream stackStream;
	stackStream << std::endl;
	for (i = 0; i < size; i++)
	{
		stackStream << Demangle(strings[i]);
		stackStream << std::endl;
	}
	mStackTrace = stackStream.str();
	free(strings);
}

//============================================================================
