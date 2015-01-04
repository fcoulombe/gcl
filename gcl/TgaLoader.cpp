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


#include "gcl/Assert.h"
#include "gcl/Log.h"
#include "gcl/TGALoaderData.h"

#include <cstring>
#include <iostream>
#include <fstream>

using namespace GCL;

void PixelBuffer::LoadTga(IFile &fp, PixelBuffer &data)
{
	TGAHeader header ;
	memset(&header, 0, sizeof(header));
	fp.Read((char*)&header, sizeof(TGAHeader));

	if(memcmp(TGAUncompressedHeader, &header, sizeof(TGAUncompressedHeader)) == 0)
	{
		data.mWidth       = header.TGAHEADER.width; //tga.header[1] * 256 + tga.header[0];
		data.mHeight      = header.TGAHEADER.height; //tga.header[3] * 256 + tga.header[2];
		data.mBitsPerPixel = header.TGAHEADER.bitsperpixel; //tga.header[4];
		data.mBitDepth = 8;
		data.mBytesPerPixel = data.mBitsPerPixel/data.mBitDepth;

		//test that we have power rof 2 textture
		if ( (data.mWidth & (data.mWidth - 1))  != 0  &&
				(data.mHeight & (data.mHeight - 1)) != 0 )
		{
			KLog("Warning: the texture is not a power of 2");
		}
		/*if(data.mBytePerPixel == 3)
			data.mTextureFormat      = GL_RGB;
		else if (data.mBytePerPixel == 4)
			data.mTextureFormat      = GL_RGBA;
*/
		size_t imageSize = (data.mBytesPerPixel * data.mWidth * data.mHeight);
		data.mPixels =  new uint8_t[imageSize];
		fp.Read(data.mPixels, imageSize);

		//swap the R and the B
		for(uint32_t cswap = 0; cswap < imageSize; cswap += data.mBytesPerPixel)
		{
			uint8_t temp = data.mPixels[cswap];
			data.mPixels[cswap] = data.mPixels[cswap+2];
			data.mPixels[cswap+2] = temp;
		}
	}
	//check if header is compressed
	else if(memcmp(TGACompressedHeader, &header, sizeof(TGACompressedHeader)) == 0)
	{
        data.mWidth       = header.TGAHEADER.width; //tga.header[1] * 256 + tga.header[0];
        data.mHeight      = header.TGAHEADER.height; //tga.header[3] * 256 + tga.header[2];
        data.mBitsPerPixel = header.TGAHEADER.bitsperpixel; //tga.header[4];
		data.mBitDepth = 8;
		data.mBytesPerPixel = data.mBitsPerPixel/data.mBitDepth;

		GCLAssert(data.mWidth &&
				data.mHeight &&
				(data.mBytesPerPixel == 3 || data.mBytesPerPixel ==4)) ;

		/*if(data.mBytesPerPixel == 3)           // Is It A 24bpp Image?
			data.mTextureFormat    = GL_RGB;   // If So, Set Type To GL_RGB
		else                    // If It's Not 24, It Must Be 32
			data.mTextureFormat    = GL_RGBA;  // So Set The Type To GL_RGBA
*/
		size_t imageSize       = (data.mBytesPerPixel * data.mWidth * data.mHeight);

		// Allocate Memory To Store Image Data
		data.mPixels   = new uint8_t[imageSize];

		size_t pixelcount = data.mHeight * data.mWidth ; // Number Of Pixels In The Image
		size_t currentpixel = 0;            // Current Pixel We Are Reading From Data
		size_t currentbyte  = 0;            // Current Byte We Are Writing Into Imagedata
		// Storage For 1 Pixel
		uint8_t * colorbuffer = new uint8_t[data.mBytesPerPixel];

		do
		{
			uint8_t chunkheader = 0;            // Variable To Store The Value Of The Id Chunk
			fp.Read(&chunkheader, sizeof(uint8_t));

			if(chunkheader < 128)                // If The Chunk Is A 'RAW' Chunk
			{
				chunkheader++;              // Add 1 To The Value To Get Total Number Of Raw Pixels
				// Start Pixel Reading Loop
				for(size_t counter = 0; counter < chunkheader; counter++)
				{
					// Try To Read 1 Pixel
					fp.Read(colorbuffer, data.mBytesPerPixel) ;
					//GCLAssert(fp.good());
					uint8_t &temp = data.mPixels[currentbyte];
					uint8_t temp2 = colorbuffer[2];
					temp = temp2;
					data.mPixels[currentbyte] = colorbuffer[2];        // Write The 'R' Byte
					data.mPixels[currentbyte + 1   ] = colorbuffer[1]; // Write The 'G' Byte
					data.mPixels[currentbyte + 2   ] = colorbuffer[0]; // Write The 'B' Byte
					if(data.mBytesPerPixel == 4)                  // If It's A 32bpp Image...
					{
						data.mPixels[currentbyte + 3] = colorbuffer[3];    // Write The 'A' Byte
					}
					// Increment The Byte Counter By The Number Of Bytes In A Pixel
					currentbyte += data.mBytesPerPixel;
					currentpixel++;                 // Increment The Number Of Pixels By 1
				}
			}
			else                        // If It's An RLE Header
			{
				chunkheader -= 127;         // Subtract 127 To Get Rid Of The ID Bit
				// Read The Next Pixel
				fp.Read(colorbuffer, data.mBytesPerPixel) ;

				// Start The Loop
				for(size_t counter = 0; counter < chunkheader; counter++)
				{
					// Copy The 'R' Byte
					data.mPixels[currentbyte] = colorbuffer[2];
					// Copy The 'G' Byte
					data.mPixels[currentbyte + 1   ] = colorbuffer[1];
					// Copy The 'B' Byte
					data.mPixels[currentbyte + 2   ] = colorbuffer[0];
					if(data.mBytesPerPixel== 4)      // If It's A 32bpp Image
					{
						// Copy The 'A' Byte
						data.mPixels[currentbyte + 3] = colorbuffer[3];
					}
					currentbyte += data.mBytesPerPixel;   // Increment The Byte Counter
					currentpixel++;             // Increment The Pixel Counter
				}
			}
		}	while(currentpixel < pixelcount);    // More Pixels To Read? ... Start Loop Over
		delete [] colorbuffer;

	}
	//unknown header
	else
	{
		data.mPixels = NULL;
		GCLAssert(false && "Unknown image header");
	}
}


