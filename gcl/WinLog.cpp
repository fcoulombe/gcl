/*
 * Copyright (C) 2012 by Erin Houston
 * Copyright (C) 2012 by Francois Coulombe
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
#if defined(OS_WIN32) && !defined(__GNUC__)
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <windows.h>

namespace GCL
{
    template <class CharT, class TraitsT = std::char_traits<CharT> >
    class DebugStringBuf : public std::basic_stringbuf<CharT, TraitsT>
    {
    public:
        virtual ~DebugStringBuf()
        {
            sync();
        }

    private:
        virtual int sync()
        {
            write(str().c_str());
            str(std::basic_string<CharT>());
            return 0;
        }

        void write(const CharT *text) {}

        static void DebugStringbufOutput(const char* text) {     ::OutputDebugStringA(text); }
        static void DebugStringbufOutputw(const wchar_t* text) { ::OutputDebugStringW(text); }
    };


    template<> void DebugStringBuf<char>::write(const char *text) { DebugStringbufOutput(text); }
    template<> void DebugStringBuf<wchar_t>::write(const wchar_t *text) { DebugStringbufOutputw(text); }

    template<class CharT, class TraitsT = std::char_traits<CharT> >
    class DebugOstream : public std::basic_ostream<CharT, TraitsT>
    {
    public:

        DebugOstream()
            : std::basic_ostream<CharT, TraitsT>(new DebugStringBuf<CharT, TraitsT>())
        {
        }

        ~DebugOstream() 
        {
            delete rdbuf(); 
        }
    };

    typedef DebugOstream<char> DOStream;
    typedef DebugOstream<wchar_t> WDOStream;

    class GCLLog
    {
    public:
        GCLLog()
        {
            std::cout << "GCLLOG" << std::endl;
            mBackCout = std::cout.rdbuf();
            mBackCerr = std::cerr.rdbuf();
            BOOL is = ::IsDebuggerPresent();
            if (is)
            {
                std::cout.rdbuf(mRedirectStream.rdbuf());
                std::cerr.rdbuf(mRedirectStream.rdbuf());
            }
            else
            {
                //BOOL ret =
                 AttachConsole(ATTACH_PARENT_PROCESS);
                //assert(ret != 0);
                //ULONG_PTR p = GetParentProcessId(); 
            }
        }
        ~GCLLog()
        {
            std::cout.rdbuf(mBackCout);
            std::cerr.rdbuf(mBackCerr);
        }
        DOStream mRedirectStream;
        std::streambuf *mBackCout;
        std::streambuf *mBackCerr;
    };

    static GCLLog sRedirectLog;
}

#endif