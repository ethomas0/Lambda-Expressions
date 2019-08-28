#include "stdafx.h"
#include "PriorityQueue.h"
#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <algorithm>
#include <random>
#include <sstream>
#include <fstream>
#include "Process.h"


vector<string> split(const string &s, char delim) {
	stringstream ss(s);
	string item;
	vector<string> tokens;
	while (getline(ss, item, delim)) {
		tokens.push_back(item);
	}
	return tokens;
}

vector<Process*> load(const string &filename) {
	vector<Process*> list;
	std::ifstream file(filename);

	std::string str;
	while (std::getline(file, str))
	{
		vector<string> tokens = split(str, ',');
		
		list.push_back(new Process(tokens[0], stoi(tokens[1]) , stoi(tokens[2]), static_cast<Process::PriorityLevel>(stoi(tokens[3]))));
	}
		
	return list;
}
bool compare(int first, int second)
{
	return (first  > second);
}

bool compareProcess(Process* first, Process* second)
{
	return (first->getPriorityLevel()  > second->getPriorityLevel());
}


int _tmain(int argc, _TCHAR* argv[])
{

	srand(time(NULL));
	int random = 0;
	//Random Numbers
	PriorityQueue<int> pq([](int first, int second)
	{
		return (first  > second);
	});

	for (int x = 0; x < 10; x++)
	{
		random = rand() % 10 + 1;
		cout << random << " " ;
		pq.enqueue(random);
	}
	std::cout << std::endl;

	for (int x = 0; x < 10; x++)
		std::cout << pq.dequeue() << " ";
	std::cout << std::endl;
	
	//Process with Function Pointer
	vector<Process*> processes = load("ProcessList.txt");
	for (Process* process : processes) // access by reference to avoid copying
	{
		cout << (*process) << endl ;
	}
	cout << endl;
	//Process Queue with Function Pointer
	PriorityQueue<Process*> processq(&compareProcess);
	for (Process* process : processes) // access by reference to avoid copying
	{
		processq.enqueue(process);
	}
	cout << endl;

	std::cout << " Start DEQUEUE processq " << endl;
	while (processq.length() > 0)
	{
		std::cout << processq.length() << " ";
		std::cout << *(processq.dequeue()) << " ";
		std::cout << std::endl;
	}


	//Process Queue with Lamda
	PriorityQueue<Process*> processqLambda([](Process* first, Process* second)
	{
		return (first->getPriorityLevel()  > second->getPriorityLevel());
	});
	

	for (Process* process : processes) // access by reference to avoid copying
	{
		processqLambda.enqueue(process);
	}
	cout << endl;

	std::cout << " Start DEQUEUE processqLambda " << endl ;
	while (processqLambda.length() > 0)
	{
		std::cout << processqLambda.length() << " ";
		std::cout << *(processqLambda.dequeue()) << " ";
		std::cout << std::endl;
	}
	system("pause");
	// Part 2 A prioritize by ID 
	PriorityQueue<Process*> processqLambdaID([](Process* first, Process* second)
	{
		return (first->getID()  > second->getID());
	});

	// Part 2 B prioritize by PriorityLevel Reverse 
	PriorityQueue<Process*> processqLambdaIDReverse([](Process* first, Process* second)
	{
		return (first->getPriorityLevel()  < second->getPriorityLevel());
	});

	// Part 2 C prioritize by Size Large to small
	PriorityQueue<Process*> processqLambdaSize([](Process* first, Process* second)
	{
		return (first->getSize()  > second->getSize());
	});

	// Part 2 D prioritize by Name as in Dictionary
	PriorityQueue<Process*> processqLambdaName([](Process* first, Process* second)
	{
		return (first->getName()  > second->getName());
	});

	// Part 2 E prioritize by Name Reverse Dictionary
	PriorityQueue<Process*> processqLambdaNameReverse([](Process* first, Process* second)
	{
		if (first->getPriorityLevel() == Process::PriorityLevel::Critical && second->getPriorityLevel() == Process::PriorityLevel::Critical)
		{
			return (first->getPriorityLevel() > second->getPriorityLevel());
		}
		else if (first->getPriorityLevel() == Process::PriorityLevel::Critical && second->getPriorityLevel() != Process::PriorityLevel::Critical)
		{
			return (first->getPriorityLevel() > second->getPriorityLevel());
		}
		else if (first->getPriorityLevel() != Process::PriorityLevel::Critical && second->getPriorityLevel() != Process::PriorityLevel::Critical)
		{
			return (first->getPriorityLevel() < second->getPriorityLevel());
		}

		if (first->getPriorityLevel() == Process::PriorityLevel::Critical && second->getPriorityLevel() == Process::PriorityLevel::High)
		{
			return (first->getPriorityLevel() > second->getPriorityLevel());
		}
		else if (first->getPriorityLevel() == Process::PriorityLevel::Critical && second->getPriorityLevel() != Process::PriorityLevel::High)
		{
			return (first->getPriorityLevel() > second->getPriorityLevel());
		}
		else if (first->getPriorityLevel() != Process::PriorityLevel::Critical && second->getPriorityLevel() != Process::PriorityLevel::High)
		{
			return (first->getPriorityLevel() < second->getPriorityLevel());
		}
		else
		{
			return (first->getPriorityLevel() > second->getPriorityLevel());
		}
	});

	// Part 2 F prioritize by PriorityLevel Critcal then High ALL others equal
	
	return 0;
}
