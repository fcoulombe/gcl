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
#ifndef OS_ANDROID
#include "gcl/Assert.h"
#include "gcl/File.h"

//============================================================================

using namespace GCL;

size_t GCLFile::GetCurrentReadPos() const
{
	std::streampos pos = ((std::istream&)mFp).tellg() ;
	return (size_t)pos;
}

size_t GCLFile::GetFileSize() const
{
	((std::istream&)mFp).seekg(0, std::ios::end);
	std::streampos pos = ((std::istream&)mFp).tellg() ;
    ((std::istream&)mFp).seekg(0, std::ios::beg);
	return (size_t)pos;
}
void GCLFile::Read(void *buffer, size_t count)
{
	mFp.read((char*)buffer, count);
}
std::unique_ptr<uint8_t[]> GCLFile::ReadAll()
{
	size_t bufferSize = GetFileSize();
	std::unique_ptr<uint8_t[]> buffer(new uint8_t[bufferSize]);
	mFp.read((char*)buffer.get(), bufferSize);
	return buffer;
}
void GCLFile::Close()
{
	mFp.close();
}
void GCLFile::Open(const char *file )
{
	mFp.open(file, std::ios::in|std::ios::binary);
	std::string msg("trying to loads " );
	msg += file;
	msg += "\n";
	GCLAssertMsg(mFp.is_open() && mFp.good(), msg.c_str());
}


bool GCLFile::Exists(const char *filename)
{
	std::fstream fp(filename);
	if (fp.good())
	{
		fp.close();
		return true;
	}
	return false;
}
//============================================================================
#endif
