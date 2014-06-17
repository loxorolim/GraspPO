#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include "LocalSearch.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>      
using namespace std;

float const p = 0.75;


int* BestFlip(vector<vector<int>> scp, int* solution, int size)
{
	vector<int*> bestSolutions;
	int* best = (int*)malloc(sizeof(int)*size);
	for(int i = 0; i < size; i++)
		best[i] = solution[i];
	bestSolutions.push_back(best);
	
	for(int i = 0; i < size; i++)
	{
		//for(int i = 0; i < size; i++)
		//{
		//	printf("%d",bestSolutions[0][i]);
		//}
		//printf("\n");

		solution[i] = !solution[i];
		int isBetter = isBetterSolution(scp, solution, bestSolutions[0], size);
		if(isBetter == 1)
		{
			for(int i = 0; i < size; i++)
				best[i] = solution[i];	
			for(int i = 1; i < bestSolutions.size(); i++)
			{
				free(bestSolutions[i]);
				bestSolutions.erase(bestSolutions.begin() + i);
			}
			
		}
		if(isBetter == 2)
		{
			int * equalBest = (int*)malloc(sizeof(int)*size);
			for(int i = 0; i < size; i++)
				equalBest[i] = solution[i];
			bestSolutions.push_back(equalBest);
		}				
		solution[i] = !solution[i];
	}
	int pos = rand()%bestSolutions.size();
	for(int i = 0; i < bestSolutions.size(); i++)
		if(i != pos)		
			free(bestSolutions[i]);
	int * ret = bestSolutions[pos];
	bestSolutions.clear();
	return ret;

}
int* RandomFlip(int * solution, int size)
{		
	int* ret = (int*)malloc(sizeof(int)*size);
	for(int i = 0; i < size; i++)
		ret[i] = solution[i];
	int pos = rand()%size;
	ret[pos] = !ret[pos];
	return ret;
}
int numOfColumnsInSolution(int * solution, int size)
{
	int ret = 0;
	for(int i = 0; i < size; i++)
		if(solution[i] == 1)
			ret++;
	return ret;
}
int clausesSatisfiedBySolution(vector<vector<int>> scp, int * solution, int size)
{
	int num = 0;
	for(int i = 0;i < scp.size(); i++)
	{
			for(int j = 0; j < scp[i].size(); j++)
			{

				for(int k = 0; k < size; k++)
				{
					if(solution[k] == 1)
					{
						if(scp[i][j] == k)
						{
							j = scp[i].size();
							num++;
							break;
						}
					}
					
				}
				
			}
		
	}
	return num;
}
int isBetterSolution(vector<vector<int>> scp, int * newSolution, int * solution, int size)
{
	//2 se são iguais
	//1 se é melhor
	//0 se é pior
	int numNewSat = clausesSatisfiedBySolution(scp,newSolution,size);
    int numSat = clausesSatisfiedBySolution(scp,solution,size);
	if(numNewSat > numSat)
		return 1;
	else if(numNewSat < numSat)
		return 0;
	else if(numNewSat == numSat)
	{
		int a = numOfColumnsInSolution(newSolution,size);
		int b = numOfColumnsInSolution(solution,size);
		if(a > b)
			return 0;
		if(a < b)
			return 1;
		if(a == b )
			return 2;
	}	
}


int* WalkSat(vector<vector<int>> scp, int * solution, int size)
{
	int* newSolution;


	for(int i = 0; i < 10*size; i++)
	{
		
		float r = rand()%100 + 1;
		r = r/100;
		if(r < p)
			newSolution = BestFlip(scp,solution,size);
		else
			newSolution = RandomFlip(solution,size);
		
		
			
		free(solution);
		solution = newSolution;
		//for(int i = 0; i < size; i++)
		//{
		//	printf("%d",solution[i]);
		//}
		//printf("\n");

	}
	return solution;
}