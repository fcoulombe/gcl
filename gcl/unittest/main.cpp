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
#include <sstream>
#ifdef USE_VLD
#include <vld.h>
#endif

#include <gcl/Assert.h>
#include <gcl/Circle.h>
#include <gcl/Complex.h>
#include <gcl/Config.h>
#include <gcl/Curve.h>
#include <gcl/Exception.h>
#include <gcl/FixedPoint.h>
#include <gcl/Macro.h>
#include <gcl/Math.h>
#include <gcl/Matrix33.h>
#include <gcl/Matrix43.h>
#include <gcl/Matrix44.h>
#include <gcl/Memory.h>
#include <gcl/Point2.h>
#include <gcl/Point3.h>
#include <gcl/Point4.h>
#include <gcl/Quaternion.h>
#include <gcl/File.h>
#include <gcl/Pixel.h>
#include <gcl/PixelBuffer.h>
#include <gcl/Resource.h>
#include <gcl/ResourceManager.h>
#include <gcl/Sphere.h>
#include <gcl/Time.h>
#include <gcl/Thread.h>
#include <gcl/TypeData.h>
#include <gcl/UnitTest.h>
#include <gcl/WorldUnit.h>
#include <gcl/WorkerThread.h>

#include "AssertTest.h"
#include "ConfigTest.h"
#include "CurveTest.h"
#include "ExceptionTest.h"
#include "FileLoadingTest.h"
#include "HashTest.h"
#include "MathTest.h"
#include "Matrix44Test.h"
#include "MemoryTest.h"
#include "PathTest.h"
#include "PixelTest.h"
#include "PixelBufferTest.h"
#include "PngLoadingTest.h"
#include "Point2Test.h"
#include "Point3Test.h"
#include "Point4Test.h"
#include "RawLoadingTest.h"
#include "ResourceTest.h"
#include "SafeCastTest.h"
#include "StringUtilTest.h"
#include "TgaLoadingTest.h"
#include "ThreadTest.h"
#include "TimeTest.h"
#include "WarningTest.h"
#include "WorkerThreadTest.h"

using namespace GCL;
int main(int argc, char **argv)
{
	SUITE_INIT(argc, argv)
		WarningTest::Test();
		ExceptionTest::Test();
		AssertTest::Test();
		SafeCastTest::Test();
		HashTest::Test();
		MathTest::Test();
		StringUtilTest::Test();
		TimeTest::Test();
		PathTest::Test();
		MemoryTest::Test();

		Point2Test::Test();
		Point3Test::Test();
		Point4Test::Test();

		Matrix44Test::Test();

		CurveTest::Test();

		FileLoadingTest::Test();
		ResourceTest::Test();
		PixelTest::Test();
		PixelBufferTest::Test();
		RawLoadingTest::Test();
		TgaLoadingTest::Test();
		PngLoadingTest::Test();
        ConfigTest::Test();
        ThreadTest::Test();
		WorkerThreadTest::Test();

		SUITE_TERMINATE
	return 0;
}