//franky disable strict aliasing warning for this save funcgtion
#if defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

void PixelBuffer::SaveTga(const char *filename, size_t width, size_t height, size_t bytePerPixel,const uint8_t *data )
{
	const char *ext = &(filename[strlen(filename)-3]);
	if (strncmp(ext, "tga", 3)==0)
	{
		uint16_t x = (uint16_t)width;
		uint16_t y = (uint16_t)height;
		// split x and y sizes into bytes

	    TGAHeader header ;
        memset(&header, 0, sizeof(header));
		if (bytePerPixel == 1)
			header.TGAHEADER.datatypecode  = 3; //setting mode to gray since we only have 1 byte per pixel
        else if (bytePerPixel>=3)
            header.TGAHEADER.datatypecode = 2;
        else
        {
            GCLAssert(false && "unsupported");
        }
        header.TGAHEADER.x_origin = 0;
        header.TGAHEADER.y_origin = 0;
        header.TGAHEADER.width = x;
        header.TGAHEADER.height = y;
        header.TGAHEADER.bitsperpixel = (uint8_t)(bytePerPixel*8);

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
		File.write ((const char *)&header, sizeof (header));
		File.write ((const char *)tempData, imageSize);
		File.close();

		delete[] tempData;
		tempData=NULL;
	}
	else
	{
		std::string s("This extension is not supported: ");
		s += ext;
		GCLAssertMsg(false, s)
	}

}


