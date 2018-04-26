#pragma once

#include <string>
#include <vector>

//kitchensink
class KitchensinkLib
{
public:

	static int ggT(int a, int b);
	static int ggTOfN(std::vector<int>& numbers);

	static int lcm(int a, int b);
	static int lcmOfN(std::vector<int>& numbers);


	static void writeDbLines(std::vector<std::string> dbLines);
};

