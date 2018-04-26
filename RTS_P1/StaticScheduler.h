#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Process.h"

class StaticScheduler
{
public:
	StaticScheduler();
	~StaticScheduler();

	void calccSchedule(std::vector<Process>& pVct);

private:
	
	int ggT(int a, int b);
	int ggTOfN(std::vector<int>& numbers);
	void sortByPeriod(std::vector<Process>& pVct);
};

