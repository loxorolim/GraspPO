
#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>      
using namespace std;

const float alpha = 0.8;

int* initialSolution(int size)
{
	int* ret = (int*)malloc(sizeof(int)*size);
	int i;
	for (i = 0; i < size; i++)
		ret[i] = 0;
	return ret;
}
//vector<vector<int>> copyScp(vector<vector<int>> scp)
//{
//	int size = scp.size();
//	vector<vector<int>> ret;
//	for(int i = 0; i < size; i++)
//	{
//		vector<int> col;
//		for(int j = 0; j < scp[i].size();j++)
//		{
//			col.push_back(scp[i][j]);
//		}
//		ret.push_back(col);
//	}
//	return ret;
//	
//}
void constructPhase(vector<vector<int>> scp, int size)
{
	//vector<vector<int>> scpCopy = copyScp(scp);
	int* solution = initialSolution(size);
	while(scp.size() > 0)
	{
		vector<int> RCL = generateRCL(scp,size,solution);
		int cand = selectCandidate(RCL);
		solution[cand] = 1;
		scp = removeCovered(scp,cand);
	}
}
vector<vector<int>> removeCovered(vector<vector<int>> scp, int candidate)
{

	for(int i = 0; i < scp.size(); i ++)
	{
		for(int j = 0 ; j < scp[i].size();j++)
		{
			if(scp[i][j] == candidate)
			{
				scp[i].clear();	
				scp.erase(scp.begin() + i);
				i--;
				break;
			}
		}
	}
	return scp;
}
int selectCandidate(vector<int> RCL)
{
	int size = RCL.size();
	return RCL[rand()%size];

}
vector<int> generateRCL(vector<vector<int>> scp, int size, int* solution)
{
	int * numSatisfied = (int*)malloc(sizeof(int)*size);
	int max = 0;
	for(int i = 0; i < size; i++)
	{
		if(solution[i] == 1)
		{
			numSatisfied[i] = -1;
		}
		else
		{
			int s = clausesSatisfied(scp,i);
			numSatisfied[i] = s;
			if(s > max)
				max = s;
		}
	}
	float L = alpha*max;
	vector<int> RCL;
	for(int i = 0; i < size; i++)
		if(numSatisfied[i] >= L)
			RCL.push_back(i);



	free(numSatisfied);
	return RCL;
}
int clausesSatisfied(vector<vector<int>> scp, int column)
{
	int num = 0;
	for(int i = 0; i < scp.size(); i++)
	{
		for(int j = 0; j < scp[i].size();j++)
		{
			if(scp[i][j] == column)
			{
				num++;
				break;
			}
		}
	}
	return num;
}
