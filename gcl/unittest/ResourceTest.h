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

#include <gcl/UnitTest.h>
#include <gcl/Resource.h>
#include <gcl/ResourceManager.h>

#include <fstream>

using namespace GCL;

namespace ResourceTest
{
class MyResource : public Resource
{
public:
	MyResource(const char * filename)
	: Resource()
	{
		std::string path = Resource::GetResourcePath();
		path += filename;

		std::string msg("trying to loads " );
		msg += path.c_str();
		msg += "\n";

		std::fstream fp(path.c_str(), std::fstream::binary|std::fstream::in);
		GCLAssertMsg(fp.is_open() && fp.good(), msg.c_str());
		//load file here
		fp.close();
	}
	~MyResource(){}

	static const MyResource EmptyResourceInstance;
private:

};


class MyResourceManager : public ResourceManager
{
public:
	static void Initialize()
	{
		GCLAssert(smpInstance == NULL);
		smpInstance = new MyResourceManager();
	}
	static void Terminate()
	{
		GCLAssert(smpInstance != NULL);
		delete smpInstance;
		smpInstance = NULL;
	}
	static MyResourceManager &Instance()
	{	GCLAssert(smpInstance != NULL);return *smpInstance;}

	Resource *Allocate(const char * filename)
	{
		return new MyResource(filename);
	}
	void Free(Resource * resource)
	{
		delete resource;
	}

private:
	static MyResourceManager *smpInstance;

	MyResourceManager() {}
};
MyResourceManager *MyResourceManager::smpInstance = NULL;




void Test()
{
	TEST_START

	MyResourceManager::Initialize();

	MyResourceManager &textureResourceManager = MyResourceManager::Instance();
	const Resource *tgaResource;
	tgaResource = textureResourceManager.LoadResource(TEXTURE_PATH"mushroomtga.tga");
	Assert_Test(tgaResource);
	const Resource *tgaResource2;
	tgaResource2 = textureResourceManager.LoadResource(TEXTURE_PATH"mushroomtga.tga");
	Assert_Test(tgaResource2);
	Assert_Test(tgaResource == tgaResource2);

	textureResourceManager.ReleaseResource(tgaResource2);
	textureResourceManager.ReleaseResource(tgaResource);

	MyResourceManager::Terminate();
}
}
