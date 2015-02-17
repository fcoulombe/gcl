/*
 * Copyright (C) 2014 by Francois Coulombe
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
#include <3rdparty/spdlog.h>
#include <gcl/StringUtil.h>

namespace GCL
{
class KLogger
{
public:
    KLogger()
{
        mConsole = spdlog::stdout_logger_mt("kinevox");
}
    std::shared_ptr<spdlog::logger> operator()()
    {
        return mConsole;
    }
private:
    std::shared_ptr<spdlog::logger> mConsole;

};
}
extern GCL::KLogger g_Klogger;
#define KLog(...)\
        do{\
            KLogI(__VA_ARGS__);\
        }while(false)\

#define KLogW(...)\
        do{\
            g_Klogger()->warn(StringUtil::FormatText(__VA_ARGS__));\
        }while(false)\

#define KLogV(...)\
        do{\
            g_Klogger()->trace(StringUtil::FormatText(__VA_ARGS__));\
        }while(false)\

#define KLogD(...)\
        do{\
            g_Klogger()->debug(StringUtil::FormatText(__VA_ARGS__));\
        }while(false)\

#define KLogE(...)\
        do{\
            g_Klogger()->error(StringUtil::FormatText(__VA_ARGS__));\
        }while(false)\

#define KLogF(...)\
        do{\
            g_Klogger()->critical(StringUtil::FormatText(__VA_ARGS__));\
        }while(false)\

#define KLogI(...)\
        do{\
            g_Klogger()->info(StringUtil::FormatText(__VA_ARGS__));\
        }while(false)\


