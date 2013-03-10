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
#include <gcl/Assert.h>
#include <gcl/Point3.h>
#include <gcl/Point4.h>

namespace GCL
{
enum PixelTypeComponents
{
	eMONO 	        = 1<<0,
	eRGB 	        = 1<<1,
	eRGBA			= 1<<2
};

struct PixelMono
{
    PixelMono()
        : mColor(0) {}
	uint8_t mColor;
	static uint32_t GetComponentType()  { return eMONO; }
	static size_t OffsetToNext() { return 1; }
};

struct PixelRGB
{
	Point3<uint8_t> mColor;
	static uint32_t GetComponentType() { return eRGB; }
	static size_t OffsetToNext() { return 3; }
};

struct PixelRGBA
{
	Point4<uint8_t> mColor;
	static uint32_t GetComponentType()  { return eRGBA; }
	static size_t OffsetToNext() { return 4; }
};
}
