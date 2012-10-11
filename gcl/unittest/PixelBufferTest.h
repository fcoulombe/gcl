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

#include <sstream>

#include <gcl/PixelBuffer.h>
#include <gcl/UnitTest.h>

using namespace GCL;
namespace PixelBufferTest
{
void Test();
void Test()
{
	TEST_START
	PixelBuffer bufferMono;
	PixelBuffer bufferRGB;
	PixelBuffer bufferRGBA;

	bufferMono.mWidth = 122;
	bufferMono.mHeight = 122;
	bufferMono.mBitsPerPixel = 8;
	bufferMono.mBytesPerPixel = 1;
	bufferMono.mPixels = new uint8_t[sizeof(PixelMono)*122*122];

	bufferMono.PadToNextPOT();
	Assert_Test(bufferMono.mWidth == 128);

	Assert_Test(bufferMono.mHeight == 128);
	//see font test

	//Pixel Buffer Texture
	{
		const char *fullFileName = TEXTURE_PATH"mushroomtga.tga";

		PixelBuffer buffer(fullFileName);
		PixelBuffer buffer2;
		buffer2.mPixels = new uint8_t[buffer.GetBufferSize()];
		buffer2.mBitDepth = buffer.mBitDepth;
		buffer2.mBitsPerPixel = buffer.mBitsPerPixel;
		buffer2.mBytesPerPixel = buffer.mBytesPerPixel;
		buffer2.mHeight = buffer.mHeight;
		buffer2.mWidth = buffer.mWidth;
		buffer2.Blit(buffer, 0,0);
#ifndef OS_IPHONE
		PixelBuffer::SaveTga("PixelBufferBlitTest.tga", buffer2.mWidth, buffer2.mHeight, buffer2.mBytesPerPixel, buffer2.mPixels);
		AssertMsg_Test(UnitTest::ImageComp("PixelBufferBlitTest.tga"), "PixelBufferBlitTest.tga");
#endif
	}
	//Pixel Buffer blit test
	{
		const char *fullFileName = TEXTURE_PATH"mushroomtga_small.tga";

		PixelBuffer buffer(fullFileName);
		PixelBuffer buffer2;
		buffer2.mPixels = new uint8_t[buffer.GetBufferSize()*8*8];
		buffer2.mBitDepth = buffer.mBitDepth;
		buffer2.mBitsPerPixel = buffer.mBitsPerPixel;
		buffer2.mBytesPerPixel = buffer.mBytesPerPixel;
		buffer2.mHeight = buffer.mHeight*8;
		buffer2.mWidth = buffer.mWidth*8;
		for (size_t i=0; i<8; ++i)
		{
			for (size_t j=0; j<8; ++j)
			{
				buffer2.Blit(buffer, i*64,j*64);
			}
		}
#ifndef OS_IPHONE
		PixelBuffer::SaveTga("PixelBufferBlitTest2.tga", buffer2.mWidth, buffer2.mHeight, buffer2.mBytesPerPixel, buffer2.mPixels);
		AssertMsg_Test(UnitTest::ImageComp("PixelBufferBlitTest2.tga"), "PixelBufferBlitTest2.tga");
		PixelBuffer compareTestBuffer("PixelBufferBlitTest2.tga");
		Assert_Test(compareTestBuffer == buffer2);
#endif
	}
	//test that all the images that got saved are equal to what we expect
	{

	}
}

}
