#include "QueueADT.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename E> class PriorityQueue :  Queue<E>
{
private:

	E *items;
	unsigned int count = 0;
	int size = 10;// number of items
	bool(*compareFunction)(E, E);
	// Protect assignment
	void operator =(const PriorityQueue&) 
	{
	
	}; 
	// Protect copy constructor
	PriorityQueue(const PriorityQueue&)
	{
	
	}; 
	// Intialization helper method
	void init() 
	{  
		this->items = new E[size]();
		this->count = 0;
	}
	void removeall()
	{ // Return link nodes to free store
		
	}

	int largestChild(int index)
	{
		if (count == 1)//no children
		{
			return index;
		}
		else if((index * 2 + 1) <= count) // two children
		{
			E lChild = items[index * 2];
			E rChild = items[index * 2 + 1];
			if (lChild > rChild && lChild > items[index])//left child greater
			{
				return (index * 2);
			}
			else if (rChild > items[index])//right child greater
			{
				return (index * 2 + 1);
			}
			else//no child greater
			{
				return index;
			}
			
		}
		else//one child
		{
			return items[index * 2] > items[index] ? (index * 2) : (index);
		}
	}
public:
	
	// takes a function pointer to a compare function
	// as a Parameter
	PriorityQueue(bool(*func)(E, E))
	{
		compareFunction = func;
		init();
	
	} 

	// Print queue contents
	void print() const
	{
		for (int i = 0; i < count; i++)
		{
			cout << items[i] << endl;
		}

	};

	// Base destructor
	 ~PriorityQueue() 
	 {
	 
	 } 
	// Reinitialize the queue. The user is responsible for
	// reclaiming the storage used by the queue elements.
	 void clear()
	 {
		 count = 0;
	 };	 
	// Place an element at the position 
	// based on its prioity of the queue.
	// it: The element being enqueued.
	 void enqueue(const E& it)
	 {

		 if (count + 1 >= size)
		 {
			 E *temp = new E[size * 2];

			 for (int i = 0; i < size; i++)
			 {
				 temp[i] = items[i];
			 }
			 size = size * 2;
			 delete[] items;
			 items = temp;
		 }

		 items[count + 1] = it;
		 count++;

		 int index = count;
		 while (index != 1)
		 {
			 if (compareFunction(items[index], items[index / 2]))
			 {
				 swap(items[index], items[index / 2]);

			 }
			 index = index / 2;
		 }
	 };


	
	 
	// Remove and return element at the front of the queue.
	// Return: The element at the front of the queue.
	 E dequeue()
	 {
		 if (count == 0)
		 {
			 throw out_of_range("Empty Queue");
		 }
		 
		
		 int index = 1;
		 E copy = items[index];

		 items[index] = items[count];
		 count--;
		 
		 while (index <= (count/2))
		 {
			 if (largestChild(index) != index)//swaps parent with largest child
			 {
				 swap(items[index], items[largestChild(index)]);
				
				 //if ((index/2) >= 1 && largestChild(index/2) != (index/2))//checks to see if childs parent is still largest
				 //{
					// swap(items[index / 2], items[largestChild(index / 2)]);
					// 
				 //}
			 }
			 index++;				 
		 }
		 return copy;
	 };
	// Return: A copy of the front element.
	 const E& frontValue() const
	 {
		 return items[1];
		
	 }
	// Return: The number of elements in the queue.
	 int length() const
	 {
		 return count;
	 }
};