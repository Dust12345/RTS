#include "Process.h"


Process::Process()
{
}


Process::Process(std::string& pName, int pPeriod, int pCompTime, int pPrio)
{
	name = pName;
	period = pPeriod;
	compTime = pCompTime;
	prio = pPrio;
}

Process::~Process()
{
}
