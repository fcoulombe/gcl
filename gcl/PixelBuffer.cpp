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

#include "gcl/PixelBuffer.h"

#include <fstream>

#include "gcl/Assert.h"


using namespace GCL;


void PixelBuffer::Blit(const PixelBuffer &buffer, size_t x, size_t y)
{
	GCLAssert(buffer.mBytesPerPixel == mBytesPerPixel);
    size_t thisBufferOffset = x*mBytesPerPixel+y*mWidth*mBytesPerPixel;
    GCLAssert(thisBufferOffset < GetBufferSize() && "writing past the buffer bounds"); 
    uint8_t *currPos = &(mPixels[thisBufferOffset]);
	for (size_t j=0; j<buffer.mHeight; ++j)
	{
		uint8_t *line = &(buffer.mPixels[j*buffer.mWidth*buffer.mBytesPerPixel]);
		memcpy(currPos, line, buffer.mWidth*mBytesPerPixel);
		currPos += mWidth*mBytesPerPixel;
	}
    GCLAssert(intptr_t(currPos-mWidth*mBytesPerPixel)-intptr_t(mPixels) < GetBufferSize() && "writing past the buffer bounds"); 
}

void PixelBuffer::Blit(const PixelBuffer &buffer, size_t x, size_t y, const Rect<int> &clip)
{
    GCLAssert(buffer.mBytesPerPixel == mBytesPerPixel);
    size_t thisBufferOffset = x*mBytesPerPixel+y*mWidth*mBytesPerPixel;
    GCLAssert(thisBufferOffset < GetBufferSize() && "writing past the buffer bounds"); 
    uint8_t *currPos = &(mPixels[thisBufferOffset]);

    GCLAssert(thisBufferOffset+mWidth*mBytesPerPixel*(clip.height-1)+(clip.width-1)*mBytesPerPixel < GetBufferSize() && "writing past the buffer bounds"); 
    for (size_t j=0; j<clip.height; ++j)
    {
        size_t offset = clip.y*buffer.mWidth*buffer.mBytesPerPixel+j*buffer.mWidth*buffer.mBytesPerPixel;
        offset+=clip.x*buffer.mBytesPerPixel;
        uint8_t *line = &(buffer.mPixels[offset]);
        memcpy(currPos, line, clip.width*mBytesPerPixel);
        currPos += mWidth*mBytesPerPixel;
    }
    
   

}

void PixelBuffer::Unload(PixelBuffer &data)
{
	if (data.mPixels)
		delete [] data.mPixels;
}


