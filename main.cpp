// Operating System FALL2011
// Project #2 - Memory Management Simulation System
// Tiffany Milano & Meng Jung Lin
// Finalize Date: 12/09/2011

#include <iostream>
#include <string.h>
#include <time.h>
#include <vector>
#include "mem.h"
using namespace std;

#define ros 80

//Process* create(int size, int tp); //function to create an array of processes

//void firstFit(Process* p, int ptprob, int npprob);	//First Fit Algorithm
void firstFit(vector<Process> &p, int ptprob, int npprob);
void bestFit(Process* p, int ptprob, int npprob);	//Best Fit Algorithm
void nextFit(Process* p, int ptprob, int npprob);	//Next Fit Algorithm
void worstFit(Process* p, int ptprob, int npprob);	//Worst Fit Algorithm
void defragmentation(vector<Process> &p);

bool enterProbability(int prob);
int nextProcessChar();
int findFit(int length); //function that find the size of the first empty slot
void printMem(); //function to print main memory
int createProcess(vector<Process> &proc, int pt);

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

	ptp = atoi(argv[2]); //process-termination-probability = argv[2]
	npp = atoi(argv[3]); //new-process-probability = argv[3]

	//initialize main memory
	for (i = 0; i < 2400; i++)
	{
		if (i < ros)
			mainMem[i] = '#';
		else
			mainMem[i] = '.';
	}

	srand(time(NULL)); //set seed to get random numbers

	//Process* processes = new Process[58];	//create an array of Process
	vector <Process> processes;
	
	//create and assign 20 processes into memory
	for (int i = 0; i < 20; i++)
	{
		int check = createProcess(processes, ptp);
		if(check == -1) 
		{ 
			// the program is out of memory so it ends
			cout << "1: ERROR: Process could not be created" << endl; 
			return -1; 
		}
		for (j = 0; j < processes.back().getCellRequired(); j++)
		{
			mainMem[processes.back().getStartPos() + j] = processes.back().getProcName();
		}
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
//		bestFit(processes, ptp, npp);
	}
	else if (strcmp(argv[1],"next") == 0)
	{
		//running next fit algo
//		nextFit(processes, ptp, npp);
	}
	else if (strcmp(argv[1],"worst") == 0)
	{
		//running worst fit algo
//		worstFit(processes, ptp, npp);
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



void firstFit(vector<Process> &p, int ptprob, int npprob)
{
	cout << "ENTER¡@FIRST FIT FUNCTION " << endl;
	char input;
	cin >> input;
	vector<Process> pCopy; 
	//vector<Process>::iterator it;
	while( input != 'q' )
	{
		if (input == 'c')
		{ 
			pCopy.clear(); 
			//Check for terminated processes
			for (int j = 0; j < p.size(); j++)
			{
				if (enterProbability(p[j].getTermProb()) == true)
				{
					for(int r = 0; r < 58; r++) 
					{
						char temp = r + 65;  
						if(temp == p[j].getProcName())
						{
							asciiChar[r] = 0; 
							break;
						}
					}
					for (int m = 0; m < p[j].getCellRequired(); m++)
					{
						mainMem[p[j].getStartPos() + m] = '.';
					}
				}
				else
				{
					pCopy.push_back(p[j]);
				}
			}
			cout << "pCopy size " << pCopy.size() << endl; 
			cout << "p size " << p.size() << endl; 
			if(pCopy.size() != p.size())
			{
				cout << "p = pCopy" << endl; 
				//it = pCopy.begin(); 
				p.clear(); 
				//p.assign(it, pCopy.end() - 1);
				p = pCopy;
				cout << "after p = pCopy call" << endl; 
			}

			//attempt to create new process
			if(enterProbability(npprob) == true)
			{ 
				cout << "creating new processes" << endl; 
				int check = createProcess(p, ptprob);
				if(check == -1) 
				{ 
					cout << "2: ERROR: Process could not be created" << endl;
					defragmentation(p);
					return; 
				}
				
				for (int i = 0; i < p.back().getCellRequired(); i++)
				{
					mainMem[p.back().getStartPos() + i] = p.back().getProcName();
				}
				cout << "new processes created in main memory" << endl; 
			}
			printMem();
			cin >> input;
		}
		else
		{
			cout << "Can not understand your request!" << endl;
			cin >> input;
		}
	}
	cout << "EXIT FIRST FIT FUNCTION " << endl; 
	return; 
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

void defragmentation(vector<Process> &p)
{
	int i = 0, count = 0;

	cout << "Performing defragmentation." << endl;

	while (i < 2400)
	{
		while(mainMem[i] != '.' && mainMem[i] != mainMem[i+1])
		{
			cout << "testing~~~" << endl;
			i++; //by the end it represent size of the process
		}
		for (int j = 0; j < p.size(); j++) //search through the vector of process to find the char
		{
			cout << "loop 1111111111" << endl;
			if (mainMem[i] = p[j].getProcName()) //when found the char
			{
				for (int k = 0; k < p[j].getCellRequired(); k++)
				{
					cout << "loop 222222222" << endl;
					p[j].setStartPos(i-p[j].getCellRequired()); //reset starting position of each process
					mainMem[p[j].getStartPos() + k] = p[j].getProcName();
				}
			}
		}
	}

	cout << "Defragmentation complete." << endl;
	cout << "Relocated....." << endl;
}

int createProcess(vector<Process> &proc, int pt)
{
	cout << "CREATE PROCESS FUNCTION" << endl; 
	int k = nextProcessChar();
	if (k == -1)
	{
		// the process could not be created so it sends a -1 flag
		//cout << "3: ERROR: out of memory" << endl;
		return -1;
	}
	int len = rand() % 90 + 10;
	int startLocation = findFit(len); 
	if (startLocation == -1)
	{
		cout << "4: ERROR: Out of Memory in Create Process " << endl; 
		return -1; 
	}
	Process newProcess(k, len, startLocation, pt);
	proc.push_back(newProcess);
	cout << "END CREATE PROCESS FUNCTION " << endl; 
	return 0; 
}
bool enterProbability(int prob){ 
	int random = rand() % 99 + 1; 
	//If the number is within the probability return true
	if(random <= prob) 
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
	cout << "NEXT PROCESS CHAR FUNCTION" << endl; 
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
			else if( asciiChar[charArrLoc] == 0 ) 
			{ 
				int temp; 
				asciiChar[charArrLoc] = 1;
				temp = charArrLoc + 65; 
				charArrLoc++;
				return temp; 
			}
			else
			{
				charArrLoc++; 
			} 
			outOfMemory++;
		}
		else
		{
			cout << "CHAR LOCATION IS AT 58" << endl;
			charArrLoc = 0;
			outOfMemory = 0; // reset outOfMemory to zero
			cout << "NEW CHAR LOCATION IS " << charArrLoc << endl; 
		}
		cout << "The out of memory number is: "<< outOfMemory << endl; 
		
	}
	cout << "I AM IN A PLACE I SHOULDN'T BE AND I AM RETURNING -1" << endl; 
	return -1; //if -1 is returned the program is out of memory therefore it should terminate 
}

int findFit(int length)
{
	cout << "FIND FIT FUNCTION" << endl;

	int i = ros; // ros = the begining of memory
	int size = 0; 
 
	for(i; i < 2400; i++)
	{
		size = 0; // reset size 
		while (mainMem[i] == '.')
		{	
			size++;
			i++;
			if(size == length)
			{
				cout << "FIND FIT size == length END" << endl; 
				return i-size;  // starting location for memory of this length 
			}
		} 
	}
	//if we get here that means we are out of memory 
	cout << "FIND FIT OUT OF MEMORY" << endl; 
	return -1; 
}
void printMem()
{
	cout << "PRINT MEMORY FUNCTION " << endl; 
	for (int i = 0; i < 2400; i++)
		cout << mainMem[i];
	cout << "*********************************" << endl;
}