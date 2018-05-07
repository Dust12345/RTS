#pragma once
#include <vector>
#include "Process.h"

class RTAScheduler
{
public:
	RTAScheduler();
	~RTAScheduler();

	void simpleRTA(std::vector<Process>& pVct);

	void exactRTA(std::vector<Process>& pVct);
	float exactRTA(std::vector<Process>& pVct,float rLastIt,int i);
	
	void scheduleOPA(std::vector<Process>& pVct);
	


private:
	
	float simpleRTASum(std::vector<Process>& pVct, int i);
	float exactRTASum(std::vector<Process>& pVct, float rLastIt,int i);

	bool exactRTA(std::vector<Process>& pVct, int k);

	void swap(std::vector<Process>& pVct, int k, int next);

};

