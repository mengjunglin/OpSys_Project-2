#include <iostream>
using namespace std;
class Memory
{
private:
	char memName;
	int numCells;

public:
	Memory();
	Memory(char mem, int cell);
	char getMemName();
	int getNumCells();
	void setMemName(char name);
	void setNumCells(int cell);
};

Memory::Memory()
{
	memName = ' ';
	numCells = 0;
}

Memory::Memory(char mem, int cell)
{
	memName = mem;
	numCells = cell;
}

char Memory::getMemName()
{
	return memName;
}

int Memory::getNumCells()
{
	return numCells;
}

void Memory::setMemName(char name)
{
	memName = name;
}

void Memory::setNumCells(int cell)
{
	numCells = cell;
}