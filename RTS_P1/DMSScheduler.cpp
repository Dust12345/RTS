#include "DMSScheduler.h"
#include "KitchensinkLib.h"
#include <iostream>

DMSScheduler::DMSScheduler()
{
}


DMSScheduler::~DMSScheduler()
{
}



void DMSScheduler::scheduleByDMS(std::vector<Process>& pVct)
{
	int currentTime = 0;
	std::vector<bool> needsTime;
	std::vector<int> lastExecWindow;
	std::vector<int> timeNeeded;
	std::vector<int> peroids;

	std::vector<std::string> dbLines;


	for (int i = 0; i < pVct.size(); i++)
	{
		needsTime.push_back(true);
		lastExecWindow.push_back(-1);
		peroids.push_back(pVct[i].period);
		timeNeeded.push_back(pVct[i].compTime);
		dbLines.push_back("Line " + pVct[i].name + ": ");
	}

	int repeatPoint = KitchensinkLib::lcmOfN(peroids);

	while (true)
	{

		//break condition
		if (currentTime >= repeatPoint){
			std::cout << "Scheduling done" << std::endl;
			KitchensinkLib::writeDbLines(dbLines);

			return;
		}

		//check which process gets time
		int indexOfProcess = -1;
		for (int i = 0; i < needsTime.size(); i++)
		{
			if (needsTime[i])
			{
				indexOfProcess = i;
				break;
			}
		}



		//check if any process needs time
		if (indexOfProcess != -1)
		{
			timeNeeded[indexOfProcess] = timeNeeded[indexOfProcess] - 1;

			if (timeNeeded[indexOfProcess] == 0)
			{

				int endWindow = (currentTime) / pVct[indexOfProcess].period;
				lastExecWindow[indexOfProcess] = endWindow;

				needsTime[indexOfProcess] = false;
			}

			std::cout << pVct[indexOfProcess].name << std::endl;

		}
		else
		{
			//no process needs time atm

		}

		currentTime++;
		for (int i = 0; i < needsTime.size(); i++)
		{
			//check if a process is about to fail
			int endWindow = (currentTime + timeNeeded[i]-1) / pVct[i].period;

			int timeAfterCurrentWindow = currentTime%pVct[i].period;

			if (needsTime[i] && timeNeeded[i]-1 + timeAfterCurrentWindow > pVct[i].prio)
			{
				std::cout << "Scheduling failed. Process " << pVct[i].name << " could not be executed within its deadline" << std::endl;
				KitchensinkLib::writeDbLines(dbLines);
				return;
			}

			if (lastExecWindow[i] + 1 < endWindow)
			{
				std::cout << "Scheduling failed. Process " << pVct[i].name << " could not be executed in time" << std::endl;
				KitchensinkLib::writeDbLines(dbLines);
				return;
			}

			if (i == indexOfProcess){
				dbLines[i] = dbLines[i] + pVct[i].name;
			}
			else{
				dbLines[i] = dbLines[i] + "x";
			}

			int window = currentTime / pVct[i].period;

			if (lastExecWindow[i] < window && !needsTime[i]){
				needsTime[i] = true;
				timeNeeded[i] = pVct[i].compTime;
			}
		}


	}
}



void DMSScheduler::sortByDMS(std::vector<Process>& pVct)
{
	int currentLowest = std::numeric_limits<int>::max();
	int currentLowestIndex = -1;
	int prio = 1;
	std::vector<Process> sortedList;

	while (true)
	{
		for (int i = 0; i < pVct.size(); i++)
		{
			if (pVct[i].prio <= currentLowest)
			{
				currentLowest = pVct[i].prio;
				currentLowestIndex = i;
			}
		}

		if (currentLowestIndex != -1)
		{
			sortedList.push_back(pVct[currentLowestIndex]);
			pVct.erase(pVct.begin() + currentLowestIndex);
			currentLowestIndex = -1;
			currentLowest = std::numeric_limits<int>::max();
			prio++;

		}
		else
		{
			pVct = sortedList;

			return;
		}
	}
}
