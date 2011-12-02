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

//Process* create(int size, int tp); //function to create an array of processes

void firstFit(Process* p, int ptprob, int npprob);	//First Fit Algorithm
void bestFit(Process* p, int ptprob, int npprob);	//Best Fit Algorithm
void nextFit(Process* p, int ptprob, int npprob);	//Next Fit Algorithm
void worstFit(Process* p, int ptprob, int npprob);	//Worst Fit Algorithm

bool enterProbability(int prob);
void printMem(); //function to print main memory

int charArrLoc = 0; //counter for the ASCII character 
int asciiChar[58]; 
char mainMem[2400]; //1-dimentional character array, main memory
int used = ros;

int main(int argc, char * argv[])
{
	int ptp, npp, i, j;

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

	Process* processes = new Process[58];	//create an array of Process
	
	//create and assign 20 processes into memory
	for (int i = 0; i < 20; i++)
	{
		int w = nextProcessChar();
		int amount = rand() % 90 + 10;
		Process p(i+65, amount, used, ptp);
		processes[i] = p;
		for (j = 0; j < amount; j++)
		{
			mainMem[j+used] = w;
		}
		//used += amount;
	}

	//print out main memory
	printMem();

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

	system("pause");
	return 0;
}

/*Process* create(int tp)
{
	Process* arr = new Process[size];

	int amount = rand() % 90 + 10;
	Process p(i+65, amount, 0, tp);
	arr[i] = p;

	return arr;
}*/

bool enterProbability(int prob){ 
	// RANDOM NUMBER CRAP
	int random = rand() % 99 + 1; 
	//If the number is within the probability return true
	if(random < prob) 
	{ 
		return true; 
	}
	else
	{ 
		return false; 
	} 
}

int nextProcessChar(){ 
	int outOfMemory = 0;
	while(outOfMemory < 58)
	{
		if( charArrLoc != 58 ) 
		{ 
			if( charArrLoc == 0 && asciiChar[charArrLoc] != 1)
			{
				asciiChar[charArrLoc] = 1; 
				charArrLoc++;
				return 65;
			}
			else if( asciiChar[charArrLoc] != 1 ) 
			{ 
				int temp; 
				asciiChar[charArrLoc] = 1;
				temp = charArrLoc +65; 
				charArrLoc++;
				return temp; 
			}
			else
			{
				charArrLoc++; 
			} 
		}
		else
		{
			charArrLoc = 0; 
		}
		outOfMemory++;
	}
	return -1; //if -1 is returned the program is out of memory therefore it should terminate 
}

void firstFit(Process* p, int ptprob, int npprob)
{
	char input;
	cin >> input; 
	while( input != 'q' )
	{
		if (input == 'c')
		{
			if(enterProbability(npprob) == true)
			{ 
				int k = nextProcessChar();
				cout << "k = " << k << endl;
				int random = rand() % 99 + 1;
				Process newProcess(k+65, random, used, ptprob); 
				for (int i = used; i < random; i++)
				{
					cout << "hey!!1" << endl;
					mainMem[i] = k;
				}
				//create a new process
				//then restart loop
				printMem();
			}
			cin >> input;
		}j
		else
		{
			cout << "Can not understand your request!" << endl;
			cin >> input;
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
	cout << "*********************************" << endl;
}