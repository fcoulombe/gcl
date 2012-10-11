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
#include "gcl/Math.h"
#include "gcl/Pixel.h"

namespace GCL
{

class PixelBuffer
{
public:
	PixelBuffer()
	{
		mPixels = NULL;
	}

	template<typename PixelType>
	PixelBuffer(PixelType *pixelArray, size_t width, size_t height)
	{
		Initialize(pixelArray, width, height);
	}
	template<typename PixelType>
	void Initialize(PixelType *pixelArray, size_t width, size_t height)
	{
		mPixels = (uint8_t*)pixelArray;
		mWidth = width;
		mHeight = height;
		mBytesPerPixel = PixelType::OffsetToNext();
		mBitsPerPixel = PixelType::OffsetToNext()*8;
	}
	~PixelBuffer() {}
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

	void Blit(const PixelBuffer &buffer, size_t x, size_t y);


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

