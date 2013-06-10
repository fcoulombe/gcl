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

#include <sstream>

#include <gcl/UnitTest.h>

#include <gcl/Memory.h>

using namespace GCL;
namespace MemoryTest
{
void Test();
void Test()
{
	TEST_START
	std::stringstream s;

	{
		Assert_Test(Memory::Align32(1) == 4);
		Assert_Test(Memory::Align32(4) == 4);


		Assert_Test(Memory::Align64(1) == 8);
		Assert_Test(Memory::Align64(4) == 8);
		Assert_Test(Memory::Align64(8) == 8);

		size_t ali = Memory::Align(1);

#if USE_64BIT_PLATFORM
		Assert_Test(ali == 8);
#else
		Assert_Test(ali == 4);
#endif
	}
}
}
