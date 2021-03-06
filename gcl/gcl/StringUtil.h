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
#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <vector>

//============================================================================

namespace GCL
{
  //============================================================================

  class StringUtil
  {
  public:
    static void Explode(const std::string& str,
      std::vector<std::string> &ret,
      const char ch);
    // trim from end
    static inline std::string &TrimEnd(std::string &s)
    {
      s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
      return s;
    }
    // trim from start
    static inline std::string &TrimFront(std::string &s)
    {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
      return s;
    }
    // trim from both ends
    static inline std::string &Trim(std::string &s)
    {
      return TrimFront(TrimEnd(s));
    }


    template<typename... Args>
    static std::string FormatText(const std::string &fmt, Args&&... args)
    {
      return FormatText(fmt.c_str(), std::forward<Args>(args)...);
    }
    template<typename... Args>
    static std::string FormatText(const char * const fmt, Args&&... args)
    {
      const int BUFFER_SIZE = 4096;
      std::vector<char> buff(BUFFER_SIZE + 1);
#ifdef OS_WIN32
      int l = _snprintf(&buff[0], BUFFER_SIZE, fmt, std::forward<Args>(args)...);
#else
      int l = snprintf(&buff[0], BUFFER_SIZE, fmt, std::forward<Args>(args)...);
#endif
      int len = std::min(l, BUFFER_SIZE);
      std::string buffer(buff.begin(), buff.begin() + len);
      buffer[len] = '\0';
      return buffer;
    }

    static std::string FormatText(const char * const fmt)
    {
      const int BUFFER_SIZE = 4096;
      std::vector<char> buff(BUFFER_SIZE + 1);
#ifdef OS_WIN32
      int l = _snprintf(&buff[0], BUFFER_SIZE, "%s", fmt);
#else
      int l = snprintf(&buff[0], BUFFER_SIZE, "%s", fmt);
#endif
      int len = std::min(l, BUFFER_SIZE);
      std::string buffer(buff.begin(), buff.begin() + len);
      buffer[len] = '\0';
      return buffer;
    }
  };
  //============================================================================
} // namespace GCL
//============================================================================
