#pragma once

#include <vector>
#include "Process.h"

class DMSScheduler
{
public:
	DMSScheduler();
	~DMSScheduler();

	void scheduleByDMS(std::vector<Process>& pVct);
	void sortByDMS(std::vector<Process>& pVct);

};

