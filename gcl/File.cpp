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
#include "gcl/Assert.h"
#include "gcl/File.h"

//============================================================================

using namespace GCL;
std::string GCLFile::mDataPath;
void GCLFile::SetDataPath(const char *dataPath)
{
	mDataPath = dataPath;
	mDataPath += "/";
}

size_t GCLFile::GetCurrentReadPos() const
{
	return ftell(mFp);
}

size_t GCLFile::GetFileSize() const
{
	fseek(mFp , 0 , SEEK_END);
	size_t size = ftell(mFp);
	rewind(mFp);
	return size;
}
void GCLFile::Read(void *buffer, size_t count)
{
	size_t ret = fread((char*)buffer, 1, count, mFp);
	GCLAssert(ret == count);
}

void GCLFile::Write(void *buffer, size_t count)
{
	size_t ret = fwrite((char*)buffer, 1, count, mFp);
	GCLAssert(ret == count);
}
std::tuple<std::unique_ptr<uint8_t[]>, size_t> GCLFile::ReadAll()
{
	size_t bufferSize = GetFileSize();
	std::unique_ptr<uint8_t[]> buffer(new uint8_t[bufferSize]);
	size_t ret = fread((char*)buffer.get(), 1, bufferSize, mFp);
	GCLAssert(ret == bufferSize);
	return std::make_tuple(std::move(buffer), bufferSize);
}
void GCLFile::Close()
{
	if (mFp)
	{
		fclose(mFp);
		mFp = nullptr;
	}
}
void GCLFile::Open(const char *file, const char *mode )
{
	std::string fullFileName = mDataPath + file;
	mFp = fopen(fullFileName.c_str(), mode);
	std::string msg("trying to loads " );
	msg += file;
	msg += "\n";
	GCLAssertMsg(mFp != nullptr, msg.c_str());
}


bool GCLFile::Exists(const char *filename)
{
	std::string fullFileName = mDataPath + filename;
	FILE* fp = fopen(fullFileName.c_str(), "r");
	if (fp != nullptr)
	{
		fclose(fp);
		return true;
	}
	return false;
}
//============================================================================
