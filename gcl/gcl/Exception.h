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

#pragma once

#include <string>
#include <exception>
#include <thread>

//============================================================================

namespace GCL
{
//============================================================================

class GCLException : public std::exception
{
public:
	/*GCLException(const std::string &message = "no reason")
    { Initialize(message, "undefined", 0); }*/


	GCLException(const std::string &message=  "no reason", const std::string &file = std::string(), int line = 0, std::thread::id threadId = std::this_thread::get_id())
	{ Initialize(message, file, line, threadId); }

	virtual ~GCLException() throw() {}
	virtual const char *what() const throw()
    {
		static std::string ret;
		ret = std::string("\n")+ mFileInfo+mMessage+mStackTrace;
		return ret.c_str();
    }

	const char *message() const { return mMessage.c_str(); }
	const char *stacktrace() const { return mStackTrace.c_str(); }

	static const std::string Demangle(const char *symbol);
private:
	//copy string argument to ensure the string data to be cleared by the stack unwinding
	void Initialize(const std::string &message, const std::string &file, int line, std::thread::id threadId );
	std::string mFileInfo;
	std::string mMessage;
	std::string mStackTrace;
};

//============================================================================
} // namespace GCL
//============================================================================
