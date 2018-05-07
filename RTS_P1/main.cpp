#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Process.h"
#include <limits>
#include "StaticScheduler.h"
#include "RMSScheduler.h"
#include "DMSScheduler.h"
#include "RTAScheduler.h"
#include "KitchensinkLib.h"


void processLine(std::vector<Process>& pVct, std::string& line)
{
	char delim = ';';

	int elem = 0;
	Process p;

	std::string str = "";

	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] != delim){
			str += line[i];

		}
		else{
			if (elem == 0){
				p.name = str;
			}
			else if (elem == 1){
				p.period = std::stoi(str);
			}
			else if (elem == 2){
				p.compTime = std::stoi(str);
			}
			else if (elem == 3)
			{
				p.prio = std::stoi(str);
			}
			elem++;
			str = "";
		}
	}

	pVct.push_back(p);
}

void getProcessesFromFile(std::vector<Process>& pVct,std::string& src)
{
	std::string line;
	std::ifstream myfile(src);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			processLine(pVct, line);
		}
		myfile.close();
	}
}

void sortByRMS(std::vector<Process>& pVct)
{
	int currentLowest = std::numeric_limits<int>::max();
	int currentLowestIndex = -1;
	int prio = 1;
	std::vector<Process> sortedList;

	while (true)
	{
		for (int i = 0; i < pVct.size(); i++)
		{
			if (pVct[i].compTime <= currentLowest)
			{
				currentLowest = pVct[i].compTime;
				currentLowestIndex = i;
			}
		}


		if (currentLowestIndex != -1)
		{

			float u = pVct[currentLowestIndex].compTime / pVct[currentLowestIndex].period;

			std::cout << "Job: " << pVct[currentLowestIndex].name << " Priority: " << prio << " Piriod: "
				<<	pVct[currentLowestIndex].period << " computation time: " << pVct[currentLowestIndex].compTime << " Utility: " << u << std::endl;

			sortedList.push_back(pVct[currentLowestIndex]);

			pVct.erase(pVct.begin() + currentLowestIndex);
			currentLowestIndex = -1;			
			currentLowest = std::numeric_limits<int>::max();
			prio++;

		}
		else
		{
			pVct = sortedList;
			std::cout << "All jobs printed" << std::endl;
			return;
		}
	}
}


float calclLL(std::vector<Process>& pVct)
{
	float uSum = 0;
	for (int i = 0; i < pVct.size(); i++)
	{
		float u = (float)pVct[i].compTime / (float)pVct[i].period;
		uSum += u;
	}

	return uSum;
}



float calcLLBound(float n)
{
	return n*(std::powf(2, (1 / n)) - 1);
}

bool isSchedulable(std::vector<Process>& pVct)
{
	float llu = calclLL(pVct);
	float llBound = calcLLBound(pVct.size());

	if (llu <= llBound)
	{
		return true;
	}
	else{
		return false;
	}
}


void writeLLBoundForN(int n)
{
	std::string str = "";
	for (int i = 1; i < n; i++)
	{
		std::string bound = std::to_string(calcLLBound(i));
		str = str + bound + ";";
	}
	std::ofstream myfile;
	myfile.open("D:/GitHubRepos/RTS_P1/RTS_P1/out.txt");
	myfile << str;
	myfile.close();

}




void doStuff(std::vector<Process>& pVct)
{

	sortByRMS(pVct);
	float llu = calclLL(pVct);
	std::cout << "LL of set: " << llu << std::endl;

	float llBound = calcLLBound(pVct.size());

	if (llu <= llBound)
	{
		std::cout << "will work" << std::endl;
	}
	else {
		std::cout << "wont work" << std::endl;
	}

	writeLLBoundForN(10);
}

int main()
{
	std::vector<Process> pVct;
	std::string str = "D:/GitHubRepos/RTS_P1/RTS/RTS_P1/T3.txt";

	getProcessesFromFile(pVct, str);
		
	//doStuff(pVct);

	//StaticScheduler ss;
	//ss.calccSchedule(pVct);


	/*RMSScheduler rs;
	rs.sortByRMS(pVct);
	rs.scheduleByRMS(pVct);*/

/*	DMSScheduler ds;
	ds.sortByDMS(pVct);
	ds.scheduleByDMS(pVct);*/

	RMSScheduler rs;
	//rs.sortByRMS(pVct);
	

	RTAScheduler rtaSched;
	//rtaSched.simpleRTA(pVct);
	//rtaSched.exactRTA(pVct);
	rtaSched.scheduleOPA(pVct);
	
	

	while (true){

	}
}