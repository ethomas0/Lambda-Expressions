#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Queue/PriorityQueue.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PQueueUnitTest
{
	bool compareGreater(int first, int second)
	{
		return (first  > second);
	}
	
	TEST_CLASS(TestPQueueWithComparisonMethod)
	{
	public:
		

		void static dequeueEmptyList()
		{
			PriorityQueue<int> pq(compareGreater);
			pq.dequeue();
		}
		
		TEST_METHOD(DequeueEmptyList)
		{

			Assert::ExpectException<std::out_of_range>(&TestPQueueWithComparisonMethod::dequeueEmptyList, L"Exception not thrown on dequeue with Empty List");

		}

		void static fronValueEmptyList()
		{
			PriorityQueue<int> pq(compareGreater);
			pq.frontValue();
		}

		TEST_METHOD(FrontValueEmptyList)
		{
			
			Assert::ExpectException<std::out_of_range>(&TestPQueueWithComparisonMethod::dequeueEmptyList, L"Exception not thrown on frontValue with Empty List");

		}
		TEST_METHOD(EqueueEmptyList)
		{
			PriorityQueue<int> pq(compareGreater);
			pq.enqueue(1);
			Assert::AreEqual(1, pq.frontValue(), L" New Element not at Front on Empty List");

		}
		TEST_METHOD(EqueueHighestPriorityItemsOnList)
		{
			PriorityQueue<int> pq(compareGreater);
			pq.enqueue(3);
			pq.enqueue(12);
			pq.enqueue(5);
			pq.enqueue(1);
			// higest priority item 
			// enqueued last
			pq.enqueue(19);
			Assert::AreEqual(19, pq.frontValue(), L" New Higher priority element not at Front on Empty List");


		}
		TEST_METHOD(EqueueHighestPriorityOneItemOnList)
		{
			PriorityQueue<int> pq(compareGreater);
			pq.enqueue(3);
			pq.enqueue(12);

			Assert::AreEqual(12, pq.frontValue(), L" New Higher priority element not at Front on Empty List");
			Assert::AreEqual(12, pq.dequeue(), L" New Higher priority element not at Front on Empty List");
			Assert::AreEqual(3, pq.dequeue(), L" New Higher priority element not at Front on Empty List");

		}
		TEST_METHOD(EqueueItemInMiddleOfItemsOnList)
		{
			PriorityQueue<int> pq(compareGreater);
			pq.enqueue(12);
			pq.enqueue(3);
			pq.enqueue(5);
			// middle priority item 
			// enqueued last
			Assert::AreEqual(12, pq.frontValue(), L" Highest priority element not at Front");
			Assert::AreEqual(12, pq.dequeue(), L" Dequeue Highest priority element not Correct");
			Assert::AreEqual(5, pq.dequeue(), L" Dequeue Middle priority element not Correct");
			Assert::AreEqual(3, pq.dequeue(), L" Dequeue lowest priority element not at Front on Empty List");


		}
		TEST_METHOD(EqueueLowestPriorityItemsOnList)
		{
			PriorityQueue<int> pq(compareGreater);
			pq.enqueue(3);
			pq.enqueue(1);
			// lowest priority item 
			// enqueued last

			Assert::AreEqual(3, pq.dequeue(), L" New Higher priority element not at Front on Empty List");
			Assert::AreEqual(1, pq.frontValue(), L" New Higher priority element not at Front on Empty List");

		}

		TEST_METHOD(DeueueAllItemsOnList)
		{
			PriorityQueue<int> pq(compareGreater);
			pq.enqueue(3);
			pq.enqueue(12);
			pq.enqueue(5);
			pq.enqueue(1);
			pq.enqueue(19);
			Assert::AreEqual(19, pq.dequeue(), L" New Higher priority element not at Front on Empty List");
			Assert::AreEqual(12, pq.dequeue(), L" New Higher priority element not at Front on Empty List");
			Assert::AreEqual(5, pq.dequeue(), L" New Higher priority element not at Front on Empty List");
			Assert::AreEqual(3, pq.dequeue(), L" New Higher priority element not at Front on Empty List");
			Assert::AreEqual(1, pq.frontValue(), L" New Higher priority element not at Front on Empty List");


		}
		TEST_METHOD(LengthAfterEnqueue)
		{
			PriorityQueue<int> pq(compareGreater);
			for (int x = 19; x > 0; x--)
			{
				pq.enqueue(x);
			}

			Assert::AreEqual(19, pq.length(), L"Length not correct after enqueue");

		}

		TEST_METHOD(LengthAfterDequeue)
		{
			PriorityQueue<int> pq(compareGreater);
			for (int x = 19; x > 0; x--)
			{
				pq.enqueue(x);
			}
			pq.dequeue();
			pq.dequeue();
			pq.dequeue();
			pq.dequeue();
			Assert::AreEqual(15, pq.length(), L"Length not correct after enqueue");

		}
		TEST_METHOD(LengthAfterDequeueEnqueue)
		{
			PriorityQueue<int> pq(compareGreater);
			for (int x = 19; x > 0; x--)
			{
				pq.enqueue(x);
			}
			pq.dequeue();
			pq.dequeue();
			pq.dequeue();
			pq.dequeue();
			pq.enqueue(19);
			pq.enqueue(18);
			Assert::AreEqual(17, pq.length(), L"Length not correct after enqueue");

		}
	};
}