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

namespace GCL
{
#if defined(_MSC_VER) || defined(__GNUC__)
#pragma pack(push, 1)
#pragma pack(1)               // Dont pad the following struct.
#endif
    union TGAHeader
    {
        struct TGAHeaderU
        {
            uint8_t idlength;
            uint8_t colourmaptype;
            uint8_t datatypecode;

            int16_t colourmaporigin;
            int16_t colourmaplength;
            uint8_t colourmapdepth;
            
            int16_t x_origin;
            int16_t y_origin;
            int16_t width;
            int16_t height;
            uint8_t bitsperpixel;
            uint8_t imagedescriptor;
        }TGAHEADER;
        uint8_t Header[18];
    };
#if defined(_MSC_VER) || defined(__GNUC__)
#pragma pack(pop)
#endif



// Uncompressed TGA Header
const uint8_t TGAUncompressedHeader[12] = {0,0, 2,0,0,0,0,0,0,0,0,0};
// Compressed TGA Header
const uint8_t TGACompressedHeader[12] = {0,0,10,0,0,0,0,0,0,0,0,0};
}
