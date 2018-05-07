#include <iostream>
#include <fstream>
#include "KitchensinkLib.h"

int KitchensinkLib::ggT(int a, int b)
{
	if (b == 0)
		return a;
	else return ggT(b, a % b);
}

int KitchensinkLib::ggTOfN(std::vector<int>& numbers)
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

int KitchensinkLib::lcmOfN(std::vector<int>& numbers)
{
	int returnValue = 0;
	for (int i = 1; i < numbers.size(); i++)
	{
		if (i == 1)
		{
			returnValue = lcm(numbers[i - 1], numbers[i]);
		}
		else
		{


			returnValue = lcm(returnValue, numbers[i]);
		}
	}

	return returnValue;
}

int KitchensinkLib::lcm(int a, int b)
{
	return (b / ggT(a, b)) * a;
}


void KitchensinkLib::writeDbLines(std::vector<std::string> dbLines)
{
	std::ofstream myfile;
	myfile.open("D:/GitHubRepos/RTS_P1/RTS/RTS_P1/db.txt");

	std::string str = "";
	for (int i = 0; i < dbLines.size(); i++)
	{
		myfile << dbLines[i]+"\n";
	}	
	
	myfile.close();
}