/*
 * Copyright (C) 2014 by Francois Coulombe
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

#include "gcl/File.h"
namespace GCL
{
    class BufferReader
    {
    public:
        BufferReader(IFile &file)
            : mCurrentOffset(0)
        {
            auto buffer = file.ReadAll();
            mBuffer = std::move(std::get<0>(buffer));
            mBufferSize = std::get<1>(buffer);
        }
        template<typename T>
        void Read(T &data)
        {
            size_t dataSize = sizeof(T);
            memcpy(&data, &(mBuffer.get()[mCurrentOffset]), dataSize);
            mCurrentOffset += dataSize;
        }

        void Read(std::string &data)
        {
            size_t len = mBuffer.get()[mCurrentOffset];
            mCurrentOffset += sizeof(uint32_t);
            char buffer[4096];
            GCLAssert(len < 4096);
            memcpy(buffer, &(mBuffer.get()[mCurrentOffset]), len);
            data = buffer;
            mCurrentOffset += len;
        }
    private:
        std::unique_ptr<uint8_t[]> mBuffer;
        size_t mBufferSize;
        size_t mCurrentOffset;
    };
}
