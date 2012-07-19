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

#ifdef OS_WIN32
#   include <windows.h>
#endif
//============================================================================

using namespace GCL;

//============================================================================

const std::string Path::PathToFirstSlash(const std::string  &dir)
{
	const char DIR_SEPARATOR = '/';
	register int i;
	const std::string &loc = dir;
	size_t size = loc.length();

	for (i = (size - 1); (i >= 0) && (loc[i] != DIR_SEPARATOR); --i)
		;

	return loc.substr(0, i);
}
const std::string Path::PathFromFirstSlash(const std::string  &dir)
{
	register int i;
	const std::string &loc = dir;
	size_t size = loc.length();

    const char DIR_SEPARATOR = '/';
#ifdef OS_WIN32
    const char DIR_SEPARATOR2 = '\\';
    for (i = (size - 1); (i >= 0) && (loc[i] != DIR_SEPARATOR)&& (loc[i] != DIR_SEPARATOR2); --i)
        ;
#else
    for (i = (size - 1); (i >= 0) && (loc[i] != DIR_SEPARATOR); --i)
		;
#endif
	return loc.substr(i+1, size);
}

const std::string Path::Cwd()
{
#ifdef OS_WIN32
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

#define PATH_MAX 255
const std::string Path::GetApplicationPath()
{
#ifdef OS_WIN32
    char strPathName[_MAX_PATH];
    ::GetModuleFileName(NULL, strPathName, _MAX_PATH);

    return std::string(strPathName);
#else
    char result[ PATH_MAX ];
	ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
	return std::string( result, (count > 0) ? count : 0 );
#endif
}

//============================================================================
