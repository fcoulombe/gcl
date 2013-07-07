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
#include <cstdlib>
#include <cstring>
#include <stdint.h>
#include <fstream>
#include "gcl/Math.h"
#include "gcl/Pixel.h"
#include "gcl/Path.h"
#include "gcl/Rect.h"

namespace GCL
{

class PixelBuffer
{
public:
	PixelBuffer()
	{
		mPixels = NULL;
	}
	//deep copy
	PixelBuffer(const PixelBuffer &buffer)
	{
		if (buffer.mPixels)
		{
		mPixels = new uint8_t[buffer.mWidth *buffer.mHeight *buffer.mBytesPerPixel];
		memcpy(mPixels, buffer.mPixels, buffer.mWidth *buffer.mHeight *buffer.mBytesPerPixel);
		}
		else
		{
			mPixels = buffer.mPixels;
		}
		mWidth = buffer.mWidth;
		mHeight = buffer.mHeight;
		mBytesPerPixel = buffer.mBytesPerPixel;
		mBitDepth = buffer.mBitDepth;
		mBitsPerPixel = buffer.mBitsPerPixel;
	}
	PixelBuffer(const std::string &filename)
	{
		const std::string ext = Path::GetFileNameExtension(filename);
		if (ext == "tga")
		{
			std::fstream fp(filename.c_str(), std::ios::binary|std::ios::in);
			GCLAssertMsg( fp.good(), filename);
			PixelBuffer::LoadTga(fp, *this);
			fp.close();
		}
		else if (ext == "png")
		{
			FILE *fp = fopen(filename.c_str(), "rb");
			GCLAssertMsg(fp, filename);
			PixelBuffer::LoadPng(fp, *this);
			fclose(fp);
		}
		else if (ext == "raw")
		{
			std::fstream fp(filename.c_str(), std::fstream::binary|std::fstream::in);
			GCLAssertMsg( fp.good(), filename);
			PixelBuffer::LoadRaw(fp, *this);
			fp.close();
		}
		else
			GCLAssertMsg(false, "Unsupported file extension: " + ext);

	}
    PixelBuffer( size_t width, size_t height, size_t bytesPerPixel)
    {
		mPixels = NULL;
		Initialize(width, height, bytesPerPixel);
    }
	template<typename PixelType>
	PixelBuffer( size_t width, size_t height)
	{
		mPixels = NULL;
		Initialize(width, height, sizeof(PixelType));
	}
	template<typename PixelType>
	PixelBuffer(PixelType* data, size_t width, size_t height)
	{
		if (data)
		{
		mPixels = new uint8_t[sizeof(PixelType)*width*height];
		memcpy(mPixels, data, sizeof(PixelType)*width*height);
		}
		else
		{
			mPixels = (uint8_t*)data;
		}
		mWidth = width;
		mHeight = height;
		mBytesPerPixel = (uint8_t)PixelType::OffsetToNext();
		mBitDepth = 8;
		mBitsPerPixel = (uint8_t)(PixelType::OffsetToNext()*mBitDepth);
	}

	~PixelBuffer() 
	{
		delete [] mPixels;
	}
	void Initialize(size_t width, size_t height, size_t bytesPerPixel)
	{
		if (mPixels)
			delete [] mPixels;
		mPixels = new uint8_t[width*height*bytesPerPixel];
		mWidth = width;
		mHeight = height;
		mBytesPerPixel = (uint8_t)bytesPerPixel;
		mBitDepth = 8;
		mBitsPerPixel = (uint8_t)bytesPerPixel*mBitDepth;
	}
	uint8_t mBitDepth;
	uint8_t  mBitsPerPixel;
	uint8_t  mBytesPerPixel;
	size_t mWidth, mHeight;
	uint8_t *mPixels;

	size_t GetBufferSize() const { return mWidth*mHeight*mBytesPerPixel; }
	void PadToNextPOT()
	{
		size_t futureWidth = UpgradeToNextPowerOf2(mWidth);
		size_t futureHeight = UpgradeToNextPowerOf2(mHeight);
		size_t futureBufferSize = mBytesPerPixel*futureHeight*futureWidth;
		uint8_t *newBuffer = new uint8_t[futureBufferSize];
		memset(newBuffer, 0, futureBufferSize);
		for (size_t i=0; i<mHeight; ++i)
		{
			memcpy(&(newBuffer[i*futureWidth*mBytesPerPixel]), &(mPixels[i*mWidth*mBytesPerPixel]), mWidth*mBytesPerPixel);
		}
		mWidth = futureWidth;
		mHeight = futureHeight;
		delete [] mPixels;
		mPixels = newBuffer;
	}

    //blit a buffer onto this one at a specific location
	void Blit(const PixelBuffer &buffer, size_t x, size_t y);
    //blit a section of buffer onto this one
    void Blit(const PixelBuffer &buffer, size_t x, size_t y, const Rect<int> &clip);

    template<typename T>
    void SetPixel(size_t x, size_t y, const T &color)
    {
        GCLAssert(sizeof(T) == mBytesPerPixel);
        uint8_t *currPos = &(mPixels[x*mBytesPerPixel+y*mWidth*mBytesPerPixel]);
        *(T*)(currPos) = color;
    }

	static void SaveTga(const char *filename,
			size_t width, size_t height,
			size_t bytePerPixel,
			const uint8_t *data );
	static void LoadPng(FILE *is, PixelBuffer &data);
	static void LoadTga(std::istream &is, PixelBuffer &data);
	static void LoadRaw(std::istream &is, PixelBuffer &data);

	static void Unload(PixelBuffer &data);
private:

};
inline	bool operator==(const PixelBuffer &lhs, const PixelBuffer &rhs)
								{
	if (lhs.mBitDepth != rhs.mBitDepth)
		return false;
	if (lhs.mBitsPerPixel != rhs.mBitsPerPixel)
		return false;
	if (lhs.mBytesPerPixel != rhs.mBytesPerPixel)
		return false;
	if (lhs.mHeight != rhs.mHeight)
		return false;
	if (lhs.mWidth != rhs.mWidth)
		return false;
	if (memcmp(lhs.mPixels, rhs.mPixels, lhs.GetBufferSize()) != 0)
		return false;
	return true;
								}



}

