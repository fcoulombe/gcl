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

#include "gcl/Path.h"

#if defined(OS_WIN32) && !defined(__GNUC__)
#   include <windows.h>
#else
#	include <unistd.h>
#endif
//============================================================================

using namespace GCL;

//============================================================================

const std::string Path::PathToFirstSlash(const std::string  &dir)
{
	const char DIR_SEPARATOR = '/';
	size_t size = dir.length();

    int i;
#if defined(OS_WIN32) && !defined(__GNUC__)
    const char DIR_SEPARATOR2 = '\\';
    for (i = ((int)size - 1); (i >= 0) && (dir[i] != DIR_SEPARATOR) && (dir[i] != DIR_SEPARATOR2); --i)
        ;
#else
	for (i = ((int)size - 1); (i >= 0) && (dir[i] != DIR_SEPARATOR); --i)
		;
#endif
	return dir.substr(0, i);
}
const std::string Path::PathFromFirstSlash(const std::string  &dir)
{
	int i;
	size_t size = dir.length();

    const char DIR_SEPARATOR = '/';
#if defined(OS_WIN32) && !defined(__GNUC__)
    const char DIR_SEPARATOR2 = '\\';
    for (i = ((int)size - 1); (i >= 0) && (dir[i] != DIR_SEPARATOR)&& (dir[i] != DIR_SEPARATOR2); --i)
        ;
#else
    for (i = ((int)size - 1); (i >= 0) && (dir[i] != DIR_SEPARATOR); --i)
		;
#endif
	return dir.substr(i+1, size);
}

const std::string Path::Cwd()
{
#if defined(OS_WIN32) && !defined(__GNUC__)
    char lpCurrentDirectory[_MAX_PATH];
    ::GetCurrentDirectory( _MAX_PATH - 1, lpCurrentDirectory );
    return std::string(lpCurrentDirectory);
#else
	char cwd[4096 + 1] = { '\0' };
	const char *ret = getcwd(cwd, sizeof(cwd));
	(void)ret;
	return std::string(cwd);
#endif
}

#ifndef PATH_MAX
#define PATH_MAX 255
#endif
const std::string Path::GetApplicationPath()
{
#if defined(OS_WIN32) 
#if defined(__GNUC__)
return std::string();
#else
    char strPathName[_MAX_PATH];
    ::GetModuleFileName(NULL, strPathName, _MAX_PATH);

    return std::string(strPathName);
#endif

#else
    char result[ PATH_MAX ];
	ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
	return std::string( result, (count > 0) ? count : 0 );
#endif
}



const std::string Path::GetFileNameExtension(const std::string &path)
{
	size_t dotPos = path.rfind('.');
	if (dotPos == std::string::npos)
		return std::string("");
	else
		return path.substr(dotPos+1, std::string::npos);
}

//============================================================================
