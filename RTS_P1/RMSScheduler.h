#pragma once
#include <vector>
#include "Process.h"

class RMSScheduler
{
public:
	RMSScheduler();
	~RMSScheduler();

	void scheduleByRMS(std::vector<Process>& pVct);
	void sortByRMS(std::vector<Process>& pVct);





	
};

