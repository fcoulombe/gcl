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

#include <string>
#include <thread>
#ifdef OS_WIN32
#define USE_WINDOWS_QUEUE 1
#else
#define USE_WINDOWS_QUEUE 0
#endif
#if USE_WINDOWS_QUEUE
#include <concurrent_queue.h>
#else
#include <readerwriterqueue.h>
#endif
#include <mutex>
#include <condition_variable>

namespace GCL
{
typedef std::function<void(void)> Command;
#if USE_WINDOWS_QUEUE
typedef Concurrency::concurrent_queue<Command> CommandQueue;
#else
typedef moodycamel::ReaderWriterQueue<Command> CommandQueue;

#endif
	class WorkerThread
	{
	public:
	WorkerThread(const std::string& name);
		~WorkerThread();

		void SendCommandAsync(Command& cmd);
		void SendCommandAsync(const Command& cmd);
		void SendCommandSync(const Command& cmd);

		void Flush();
#if USE_WINDOWS_QUEUE
		bool IsEmpty() const { return mCommandQueue.empty(); }
#else
		bool IsEmpty() const { return mCommandQueue.peek() == nullptr; }
#endif
	private:
		void Update();

		std::string mName;
		CommandQueue mCommandQueue;

		bool mKeepProcessing;
		bool mWorkFinished;

		std::mutex mMutex;
		std::thread mThread;
		std::condition_variable mRunMutex;
	};
}

