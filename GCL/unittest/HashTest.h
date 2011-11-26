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

#include <GCL/UnitTest.h>
#include <GCL/Hash.h>

using namespace GCL;
namespace HashTest
{

void Test()
{
	TEST_START
	uint32_t djbhash1 = Hash::DJB("Some Value");
	Assert_Test(djbhash1==1321329526);
	uint32_t djbhash2 = Hash::DJB("Some Value", 4);
	Assert_Test(djbhash2==2089580953);

	Hash::MD5Hash md5hash1 = Hash::MD5("Some Value");
	const uint8_t md5TestHash1[] = {84,219,41,105,93,58,89,248,121,162,29,220,11,160,99,73};
	Assert_Test(memcmp(md5hash1.digest, md5TestHash1, 16)==0);
	Hash::MD5Hash md5hash2 = Hash::MD5("Some Value", 4);
	const uint8_t md5TestHash2[] = {105,92,106,228,19,192,4,70,115,61,146,108,202,222,253,139};
	Assert_Test(memcmp(md5hash2.digest, md5TestHash2, 16)==0);
}
}
