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

#include <gcl/PixelBuffer.h>
#if	defined(OS_WIN32) && !defined(__GNUC__)
#pragma warning( disable : 4611 ) //setjmp needed by lib png
#endif

#include <png.h>


using namespace GCL;

struct DataHandle
{
	DataHandle(const png_byte* in_data, const png_size_t in_size)
	:data(in_data), size(in_size){}
    const png_byte* data;
    const png_size_t size;
private:
    DataHandle &operator=(const DataHandle &tmp);
};

struct ReadDataHandle
{
	ReadDataHandle(const DataHandle in_data, png_size_t in_offset)
	: data(in_data), offset(in_offset){}
    const DataHandle data;
    png_size_t offset;
private:
    ReadDataHandle &operator=(const ReadDataHandle &tmp);
};

struct PngInfo
{
	PngInfo(const png_uint_32 in_width, const png_uint_32 in_height, const int in_color_type)
	: width(in_width), height(in_height), color_type(in_color_type){}
    const png_uint_32 width;
    const png_uint_32 height;
    const int color_type;
private:
    PngInfo &operator=(const PngInfo &tmp);
};

static void read_png_data_callback(png_structp png_ptr, png_byte* png_data, png_size_t read_length);
static PngInfo read_and_update_info(const png_structp png_ptr, const png_infop info_ptr);
static DataHandle read_entire_png_image(const png_structp png_ptr, const png_infop info_ptr, const png_uint_32 height);


void get_raw_image_data_from_png(const void* png_data, const size_t png_data_size, PixelBuffer &textureData)
{
    GCLAssert(png_data != NULL && png_data_size > 8);
    GCLAssert(png_check_sig((uint8_t*)png_data, 8));

    png_structp png_ptr = png_create_read_struct(
        PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    GCLAssert(png_ptr != NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    GCLAssert(info_ptr != NULL);

    ReadDataHandle png_data_handle(DataHandle((png_byte*)png_data, (png_size_t)png_data_size), 0);
    png_set_read_fn(png_ptr, &png_data_handle, read_png_data_callback);

    if (setjmp(png_jmpbuf(png_ptr))) {
        GCLAssert(false && "Error reading PNG file!");
    }

    const PngInfo png_info = read_and_update_info(png_ptr, info_ptr);
    const DataHandle raw_image = read_entire_png_image(
        png_ptr, info_ptr, png_info.height);

    png_read_end(png_ptr, info_ptr);
    png_uint_32 bitdepth   = png_get_bit_depth(png_ptr, info_ptr);
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    textureData.mPixels = (uint8_t*)raw_image.data;
    textureData.mWidth = png_info.width;
    textureData.mHeight = png_info.height;

	switch (png_info.color_type)
	{
	case PNG_COLOR_TYPE_PALETTE:
		textureData.mBytesPerPixel = 3;
		break;
	case PNG_COLOR_TYPE_GRAY:
		textureData.mBytesPerPixel = 1;
		break;
	case PNG_COLOR_TYPE_RGB_ALPHA:
		textureData.mBytesPerPixel = 4;
		break;
	case PNG_COLOR_TYPE_RGB:
		textureData.mBytesPerPixel = 3;
		break;
	default:
		GCLAssert(false);
	}

	textureData.mBitDepth = (uint8_t)bitdepth;
	textureData.mBitsPerPixel = textureData.mBitDepth*textureData.mBytesPerPixel;
}

static void read_png_data_callback(png_structp png_ptr,
                                   png_byte* raw_data,
                                   png_size_t read_length) 
{
    ReadDataHandle* handle = (ReadDataHandle*)png_get_io_ptr(png_ptr);
    const png_byte* png_src = handle->data.data + handle->offset;

    memcpy(raw_data, png_src, read_length);
    handle->offset += read_length;
}

static PngInfo read_and_update_info(const png_structp png_ptr, const png_infop info_ptr)
{
    png_uint_32 width, height;
    int bit_depth, color_type;

    png_read_info(png_ptr, info_ptr);
    png_get_IHDR(
        png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, NULL, NULL, NULL);

    // Convert transparency to full alpha
    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(png_ptr);

    // Convert grayscale, if needed.
    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(png_ptr);

    // Convert paletted images, if needed.
    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(png_ptr);

    // Add alpha channel, if there is none.
    // Rationale: GL_RGBA is faster than GL_RGB on many GPUs)
    if (color_type == PNG_COLOR_TYPE_PALETTE || color_type == PNG_COLOR_TYPE_RGB)
       png_set_add_alpha(png_ptr, 0xFF, PNG_FILLER_AFTER);

    // Ensure 8-bit packing
    if (bit_depth < 8)
       png_set_packing(png_ptr);
    else if (bit_depth == 16)
        png_set_scale_16(png_ptr);

    png_read_update_info(png_ptr, info_ptr);

    // Read the new color type after updates have been made.
    color_type = png_get_color_type(png_ptr, info_ptr);

    return PngInfo(width, height, color_type);
}

static DataHandle read_entire_png_image(
    const png_structp png_ptr,
    const png_infop info_ptr,
    const png_uint_32 height)
{
    const png_size_t row_size = png_get_rowbytes(png_ptr, info_ptr);
    const png_size_t data_length = row_size * height;
    GCLAssert(row_size > 0);

    png_byte* raw_image = new png_byte[data_length];
    GCLAssert(raw_image != NULL);

    GCLAssert(height < 4096)
    png_byte* row_ptrs[4096];

	//A little for-loop here to set all the row pointers to the starting
	//addresses for every row in the buffer
    png_uint_32 i;
    for (i = 0; i < height; i++)
    {
        row_ptrs[i] = raw_image + (height - i -1) * row_size;
    }

    png_read_image(png_ptr, &row_ptrs[0]);

    return DataHandle(raw_image, data_length);
}



void PixelBuffer::LoadPng(GCLFile &source, PixelBuffer &textureData)
{
	auto fileContent = source.ReadAll();
	get_raw_image_data_from_png(std::get<0>(fileContent).get(), std::get<1>(fileContent), textureData);
}


