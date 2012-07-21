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
#include <cstring>

#include "gcl/Assert.h"


using namespace GCL;



//franky disable strict aliasing warning for this save funcgtion
#if defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

void PixelBuffer::SaveTga(const char *filename, size_t width, size_t height, size_t bytePerPixel,const uint8_t *data )
{
	const char *ext = &(filename[strlen(filename)-3]);
	if (strncmp(ext, "tga", 3)==0)
	{
		uint16_t x = width;
		uint16_t y = height;
		// split x and y sizes into bytes

		//assemble the header
		uint8_t header[18]={
				0, //1			1
				0, //2 garbage	2
				2, //1 type		3
				0, //1			4
				0, //2			5
				0, //3			6
				0, //4			7
				0, //5 garbage	8
				0, //1			9
				0, //2 xstart	10
				0, //1			11
				0, //2 ystart	12
				0, //1 			13
				0, //2 width	14
				0, //1			15
				0, //2 height	16
				0, //1 bpp		17
				0, //1 desc		18
		};
		if (bytePerPixel == 1)
			header[2] = 3; //setting mode to gray since we only have 1 byte per pixel

		*(uint16_t*)&(header[8]) = 0;
		*(uint16_t*)&(header[10]) = 0;
		*(uint16_t*)&(header[12]) = x;
		*(uint16_t*)&(header[14]) = y;
		*(uint8_t*)&(header[16]) = bytePerPixel*8;

		size_t imageSize = sizeof (uint8_t)*width*height*bytePerPixel;
		//swap the R and the B
		uint8_t *tempData = new uint8_t[imageSize];
		memcpy(tempData, data, imageSize);
		if (bytePerPixel>=3)
		{
			for(size_t cswap = 0; cswap < imageSize; cswap += bytePerPixel)
			{
				uint8_t temp = tempData[cswap];
				tempData[cswap] = tempData[cswap+2];
				tempData[cswap+2] = temp;
			}
		}
		// write header and data to file
		std::fstream File(filename, std::ios::out | std::ios::binary);
		File.write ((const char *)&header, sizeof (uint8_t)*18);
		File.write ((const char *)tempData, imageSize);
		File.close();

		delete[] tempData;
		tempData=NULL;
		//SaveTga(filename);
	}
	else
	{
		std::string s("This extension is not supported: ");
		s += ext;
		GCLAssertMsg(false, s)
	}

}
