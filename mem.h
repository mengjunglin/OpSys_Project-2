#include <iostream>
using namespace std;

class Process
{
private:
	char procName;
	int cellRequired;
	int termProb;

public:
	Process();
	Process(char proc, int cell);
	char getProcName();
	int getCellRequired();
	int getTermProb();
	void setMemName(char name);
	void setCellRequired(int cell);
};

Process::Process()
{
	procName = ' ';
	cellRequired = 0;
}

Process::Process(char proc, int cell)
{
	procName = proc;
	cellRequired = cell;
}

char Process::getProcName()
{
	return procName;
}

int Process::getCellRequired()
{
	return cellRequired;
}

void Process::setMemName(char name)
{
	procName = name;
}

void Process::setCellRequired(int cell)
{
	cellRequired = cell;
}