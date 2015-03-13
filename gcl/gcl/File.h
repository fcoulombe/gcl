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

#include <cstdio>
#include <memory>

//============================================================================
struct AAsset;
struct AAssetManager;
namespace GCL
{
//============================================================================
class IFile
{
public:
	virtual ~IFile()
	{
	}
	virtual size_t GetFileSize() const = 0;
	virtual size_t GetCurrentReadPos() const = 0;
	virtual std::tuple<std::unique_ptr<uint8_t[]>, size_t> ReadAll() = 0;
	virtual void Read(void *buffer, size_t count) = 0;
	virtual void Close() = 0;
	virtual void Open(const char *file, const char *mode) = 0;

};
class GCLFile : public IFile
{
public:
	GCLFile(const std::string &file, const char *mode = "rb")
		: mFp(nullptr)
	{
		Open(file.c_str(), mode);
	}
	GCLFile(const char *file, const char *mode = "rb")
		: mFp(nullptr)
	{
		Open(file, mode);
	}

	~GCLFile()
	{
		Close();
	}
	size_t GetFileSize() const;
	size_t GetCurrentReadPos() const;
	std::tuple<std::unique_ptr<uint8_t[]>, size_t> ReadAll();
	void Read(void *buffer, size_t count);
	void Write(void *buffer, size_t count);
	void Close();
	void Open(const char *file, const char *mode);
	static bool Exists(const char *filename);
	static bool Exists(const std::string &filename) { return Exists(filename.c_str()); }

	static void SetDataPath(const char *dataPath);
private:
	FILE* mFp;
	static std::string mDataPath;
};

class ResourceFile
#ifdef OS_ANDROID
		: public IFile
#else
		: public GCLFile
#endif
{
public:
#ifdef OS_ANDROID

	ResourceFile(const std::string &file, const char *mode = "rb")
	{
		Open(file.c_str(), mode);
	}
	ResourceFile(const char *file, const char *mode = "rb")
	{
		Open(file, mode);
	}
	~ResourceFile() {}
	size_t GetFileSize() const;
	size_t GetCurrentReadPos() const;
	std::tuple<std::unique_ptr<uint8_t[]>, size_t> ReadAll();
	void Read(void *buffer, size_t count);
	void Close();
	void Open(const char *file, const char *mode);

	static void RegisterAssetManager(AAssetManager* mgr);
	static bool Exists(const char *filename);
	static bool Exists(const std::string &filename) { return Exists(filename.c_str()); }
#else
	ResourceFile(const std::string &file, const char *mode = "rb")
	: GCLFile(file, mode)
	{
	}
	ResourceFile(const char *file, const char *mode = "rb")
	: GCLFile(file, mode)
	{
	}
#endif
private:
    void Write(void *buffer, size_t count);
#ifdef OS_ANDROID
	AAsset* mFp;
	static AAssetManager* mAssetManager;
#endif
};

//============================================================================
} // namespace GCL
//============================================================================
