#include "StaticScheduler.h"


StaticScheduler::StaticScheduler()
{
}


StaticScheduler::~StaticScheduler()
{
}


void StaticScheduler::calccSchedule(std::vector<Process>& pVct)
{
	int majorCycle = 0;
	int minorCycle = 0;
	std::vector<int> periods;
	std::vector<bool> doneAheadOfTime;
	
	for (int i = 0; i < pVct.size(); i++)
	{
		doneAheadOfTime.push_back(false);
	}

	int largestSoFar = -1;
	
	for (int i = 0; i < pVct.size(); i++)
	{
		periods.push_back(pVct[i].period);

		if (pVct[i].period > largestSoFar)
		{
			largestSoFar = pVct[i].period;
		}
	}
	majorCycle = largestSoFar;
	minorCycle = ggTOfN(periods);
	//sortByPeriod(pVct);

	int timeMarker = minorCycle;
	int timeLeft = minorCycle;

	while (true)
	{
		while (true)
		{
			for (int i = 0; i < pVct.size(); i++)
			{
				if (timeMarker%pVct[i].period == 0)
				{
					if (doneAheadOfTime[i])
					{
						doneAheadOfTime[i] = false;
						
					}
					else{
						timeLeft = timeLeft - pVct[i].compTime;


						if (timeLeft < 0)
						{
							std::cout << "Scheduling failed" << std::endl;
							return;
						}
						else
						{
							std::cout << "Scheduling: " << pVct[i].name << " which takes: " << pVct[i].compTime << " units" << std::endl;
							//std::cout << "Time left: " << timeLeft << std::endl;
						}
					}
				

				}
				else
				{
					if (timeLeft - pVct[i].compTime >= 0 && !doneAheadOfTime[i])
					{
						timeLeft = timeLeft - pVct[i].compTime;
						doneAheadOfTime[i] = true;
						std::cout << "Scheduling: " << pVct[i].name <<" which takes: "<< pVct[i].compTime<<" units" <<std::endl;
						//std::cout << "Time left: " << timeLeft << std::endl;
					}
				}
			}

			std::cout << "Time left: " << timeLeft << std::endl;
			std::cout << "Interrupt for: "<< timeMarker << std::endl;

			timeMarker = timeMarker + minorCycle;
			timeLeft = minorCycle;

			if (timeMarker > majorCycle) {
				return;
			}

			
		}
	}

}


int StaticScheduler::ggT(int a, int b)
{
	if (b == 0)
		return a;
	else return ggT(b, a % b);
}

int StaticScheduler::ggTOfN(std::vector<int>& numbers)
{
	int returnValue = 0;
	for (int i = 1; i < numbers.size(); i++)
	{	
		if (i == 1)
		{
			returnValue = ggT(numbers[i - 1], numbers[i]);
		}
		else
		{
			returnValue = ggT(returnValue, numbers[i]);
		}		
	}

	return returnValue;
}


void StaticScheduler::sortByPeriod(std::vector<Process>& pVct)
{
	int currentLowest = 99999999;
	int currentLowestIndex = -1;
	int lowestLast = -1;
	std::vector<Process> pVctTmp;

	while (true)
	{
		for (int i = 0; i < pVct.size(); i++)
		{
			if (pVct[i].period <= currentLowest && pVct[i].period > lowestLast)
			{
				currentLowest = pVct[i].period;
				currentLowestIndex = i;
			}
		}


		if (currentLowestIndex != -1)
		{

			pVctTmp.push_back(pVct[currentLowestIndex]);
			currentLowestIndex = -1;
			lowestLast = currentLowest;
			currentLowest = 9999999;
			

		}
		else{
			pVct = pVctTmp;
			return;
		}
	}
}