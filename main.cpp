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

void firstFit(vector<Process> &p, int ptprob, int npprob);
void bestFit(vector<Process> &p, int ptprob, int npprob);	//Best Fit Algorithm
void nextFit(vector<Process> &p, int ptprob, int npprob);	//Next Fit Algorithm
void worstFit(vector<Process> &p, int ptprob, int npprob);	//Worst Fit Algorithm
int defragmentation(vector<Process> &p);

bool enterProbability(int prob);
int nextProcessChar();
int findFit(int length); //function that find the size of the first empty slot
void printMem(); //function to print main memory
int createProcess(vector<Process> &proc, int pt);
int findMatch(vector<Process> &proc, char procName);
void checkTerminate(vector<Process> & proce); //function that check for terminated processes

int charArrLoc = 0; //counter for the ASCII character 
int asciiChar[58]; 
char mainMem[2400]; //1-dimentional character array, main memory
int used = ros;

int main(int argc, char * argv[])
{
	int ptp, npp, i, j, check;
	vector <Process> processes;

	if (argc != 4)
	{
		cout << "USAGE: memsim { first | best | next | worst } <process-termination-probability> <new-process-probability>" << endl;
		system("pause");
		return 0;
	}

	ptp = atoi(argv[2]); // process-termination-probability = argv[2]
	npp = atoi(argv[3]); // new-process-probability = argv[3]

	// Initialize Main Memory starting with 80 #'s
	for (i = 0; i < 2400; i++){
		if (i < ros){
			mainMem[i] = '#';
		} else {
			mainMem[i] = '.';
		}
	}
	srand(time(NULL)); 
	
	// create and assign 20 processes into memory
	for (int i = 0; i < 20; i++){
		check = createProcess(processes, ptp);
		/* If createProcess returns -1 than the program is out of 
		 * Memory and should report that to the user and terminate */ 
		if(check == -1) { 
			cout << "1: ERROR: Process could not be created" << endl; 
			return -1; 
		}
		/* if the program is not out of memory than add the new
		 * process to main memory */ 
		for (j = 0; j < processes.back().getCellRequired(); j++){
			mainMem[processes.back().getStartPos() + j] = processes.back().getProcName();
		}
	}
	// print out initial main memory 
	printMem();

	if (strcmp(argv[1],"first") == 0) {
		firstFit(processes, ptp, npp);
	}
	else if (strcmp(argv[1],"best") == 0) {
		bestFit(processes, ptp, npp);
	}
	else if (strcmp(argv[1],"next") == 0) {
//		nextFit(processes, ptp, npp);
	}
	else if (strcmp(argv[1],"worst") == 0) {
//		worstFit(processes, ptp, npp);
	}
	else {
		cout << "INVALID INPUT: Please re-run with first, best, next, or worst " << endl; 
		cout << "with <process-termination-probability> and <new-process-probability> " << endl;
		system("pause");
		return 0;
	}
	system("pause");
	return 0;
}

/* firstFit attempts to put the process into the first empty 
 * and large enough space found in main memory */ 
void firstFit(vector<Process> &p, int ptprob, int npprob) 
{
	char input;
	int defrag; 
	
	cin >> input;
	while( input != 'q' )
	{
		if (input == 'c')
		{ 
			checkTerminate(p);
			/* enterProbability will return true if a new process 
			/* should be created based on the probability */
			if(enterProbability(npprob) == true)
			{ 
				int check = createProcess(p, ptprob);
				if(check == -1) 
				{ 
					defrag = defragmentation(p);
					/* if defragmentation is unable to happen since the 
					 * main memory is currently defragmented than it is 
					 * out of memory and will end the program */ 
					if(defrag == -1) 
					{
						cout << "5: ERROR: Unable to perform defragmentation. System is out of memory" << endl; 
						return; 
					}
				}
				/* if defrgamentation happens than the new process 
				 * is able to be pushed into main memory where the 
				 * starting position is the first '.' in main memory */ 
				for (int i = 0; i < p.back().getCellRequired(); i++)
				{
					mainMem[p.back().getStartPos() + i] = p.back().getProcName();
				}
			}
			printMem();
			cin >> input;
		}
		else {
			cout << "INVALID COMMAND: Please enter either c or q to continue or quit" << endl;
			cin >> input;
		}
	} 
	return; 
}

/* best fit looks for the piece in memory that is the 
 * closest to the size of the processes being allocated 
 * if two chunks of memory are the same size than the first 
 * chunk is the "best fit" */ 
