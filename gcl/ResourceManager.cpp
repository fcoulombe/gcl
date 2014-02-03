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

#include "gcl/ResourceManager.h"
#include <cstring>

#include "gcl/Assert.h"
#include "gcl/Config.h"
#include "gcl/Hash.h"
#include "gcl/Resource.h"
#include "gcl/StringUtil.h"
#include "gcl/TypeData.h"

using namespace GCL;
class ResourcePaths
{
public:
	ResourcePaths()
	{
		if (Config::Instance().HasString("RESOURCE_PATH"))
		{
			const std::string &resourcePaths = Config::Instance().GetString("RESOURCE_PATH");
			StringUtil::Explode(resourcePaths, mResourcePaths, ';');
		}
	}
	const std::string GetFullPath(const char *filename) const
	{
		for (size_t i=0; i<mResourcePaths.size(); ++i)
		{
			std::string fullPath = mResourcePaths[i] + "/" + filename;
			if (GCLFile::Exists(fullPath.c_str()))
				return fullPath;
		}
		return filename;
	}
private:
	std::vector<std::string> mResourcePaths;
};
ResourcePaths PATH;
ResourceManager::~ResourceManager()
{
	mResourceCache.clear();
}

const Resource * ResourceManager::LoadResource( const char *fileName )
{
	//hash the name for faster search in the tree
	uint32_t fileNameHash = Hash::DJB(fileName, strlen(fileName));

	//check if we have the resource in our ResourceManager
	ResourceCache::iterator it = mResourceCache.find(fileNameHash);
	if (it != mResourceCache.end())
	{
		++it->second->mRefCount;
		return it->second;
	}
	
	//if we don't then load the resource
	std::string fullpath = PATH.GetFullPath(fileName);
	Resource *newResource = Allocate(fullpath.c_str());
	mResourceCache[fileNameHash] = newResource;
	return newResource;
}

//reduce the ref count
void ResourceManager::ReleaseResource( const Resource *resource )
{
	for (ResourceCache::iterator it = mResourceCache.begin(); it != mResourceCache.end(); ++it)
	{
		Resource *tempResource = it->second;
		if (tempResource == resource)
		{
			--tempResource->mRefCount;
			GCLAssert((long)(resource->mRefCount)>=0); //if we get a ref count of -1, something went really wrong;
			if (resource->mRefCount == 0)
			{
				Free(tempResource);
				mResourceCache.erase(it);
			}
			return;
		}
	}
	GCLAssertMsg(false, "we released a texture that didnt exist.");
}

