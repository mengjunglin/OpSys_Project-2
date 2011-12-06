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

#define ros 80	// resident operating system

void firstFit(vector<Process> &p, int ptprob, int npprob);	
void bestFit(vector<Process> &p, int ptprob, int npprob);	
void nextFit(vector<Process> &p, int ptprob, int npprob);	
void worstFit(vector<Process> &p, int ptprob, int npprob);	
int defragmentation(vector<Process> &p);	

bool checkProbability(int prob); 
int nextProcessChar(); 
int findFit(int length); 
int createProcess(vector<Process> &proc, int pt); 
int findMatch(vector<Process> &proc, char procName);
void checkTerminate(vector<Process> & proce); 
void printMem();

int charArrLoc = 0; // counter for the ASCII character 
int asciiChar[58]; 
char mainMem[2400]; // 1-dimentional character array, main memory

int main(int argc, char * argv[])
{
	int ptp, npp, i, j, check;
	vector <Process> processes;

	if (argc != 4) {
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
	int startPos = ros;
	// create and assign 20 processes into memory
	for (int i = 0; i < 20; i++){
		check = createProcess(processes, ptp);
		/* If createProcess returns -1 than the program is out of 
		 * Memory and should report that to the user and terminate */ 
		if(check == -1) { 
			cout << "1: ERROR: Process could not be created" << endl; 
			//return -1; 
		}
		processes.back().setStartPos(startPos);
		/* if the program is not out of memory than add the new
		 * process to main memory */ 
		for (j = 0; j < processes.back().getCellRequired(); j++){
			mainMem[processes.back().getStartPos() + j] = processes.back().getProcName();
			startPos ++;
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
	int defrag, check, i, size; 
	bool breakLoop = false; 

	cin >> input;
	
	while( input != 'q' ) {
		if (input == 'c') { 
			checkTerminate(p);
			/* checkProbability will return true if a new process 
			/* should be created based on the probability */
			if(checkProbability(npprob) == true) { 
				check = createProcess(p, ptprob);
				if(check == -1) { 
					cout << "5: ERROR: Unable to create a new process. System is out of memory" << endl; 
					return; 
				}
				i = ros; 
				while(i < 2400) {
					size = 0;
					while (mainMem[i] == '.') {	
						size++;
						i++;
						if(size == p.back().getCellRequired()) {
							/* the return value of i-size is the starting location
							 * for the process in main memory */ 
							p.back().setStartPos(i-size);
							breakLoop = true; 
							break;
						}
						if( i == 2400 ) 
						{
							defrag = defragmentation(p);
							/* if defragmentation is unable to happen since the 
							 * main memory is currently defragmented than it is 
							 * out of memory and will end the program */ 
							if(defrag == -1) {
								cout << "5: ERROR: Unable to perform defragmentation. System is out of memory" << endl; 
								return; 
							}
							else {
								printMem();
								cout << "After defrag then attempt to create new process." << endl;
								i = ros;
								size = 0;
							}
						}
					} 
					if(breakLoop == true) {
						breakLoop = false; 
						break;
					}
					i ++;
				}

				/* if defrgamentation happens than the new process 
				 * is able to be pushed into main memory where the 
				 * starting position is the first '.' in main memory */ 
				if(p.back().getStartPos() == -1)
				{
					cout << "7: ERROR: Out of Memory" << endl; 
					return; 
				}
				for (i = 0; i < p.back().getCellRequired(); i++) {
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
	int bestFit = 2401, bestFitStartLoc = 2401, i, count = 0, 
		check, x, pLoc, defrag, totalSizeRequired;
	bool breakLoop = false, periodFound = false; 

	cin >> input;
	while( input != 'q' ) {
		if (input == 'c') {
			checkTerminate(p);
			if(checkProbability(npprob) == true) { 
				check = createProcess(p, ptprob);
				if(check == -1) { 
					cout << "5: ERROR: Unable to create a new process. System is out of memory" << endl; 
					return; 
				}
				i = ros;
				bestFit = 2401; 
				bestFitStartLoc = 2401; 
				while(i < 2400) {
					while(mainMem[i] == '.') {
						count++;
						i++;
						periodFound = true; 
						if(i == 2400) {
							break;
						}
					} 
					if(count < bestFit && count >= p.back().getCellRequired())
					{
						bestFit = count; 
						bestFitStartLoc = i - count; 
					}
					count = 0;
					if(periodFound == true) {
						periodFound = false;
					}
					else {
						i++;
					}

					/* a new process was unable to be created and added to the memory
					* the program will attempt to defrag */ 
					if (i == 2400 && bestFit == 2401) { //this means it reaches the end of mainMem and current-best-fit never changes (could not fit new process into any empty spot)
						defrag = defragmentation(p);
						if(defrag == -1) {
							cout << "6: ERROR: Out of Memory, unable to perform defragmentation" << endl; 
							return; 
						}
						else { 
							printMem();
							cout << "After defrag then attempt to create new process." << endl;
							i = ros;
						}
					}
				}
				totalSizeRequired = bestFitStartLoc + p.back().getCellRequired();
				p.back().setStartPos(bestFitStartLoc); 
				for(x = bestFitStartLoc; x < totalSizeRequired; x ++)
				{
					mainMem[x] = p.back().getProcName(); 
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

void nextFit(vector<Process> &p, int ptprob, int npprob)
{
	checkProbability(npprob);
}

void worstFit(vector<Process> &p, int ptprob, int npprob)
{
	checkProbability(npprob);
}

int defragmentation(vector<Process> &p)
{
	int i = ros, empty = 0, tempStart, oldEnd = 0, newEnd = 0, freeCells = 0, numProc = 0, 
			x, pLoc, tempOldEnd, j, oldStart, oldLen, tempNewEnd;
	bool defrag = false, breakLoop = false; 
	double per;
	
	while (i < 2400) {
		if(mainMem[i] == '.') {
			breakLoop = false; 
			for(x = i; x < 2400; x ++) {
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
					for(j = i; j < i + p[pLoc].getCellRequired(); j ++) {
						mainMem[j] = p[pLoc].getProcName();
						tempNewEnd = p[pLoc].getStartPos() + p[pLoc].getCellRequired();
						if(tempNewEnd > newEnd) {
							newEnd = tempNewEnd; 
						}
					}
					oldStart = j;
					for(j = oldStart; j < oldLen; j++) {
						mainMem[j] = '.'; 
						breakLoop = true;
					}
					if(breakLoop == true) {
						numProc++;
						i += p[pLoc].getCellRequired();
						break;
					}
				}
			}
		}
		else {
			i++;
		}
	}

	/* if the program was able to defragment at all 
	 * during this iteration of the defragmentation function
	 * than defrag = true and the program returns a 1 
	 * otherwise the program was unable to defrag which 
	 * means it is out of memory and -1 is returned */ 
	if(defrag == true) {
		freeCells = oldEnd - newEnd;
		per = ((double)freeCells / (double)2400) * (double)100;
		cout << "Defragmentation complete." << endl;
		cout << "Relocated " << numProc << " processes to create free memory block of " 
			<< freeCells << " units (" << per << "% of total memory)." << endl;
		return 1; 
	}
	else {
		return -1; 
	}
}

/* find match searches through the processes to find 
 * the process that is being looked at in main memory 
 * since the processes might not be in order of their 
 * vector location it is necessary to find the processes 
 * that matches the character in main memory */ 
int findMatch(vector<Process> &proc, char procName) {
	int i = 0; 
	for(i; i < proc.size(); i ++) {
		if(proc[i].getProcName() == procName){
			return i;
		}
	}
	/* if the process is not found then -1 is returned 
	 * to trigger an error had occured */ 
	return -1; 
}

/* create process adds in the new process to the 
 * process vector if there is an available character 
 * in main memory */ 
int createProcess(vector<Process> &proc, int pt)
{
	int k = nextProcessChar(), len, startLocation;
	
	if (k == -1) {
		cout << "4: ERROR: Out of Memory in Create Process " << endl; 
		return -1;
	}
	len = rand() % 90 + 10;
	Process newProcess(k, len, -1, pt);
	proc.push_back(newProcess);
 
	return 0; 
}

/* enter probability returns true if the process 
 * will be added based on the probability */ 
bool checkProbability(int prob){ 
	int random = rand() % 99 + 1; 
	// If the number is within the probability return true
	if(random <= prob) { 
		return true; 
	}
	else { 
		return false; 
	} 
}

/* next process char returns the ASCII value of the next 
 * available process character or an out of memory 
 * error if there are no more characters */ 
int nextProcessChar() { 
	int outOfMemory = 0, temp;
	
	while(outOfMemory < 58) {
		if( charArrLoc != 58 ) { 
			if( charArrLoc == 0 && asciiChar[charArrLoc] != 1) {
				asciiChar[charArrLoc] = 1; 
				charArrLoc++;
				return 65;
			}
			else if( asciiChar[charArrLoc] != 1 ) { 
				asciiChar[charArrLoc] = 1;
				temp = charArrLoc + 65; 
				charArrLoc++;
				return temp; 
			}
			else {
				charArrLoc++; 
			} 
			outOfMemory++;
		}
		else {
			charArrLoc = 0;
			outOfMemory = 0;
		}
	}
	/* if there is not another character than the program should 
	 * report that it is out of memory therefore an error of -1 is sent */ 
	return -1;
}

/* find fit finds the location that the process will 
 * be able to fit into  */ 
//int findFit(int length)
//{
//	// ros is the beginning of memory
//	int i, size = 0;  
// 
//	for(i = ros; i < 2400; i++) {
//		size = 0;
//		while (mainMem[i] == '.') {	
//			size++;
//			i++;
//			if(size == length) {
//				/* the return value of i-size is the starting location
//				 * for the process in main memory */ 
//				return i - size; 
//			}
//		} 
//	}
//	return -1; 
//}

/* check terminate checks if the process should terminate 
 * based on the probability given by the user input */ 
void checkTerminate(vector<Process> &p)
{
	vector<Process> pCopy;
	pCopy.clear();
	char temp; 
	int j, r, m;

	for (j = 0; j < p.size(); j++)  {
		if (checkProbability(p[j].getTermProb()) == true) {
			for(r = 0; r < 58; r++) {
				temp = r + 65;  
				if(temp == p[j].getProcName()) {
					asciiChar[r] = 0; 
					break;
				}
			}
			for (m = 0; m < p[j].getCellRequired() + 1; m++) {
				mainMem[p[j].getStartPos() + m] = '.';
			}
		}
		else {
			pCopy.push_back(p[j]);
		}
	}
	if(pCopy.size() != p.size()) {
		p.clear(); 
		p = pCopy; 
	}
	return; 
}
void printMem()
{
	int i; 
	for (i = 0; i < 2400; i++) {
		cout << mainMem[i];
	}
	cout << endl << endl;
}