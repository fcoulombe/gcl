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
#include <gcl/SafeCast.h>

using namespace GCL;
namespace SafeCastTest
{


  class A
  {
  public:
    virtual ~A() {}
    int bleh;

  };

  class B : public A
  {

  };

  class C : public A
  {

  };

    void Test();
  void Test()
  {
	  TEST_START
    {
      A* a = new B();
      B *b= safe_cast<B*>(a);
      (void)b;
      delete a;
    }
    A* a=NULL;
    try
    {
      a = new C();
      B *b= safe_cast<B*>(a);
      (void)b;
    }
    catch (GCLException& e)
    {
    	if (a)
    		delete a;
        const char *testString = "t you are trying to up cast in the wrong type. this is very dangerous";
        Assert_Test(strncmp(e.message(), testString, strlen(testString)) == 0 );
    }


  }
}
