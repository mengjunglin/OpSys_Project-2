// Operating System FALL2011
// Project #2 - Memory Management Simulation System
// Tiffany Milano & Meng Jung Lin
// Finalize Date: 12/09/2011

#include <iostream>
#include <time.h>
#include "mem.h"
using namespace std;

int main()
{
	int amount, used = 0, i, j;
	char mainMem[2400]; //1-dimentional character array, main memory
	Process processes[20];	//create an array of Process

	for (i = 0; i < 2400; i++)
	{
		mainMem[i] = '.';
	}

	srand(time(NULL)); //set seed to get random numbers

	//20 random amount of memory cells
	for (i = 0; i < 20; i++)
	{
		amount = rand() % 90 + 10; //random amount between 10-100
		Process p(i+65, amount);
		processes[i] = p;
	}

	/*for (i = 0; i < 20; i++)
		cout << processes[i].getProcName() << " " << processes[i].getCellRequired() << endl;*/

	//assign into main memory
	for (i = 0; i < 20; i++)
	{
		for(j = 0; j < processes[i].getCellRequired(); j++)
		{
			mainMem[j+used] = processes[i].getProcName();
		}
		used += processes[i].getCellRequired();
	}

	//print all 2400 cells
	for (i = 0; i < 2400; i++)
		cout << mainMem[i];

	system("pause");
	return 0;
}