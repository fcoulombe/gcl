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
//============================================================================

#pragma once

#include <fstream>
#include <memory>

//============================================================================
struct AAsset;
struct AAssetManager;
namespace GCL
{
//============================================================================

class GCLFile
{
public:
	GCLFile(const std::string &file )
	{
		Open(file.c_str());
	}
	GCLFile(const char *file )
	{
		Open(file);
	}

	~GCLFile() {}
	size_t GetFileSize() const;
	size_t GetCurrentReadPos() const;
	std::tuple<std::unique_ptr<uint8_t[]>, size_t> ReadAll();
	void Read(void *buffer, size_t count);
	void Close();
	void Open(const char *file );
	static bool Exists(const char *filename);
	static bool Exists(const std::string &filename) { return Exists(filename.c_str()); }
#ifdef OS_ANDROID
	static void RegisterAssetManager(AAssetManager* mgr);
#endif
private:
#ifdef OS_ANDROID
	AAsset* mFp;
	static AAssetManager* mAssetManager;
#else
	std::fstream mFp;
#endif
};

//============================================================================
} // namespace GCL
//============================================================================
