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

#include <sstream>

#include <gcl/UnitTest.h>

#include <gcl/AABox.h>

using namespace GCL;
namespace AABoxTest
{
void Test();
void Test()
{
	TEST_START
	std::stringstream s;
	AABox box(1.,2.,3.);
	Assert_Test(box.GetMin() == WorldPoint3(-0.5, -1., -1.5));
	Assert_Test(box.GetMax() == WorldPoint3(0.5, 1., 1.5));

	Assert_Test(box.GetWidth() == 1.);
	Assert_Test(box.GetHeight() == 2.);
	Assert_Test(box.GetLength() == 3.);
	box.SetOrigin(10.0, 0.0, 0.0);
	Assert_Test(box.GetMin() == WorldPoint3(-0.5+10.0, -1., -1.5));
	Assert_Test(box.GetMax() == WorldPoint3(0.5+10.0, 1., 1.5));
	box.SetOrigin(0.0, 0.0, 0.0);

	AABox box2(0.5, 1., 1.5);
	Assert_Test(box.IsIntersecting(box2) == true);
	box2.SetOrigin(10.0, 0.0, 0.0);
	Assert_Test(box.IsIntersecting(box2) == false);


	Assert_Test(AABox(1.,2.,3.) == AABox(1.,2.,3.));
}
}
