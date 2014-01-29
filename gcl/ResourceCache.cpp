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

#include "gcl/ResourceCache.h"
#include <cstring>

#include "gcl/Assert.h"
#include "gcl/Hash.h"
#include "gcl/Resource.h"
#include "gcl/TypeData.h"

using namespace GCL;

void ResourceCache::FlushCache()
{
	for (iResourceCache::iterator it = mNotInUseResource.begin(); it != mNotInUseResource.end(); ++it)
	{
		Resource *tempResource = it->second;
		Free(tempResource);
	}

	mNotInUseResource.clear();
}
ResourceCache::~ResourceCache()
{
	mInUseResources.clear();
	mNotInUseResource.clear();
}

const Resource * ResourceCache::LoadResource( const char *fileName )
{
	//hash the name for faster search in the tree
	uint32_t fileNameHash = Hash::DJB(fileName, strlen(fileName));

	//check if we have the resource in our ResourceManager
	iResourceCache::iterator it = mInUseResources.find(fileNameHash);
	if (it != mInUseResources.end())
	{
		++it->second->mRefCount;
		return it->second;
	}
	it = mNotInUseResource.find(fileNameHash);
	if (it != mNotInUseResource.end())
	{
		Resource *tempResource = it->second;
		mInUseResources[fileNameHash] = tempResource;
		mNotInUseResource.erase(it);
		++tempResource->mRefCount;
		return tempResource;
	}
	//if we don't then load the resource
	Resource *newResource = Allocate(fileName);
	mInUseResources[fileNameHash] = newResource;
	return newResource;
}

//reduce the ref count
void ResourceCache::ReleaseResource( const Resource *resource )
{
	for (iResourceCache::iterator it = mInUseResources.begin(); it != mInUseResources.end(); ++it)
	{
		Resource *tempResource = it->second;
		if (tempResource == resource)
		{
			--tempResource->mRefCount;
			GCLAssert((long)(resource->mRefCount)>=0); //if we get a ref count of -1, something went really wrong;
			if (resource->mRefCount == 0)
			{
				mNotInUseResource[it->first] = it->second;
				//Free(tempResource);
				mInUseResources.erase(it);
			}
			return;
		}
	}
	GCLAssertMsg(false, "we released a texture that didnt exist.");
}

