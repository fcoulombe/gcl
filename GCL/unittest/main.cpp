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
#include <iostream>

#include <GCL/Assert.h>
#include <GCL/Circle.h>
#include <GCL/Complex.h>
#include <GCL/FixedPoint.h>
#include <GCL/Macro.h>
#include <GCL/Math.h>
#include <GCL/Matrix33.h>
#include <GCL/Matrix43.h>
#include <GCL/Matrix44.h>
#include <GCL/Point2.h>
#include <GCL/Point3.h>
#include <GCL/Point4.h>
#include <GCL/Quaternion.h>
#include <GCL/Sphere.h>
#include <GCL/TypeData.h>
#include <GCL/UnitTest.h>
#include <GCL/WorldUnit.h>

#include "Point3Test.h"
#include "Matrix44Test.h"


int main()
{

	Matrix44Test::Test();
	Point3Test::Test();

	return 0;
}
