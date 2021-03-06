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

#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "gcl/Assert.h"
#include "gcl/File.h"
#include "gcl/Memory.h"
#include "gcl/Point2.h"
#include "gcl/Point3.h"
#include "gcl/Point4.h"
#include "gcl/Matrix44.h"

namespace GCL
{


class BufferWriter
{
public:
	BufferWriter(size_t bufferSize)
	: mCurrentOffset(0),
	  mBufferSize(bufferSize)
	{
		buffer = new uint8_t[mBufferSize];
		memset(buffer, 0xfe, mBufferSize);
	}
	~BufferWriter()
	{
		delete [] buffer;
	}
	void Pad()
	{
#if USE_64BIT_PLATFORM
		mCurrentOffset = Memory::Align64(mCurrentOffset);
#else
		mCurrentOffset = Memory::Align32(mCurrentOffset);
#endif
		//std::cout << "cur: " << mCurrentOffset << "add: " << pad << std::endl;
		GCLAssertMsg(mCurrentOffset <= mBufferSize, "your buffer is too small. please increase its size");
	}

	static size_t GetPaddingSize()
	{
#if USE_64BIT_PLATFORM
		return sizeof(uint64_t);;
#else
		return sizeof(uint32_t);
#endif
	}
	template<typename T>
	void Write(T &val)
	{
		//std::cout << "adding: " <<sizeof(T) << " to: " << mCurrentOffset << std::endl;
		memcpy(&(buffer[mCurrentOffset]), &val, sizeof(T));
		mCurrentOffset += sizeof(T);
		GCLAssertMsg(mCurrentOffset <= mBufferSize, "your buffer is too small. please increase its size");
	}
	//assumes null terminated string
	void Write(const char *str, size_t len)
	{
		memcpy(&(buffer[mCurrentOffset]), str, len+1);
		mCurrentOffset += len+1;
		GCLAssertMsg(mCurrentOffset <= mBufferSize, "your buffer is too small. please increase its size");
	}

	void WriteToFile(const std::string &filename)
	{
		GCLFile outFile(filename.c_str(), "wb+");
		outFile.Write(buffer, mCurrentOffset);
	}
	size_t GetCurrentOffset() const { return mCurrentOffset; }
	uint8_t *GetBuffer() { return buffer; }
private:
	uint8_t *buffer;
	size_t mCurrentOffset;
	size_t mBufferSize;
};

template<typename T>
GCLINLINE BufferWriter &operator<<(BufferWriter &buffer, const T &data)
{
    buffer.Write(data);
    return buffer;
}

template<typename T>
GCLINLINE BufferWriter &operator<<(BufferWriter &buffer, const Point2<T> &data)
{
	buffer.Write(data.x);
	buffer.Write(data.y);
	return buffer;
}

template<typename T>
GCLINLINE BufferWriter &operator<<(BufferWriter &buffer, const Point3<T> &data)
{
	buffer.Write(data.x);
	buffer.Write(data.y);
	buffer.Write(data.z);
	return buffer;
}

template<typename T>
GCLINLINE BufferWriter &operator<<(BufferWriter &buffer, const Point4<T> &data)
{
	buffer.Write(data.x);
	buffer.Write(data.y);
	buffer.Write(data.z);
	buffer.Write(data.w);
	return buffer;
}
GCLINLINE BufferWriter &operator<<(BufferWriter &buffer, const Matrix44 &data)
{
    buffer << data[0];
    buffer << data[1];
    buffer << data[2];
    buffer << data[3];
    return buffer;
}
GCLINLINE BufferWriter & operator<<( BufferWriter& buffer, const std::string &stringData)
{
	uint32_t paddedLen = 0xbaadf00d;// = uint32_t(Memory::Align(len+1));
    size_t currOffset = buffer.GetCurrentOffset();
	uint32_t *patchLen = (uint32_t *)&(buffer.GetBuffer()[currOffset]);
	buffer.Write(paddedLen);
	currOffset = buffer.GetCurrentOffset();

	buffer.Write(stringData.c_str(), stringData.length());
	buffer.Pad();
    *patchLen = (uint32_t)(buffer.GetCurrentOffset()-currOffset);
	return buffer;
}
}
