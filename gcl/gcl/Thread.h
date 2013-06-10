/*
 * Copyright (C) 2013 by Francois Coulombe
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


namespace GCL
{

	class Thread
	{
	public:
		Thread()
		{

		}
		void Start()
		{
			mThreadHandle = CreateThread(
				NULL,                   // default security attributes
				0,                      // use default stack size
				ThreadHelper,       // thread function name
				this,          // argument to thread function
				0,                      // use default creation flags
				&mThreadId);   // returns the thread identifier
		}

		void Join()
		{
			WaitForSingleObject(mThreadHandle,INFINITE);
		}
		virtual ~Thread()
		{
			 CloseHandle(mThreadHandle);
		}
		virtual void Run()=0;
	private:
		static DWORD WINAPI ThreadHelper( LPVOID lpParam )
		{
			Thread *myThreadObject = (Thread *)lpParam;
			myThreadObject->Run();
			return 0;
		}

		DWORD   mThreadId;
		HANDLE mThreadHandle;
	};


}
