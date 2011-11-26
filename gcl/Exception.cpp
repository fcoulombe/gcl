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

//============================================================================

using namespace GCL;
//#include <iostream>
//============================================================================
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
      stackStream << strings[i];
      stackStream << std::endl;
    }
  mStackTrace = stackStream.str();
  free (strings);
}

//============================================================================
