#pragma once
#include <string>

class Process
{
public:
	Process();
	Process(std::string& pName, int pPeriod, int pCompTime, int pPrio);
	~Process();

	std::string name;
	int period;
	int compTime;
	int prio;

};

