class Process
{
private:
	char procName;
	int cellRequired;
	int startPos;
	int termProb;

public:
	Process();
	Process(char proc, int cell, int sPos, int term);
	char getProcName();
	int getCellRequired();
	int getStartPos();
	int getTermProb();
	void setMemName(char name);
	void setCellRequired(int cell);
	void setStartPos(int start);
	void setTermProb(int tProb);
};

Process::Process()
{
	procName = ' ';
	cellRequired = 0;
	startPos = 0;
	termProb = 0;
}

Process::Process(char proc, int cell, int sPos, int term)
{
	procName = proc;
	cellRequired = cell;
	startPos = sPos;
	termProb = term;
}

char Process::getProcName()
{
	return procName;
}

int Process::getCellRequired()
{
	return cellRequired;
}

int Process::getStartPos()
{
	return startPos;
}

int Process::getTermProb()
{
	return termProb;
}

void Process::setMemName(char name)
{
	procName = name;
}

void Process::setCellRequired(int cell)
{
	cellRequired = cell;
}

void Process::setStartPos(int start)
{
	startPos = start;
}

void Process::setTermProb(int tProb)
{
	termProb = tProb;
}