void bestFit(vector<Process> &p, int ptprob, int npprob)
{
	char input;
	int bestFit = 2401, bestFitStartLoc = 2401, i = ros, count = 0, check, defrag;
	bool breakLoop = false; 

	cin >> input;
	while( input != 'q' )
	{
		if (input == 'c')
		{
			checkTerminate(p);
			if(enterProbability(npprob) == true)
			{ 
				check = createProcess(p, ptprob);
				if(check == -1) 
				{ 
					defrag = defragmentation(p);
					if(defrag == -1) 
					{
						cout << "5: ERROR: Unable to perform defragmentation. System is out of memory" << endl; 
						return; 
					}
				}
				while(mainMem[i] == '.' && i < 2400)
				{
					count++;
					i++;

					if (count > bestFit)
					{
						break; 
					}
				}





				if (i == 2399)
				{
					int def = defragmentation(p);
					if(def == -1) 
					{
						cout << "6: ERROR: Out of Memory, unable to perform defragmentation" << endl; 
						return; 
					}
				}
				else
				{
					int pLoc = findMatch(p, mainMem[i]); 
					if(count < bestFit && count == p[pLoc].getCellRequired())
					{
						bestFit = count;
						bestFitStartLoc = i;
						breakLoop = true; 
					}
					else if( count < bestFit && count > p[pLoc].getCellRequired()) 
					{ 
						bestFit = count;
						bestFitStartLoc = i;
					}
					count = 0;				
				}
				if(breakLoop == true)
				{
					break; 
				}
				
				i++;
			}
			if(bestFit != 2401) 
			{
				cout << "BEST FIT CRAP" << endl; 
				p.back().setStartPos(bestFitStartLoc);
				for(int x = bestFitStartLoc; x < p.back().getCellRequired(); x++)
				{
					mainMem[x] = p.back().getProcName(); 
				}

			}


			printMem();
			cin >> input;
		}
		else
		{
			cout << "INVALID COMMAND: Please enter either c or q to continue or quit" << endl;
			cin >> input;
		}
	}
	cout << "BEST FIT END RETURN" << endl;
	return;
}

void nextFit(vector<Process> &p, int ptprob, int npprob)
{
	enterProbability(npprob);
}

void worstFit(vector<Process> &p, int ptprob, int npprob)
{
	enterProbability(npprob);
}

int defragmentation(vector<Process> &p)
{
	int i = ros, empty = 0, tempStart, oldEnd = 0, newEnd = 0, freeCells = 0, numProc = 0, 
			x, pLoc, tempOldEnd, j, oldStart, oldLen, tempNewEnd;
	bool defrag = false, breakup = false; 
	double per;
	
	while (i < 2400)
	{
		if(mainMem[i] == '.') 
		{
			breakLoop = false; 
			for(x = i; x < 2400; x ++) 
			{
				/* if x is the last character than the main memory loop 
				 * needs to break therefore i is set to 2400 to trigger 
				 * the end of the while loop and note that we are at the 
				 * last position in main memory */ 
				if (x == 2399) {
					i = 2400;
				}
				/* if main memory is not a '.' than there is a process
				 * located at this point in memory which needs to be 
				 * moved to fill in the free spaces before it */ 
				if(mainMem[x] != '.') {
					defrag = true; 
					pLoc = findMatch(p, mainMem[x]);
					tempOldEnd = p[pLoc].getStartPos() + p[pLoc].getCellRequired();
					/* if the oldEnd is smaller than the new end than the 
					 * old end is updated to the new end */ 
					if(tempOldEnd > oldEnd) {
						oldEnd = tempOldEnd; 
					}
					/* the old length is the starting position plus the cells
					 * required to create the whole process. This is stored for
					 * comparison of length for freeing the left over length */ 
					oldLen = p[pLoc].getStartPos() + p[pLoc].getCellRequired();
					p[pLoc].setStartPos(i); 
					/* main memory is updated to shift the process over */ 
					for(j = i; j < i + p[pLoc].getCellRequired(); j ++) 
					{
						mainMem[j] = p[pLoc].getProcName();
						tempNewEnd = p[pLoc].getStartPos() + p[pLoc].getCellRequired();
						if(tempNewEnd > newEnd)
						{
							newEnd = tempNewEnd; 
						}
					}

					oldStart = j; 

					for(j = oldStart; j < oldLen; j++) 
					{
						mainMem[j] = '.'; 
						breakLoop = true;
					}
					if(breakLoop == true) 
					{
						numProc++;
						i += p[pLoc].getCellRequired();
						break;
					}
				}
			}
		}
		else
		{
			i++;
		}
	}

	freeCells = oldEnd - newEnd;
	cout << "oldEnd = " << oldEnd << " ; newEnd = " << newEnd << endl;

	per = ((double)freeCells / (double)2400) * (double)100;

	cout << "Defragmentation complete." << endl;
	cout << "Relocated " << numProc << " processes to create free memory block of " << freeCells << " units (" << per << "% of total memory)." << endl;
	if(defrag == true)
	{
		return 1; 
	}
	else
	{
		// unable to complete defragmentation (OUT OF MEMORY)
		return -1; 
	}
}

int findMatch(vector<Process> &proc, char procName) 
{
	int i = 0; 
	for(i; i < proc.size(); i ++) 
	{
		if(proc[i].getProcName() == procName)
		{
			return i;
		}
	}
	return -1; 
}

int createProcess(vector<Process> &proc, int pt)
{
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
			charArrLoc = 0;
			outOfMemory = 0; // reset outOfMemory to zero
		}
		cout << "The out of memory number is: "<< outOfMemory << endl; 
		
	}
	return -1; //if -1 is returned the program is out of memory therefore it should terminate 
}

int findFit(int length)
{
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
				return i-size;  // starting location for memory of this length 
			}
		} 
	}
	//if we get here that means we are out of memory 
	return -1; 
}

void checkTerminate(vector<Process> &p)
{
	vector<Process> pCopy;

	pCopy.clear();

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
			if(pCopy.size() != p.size())
			{
				p.clear(); 
				p = pCopy; 
			}
}
void printMem()
{
	for (int i = 0; i < 2400; i++)
		cout << mainMem[i];
	cout << endl << endl;
}