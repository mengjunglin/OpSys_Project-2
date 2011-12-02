// Operating System FALL2011
// Project #2 - Memory Management Simulation System
// Tiffany Milano & Meng Jung Lin
// Finalize Date: 12/09/2011

#include <iostream>
#include <string.h>
#include <time.h>
#include "mem.h"
using namespace std;

#define ros 80

Process* create(int size, int tp); //function to create an array of processes

void firstFit(Process* p, int ptprob, int npprob);	//First Fit Algorithm
void bestFit(Process* p, int ptprob, int npprob);	//Best Fit Algorithm
void nextFit(Process* p, int ptprob, int npprob);	//Next Fit Algorithm
void worstFit(Process* p, int ptprob, int npprob);	//Worst Fit Algorithm

bool enterProbability(int prob);

void printMem(); //function to print main memory

char mainMem[2400]; //1-dimentional character array, main memory

int main(int argc, char * argv[])
{
	int used = ros, ptp, npp, i, j;

	if (argc != 4)
	{
		cout << "USAGE: memsim { first | best | next | worst } <process-termination-probability> <new-process-probability>" << endl;
		system("pause");
		return 0;
	}

	ptp = (int)argv[2]; //process-termination-probability = argv[2]
	npp = (int)argv[3]; //new-process-probability = argv[3]

	//initialize main memory
	for (i = 0; i < 2400; i++)
	{
		if (i < ros)
			mainMem[i] = '#';
		else
			mainMem[i] = '.';
	}

	srand(time(NULL)); //set seed to get random numbers

	Process* processes;	//create an array of Process
	//processes = create(20, ptp); //20 random amount of memory cells

	//assign into main memory
	for (i = 0; i < 20; i++)
	{
		for(j = 0; j < processes[i].getCellRequired(); j++)
		{
			mainMem[j+used] = processes[i].getProcName();
		}
		used += processes[i].getCellRequired();
	}

	if (strcmp(argv[1],"first") == 0)
	{
		//running first fit algo
		firstFit(processes, ptp, npp);
	}
	else if (strcmp(argv[1],"best") == 0)
	{
		//running best fit algo
		bestFit(processes, ptp, npp);
	}
	else if (strcmp(argv[1],"next") == 0)
	{
		//running next fit algo
		nextFit(processes, ptp, npp);
	}
	else if (strcmp(argv[1],"worst") == 0)
	{
		//running worst fit algo
		worstFit(processes, ptp, npp);
	}
	else
	{
		cout << "Can not identify the algorithm." << endl;
		cout << "USAGE: memsim { first | best | next | worst } <process-termination-probability> <new-process-probability>" << endl;

		system("pause");
		return 0;
	}

	//print out main memory
	printMem();

	system("pause");
	return 0;
}

Process* create(int size, int tp)
{
	Process* arr = new Process[size];

	//srand(time(NULL));

	for (int i = 0; i < size; i++)
	{
		int amount = rand() % 90 + 10;
		Process p(i+65, amount, 0, tp);
		arr[i] = p;
	}
	return arr;
}

bool enterProbability(int prob){ 
	// RANDOM NUMBER CRAP
	rand = randomNumber; 
	//If the number is within the probability return true
	if(rand < prob) 
	{ 
		return true; 
	}
	else
	{ 
		return false; 
	} 
}

void firstFit(Process* p, int ptprob, int npprob)
{
	while(somethingOrOther)
	{
		if(enterProbability(npprob))
		{ 
			//create a new process
			//then restart loop
		}
		else
		{ 
			//restart loop
		}
	}
}

void bestFit(Process* p, int ptprob, int npprob)
{
	enterProbability(npprob);
}

void nextFit(Process* p, int ptprob, int npprob)
{
	enterProbability(npprob);
}

void worstFit(Process* p, int ptprob, int npprob)
{
	enterProbability(npprob);
}

void printMem()
{
	for (int i = 0; i < 2400; i++)
		cout << mainMem[i];
}