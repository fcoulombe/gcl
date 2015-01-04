/*
 * Copyright (C) 2011 by Jeffrey Lim
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
#ifdef OS_ANDROID
#include "gcl/Assert.h"
#include "gcl/File.h"
#include "gcl/Log.h"
#include <android/asset_manager.h>

//============================================================================

using namespace GCL;

AAssetManager* ResourceFile::mAssetManager = nullptr;

size_t ResourceFile::GetCurrentReadPos() const
{
	GCLAssert("TBD");
	return -1;
}

size_t ResourceFile::GetFileSize() const
{
	return AAsset_getLength(mFp);
}
void ResourceFile::Read(void *buffer, size_t count)
{
	int ret = AAsset_read(mFp,buffer,count);
	GCLAssert(ret>0);
}
std::tuple<std::unique_ptr<uint8_t[]>, size_t> ResourceFile::ReadAll()
{
	size_t bufferSize = GetFileSize();
	std::unique_ptr<uint8_t[]> buffer(new uint8_t[bufferSize]);
	int ret = AAsset_read(mFp,(char*)buffer.get(),bufferSize);
	GCLAssert(ret>0);
	return std::make_tuple(std::move(buffer), bufferSize);
}
void ResourceFile::Close()
{
	AAsset_close(mFp);
}
void ResourceFile::Open(const char *file, const char * /*mode*/ )
{
	mFp = AAssetManager_open(mAssetManager, file, AASSET_MODE_RANDOM);
	std::string msg("trying to loads " );
	msg += file;
	msg += "\n";
	GCLAssertMsg(mFp != nullptr, msg.c_str());
}


bool ResourceFile::Exists(const char *filename)
{
	AAsset* fp = AAssetManager_open(mAssetManager, filename, AASSET_MODE_RANDOM);

	if (fp != nullptr)
	{
		AAsset_close(fp);
		return true;
	}
	return false;
}
void ResourceFile::RegisterAssetManager(AAssetManager* mgr)
{
	mAssetManager = mgr;
}
//============================================================================
#endif
