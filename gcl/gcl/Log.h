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

#ifdef OS_ANDROID
#	include <android/log.h>
#	define KLog(...) KLogI(__VA_ARGS__)

#	define KLogW(...)\
	((void)__android_log_print(ANDROID_LOG_WARN, "kinevox", "Warning: " __VA_ARGS__))

#	define KLogV(...)\
	((void)__android_log_print(ANDROID_LOG_VERBOSE, "kinevox","Verbose: "  __VA_ARGS__))

#	define KLogD(...)\
	((void)__android_log_print(ANDROID_LOG_DEBUG, "kinevox", "Debug: " __VA_ARGS__))

#	define KLogE(...)\
	((void)__android_log_print(ANDROID_LOG_ERROR, "kinevox", "Error: " __VA_ARGS__))

#	define KLogF(...)\
	((void)__android_log_print(ANDROID_LOG_FATAL, "kinevox", "Fatal: " __VA_ARGS__))

#	define KLogI(...)\
	((void)__android_log_print(ANDROID_LOG_INFO, "kinevox", "Info: " __VA_ARGS__))


#else
#	define KLog(...)\
	do{\
	KLogI(__VA_ARGS__);\
	}while(false)\

#	define KLogW(...)\
	do{\
	printf("Warning: ");\
	printf(__VA_ARGS__);\
	printf("\n");\
	}while(false)\

#	define KLogV(...)\
	do{\
	printf("Verbose: ");\
	printf(__VA_ARGS__);\
	printf("\n");\
	}while(false)\

#	define KLogD(...)\
	do{\
	printf("Debug: ");\
	printf(__VA_ARGS__);\
	printf("\n");\
	}while(false)\

#	define KLogE(...)\
	do{\
	printf("Error: ");\
	printf(__VA_ARGS__);\
	printf("\n");\
	}while(false)\

#	define KLogF(...)\
	do{\
	printf("Fatal: ");\
	printf(__VA_ARGS__);\
	printf("\n");\
	}while(false)\

#	define KLogI(...)\
	do{\
	printf("Info: ");\
	printf(__VA_ARGS__);\
	printf("\n");\
	}while(false)\

#endif

