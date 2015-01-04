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

#include <thread>
#include <atomic>
#include <map>
#include <exception>
namespace GCL
{
	template <typename T>
	class LockFreeQueue
	{
	private:
		struct Node 
		{
			Node( T val )
				: value(val), next(nullptr) { }
			T value;
			Node* next;
		};
		Node* first;             // for producer only
		std::atomic<Node*> divider, last;         // shared
	public:
		LockFreeQueue() 
		{
			first = divider = last = new Node( T() );           // add dummy separator
		}
		~LockFreeQueue() 
		{
			while( first != nullptr ) 
			{   // release the list
				Node* tmp = first;
				first = tmp->next;
				delete tmp;
			}
		}
		void Push( const T& t )
		{
			last->next = new Node(t);    // add the new item
			last  = last->next;      // publish it
			while( first != divider )
			{ // trim unused nodes
				Node* tmp = first;
				first = first->next;
				delete tmp;
			}
		}
		bool Pop( T& result ) 
		{
			if( divider != last ) 
			{         // if queue is nonempty
				result = divider->next->value;  // C: copy it back
				divider = divider->next;   // D: publish that we took it
				return true;              // and report success
			}
			return false;               // else report empty
		}
	};

	class Thread;
	class ThreadManager
	{
	public:
		static void RegisterThread(Thread *t);
		static void UnRegisterThread(Thread *t);
		//should only be called by child thread
		static void Throw(std::exception_ptr e)
		{
			FatalExceptionTransfer = e;
		}
		static void Join(std::thread::id threadId);
		//should only be called by main thread
		static void ReThrowException()
		{
			if( FatalExceptionTransfer!=nullptr )
			{
				KillAllThreads();
				std::rethrow_exception(FatalExceptionTransfer);
			}
		}
		static void ClearException();
		static void KillAllThreads();
	private:
		typedef std::map<std::thread::id, Thread *> ThreadList;
		static ThreadList mThreadMap;
		static std::exception_ptr FatalExceptionTransfer;
	};
}
