#include "RTAScheduler.h"
#include <math.h>
#include <iostream>
#include "KitchensinkLib.h"

RTAScheduler::RTAScheduler()
{
}


RTAScheduler::~RTAScheduler()
{
}


void RTAScheduler::simpleRTA(std::vector<Process>& pVct)
{
	for (int i = 0; i < pVct.size(); i++)
	{
		float r = pVct[i].compTime + simpleRTASum(pVct, i);
		std::cout << "Rate for task " << pVct[i].name << " is " << r << std::endl;
	}
}

void RTAScheduler::swap(std::vector<Process>& pVct, int k, int next)
{
	Process tmp = pVct[k];
	pVct[k] = pVct[next];
	pVct[next] = tmp;
}

void RTAScheduler::scheduleOPA(std::vector<Process>& pVct)
{
	for (int k = 0; k < pVct.size(); k++)
	{
		bool ok = false;

		for (int next = 0; next < pVct.size(); next++)
		{
			swap(pVct, k, next);
			ok = exactRTA(pVct, k);

			if (ok)
			{
				break;
			}
		}

		if (!ok)
		{
			std::cout << "OPA failed" << std::endl;
			return;
		}
	}

	std::cout << "OPA worked" << std::endl;
	std::cout << "Priorities are:" << std::endl;
	for (int i = 0; i < pVct.size(); i++)
	{
		std::cout << pVct[i].name << std::endl;
	}

}

bool RTAScheduler::exactRTA(std::vector<Process>& pVct, int k)
{
	std::vector<int> peroids;

	for (int i = 0; i < pVct.size(); i++)
	{
		peroids.push_back(pVct[i].period);
	}

	float d = KitchensinkLib::lcmOfN(peroids);

	float delta = 1;

	for (int i = 0; i < pVct.size(); i++)
	{
		float rLastIt = pVct[i].compTime;

		while (true)
		{
			float r = exactRTA(pVct, rLastIt, i);
			//std::cout << "Task: " << pVct[i].name << " is " << r << std::endl;
			//check break condition

			

			if (std::abs(r - rLastIt) < delta || r>d)
			{	

				if (k == i) {
					return true;
				}

				break;
			}
			else
			{
				rLastIt = r;
			}

		}
	}
	return false;
	//std::cout << "All jobs done" << std::endl;
}


void RTAScheduler::exactRTA(std::vector<Process>& pVct)
{

	std::vector<int> peroids;

	for (int i = 0; i < pVct.size(); i++)
	{	
		peroids.push_back(pVct[i].period);	
	}

	float d = KitchensinkLib::lcmOfN(peroids);

	float delta = 1;

	for (int i = 0; i < pVct.size(); i++)
	{
		float rLastIt = pVct[i].compTime;

		while (true)
		{
			float r = exactRTA(pVct, rLastIt,i);
			std::cout << "Task: " << pVct[i].name << " is " << r << std::endl;
			//check break condition

			if (r>d) {
				std::cout << "Job set wont work" << std::endl;
				return;
			}

			if (std::abs(r - rLastIt) < delta)
			{				
				break;
			}
			else
			{
				rLastIt = r;
			}

		}
	}

	std::cout << "All jobs done" << std::endl;
}

float RTAScheduler::exactRTA(std::vector<Process>& pVct, float rLastIt,int i)
{
	return pVct[i].compTime + exactRTASum(pVct, rLastIt, i);
}


float RTAScheduler::exactRTASum(std::vector<Process>& pVct, float rLastIt,int i)
{
	float sum = 0;

	for (int j = i-1; j >= 0; j--)
	{
		sum = sum + std::ceil(rLastIt / pVct[j].period)*pVct[j].compTime;
	}

	return sum;
}

float RTAScheduler::simpleRTASum(std::vector<Process>& pVct, int i)
{
	float sum = 0;

	for (int j = i-1; j >= 0; j--)
	{
		sum = sum + std::ceil(pVct[i].prio / pVct[j].period)*pVct[j].compTime;
	}

	return sum;
	
}