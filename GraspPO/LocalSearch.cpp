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

int teste = 0;
void BestFlip(vector<vector<int>> &scp,vector<vector<int>> &cMatrix, int* cArray, sol* solution, int size)
{
	//vector<int*> bestSolutions;
	//int* best = (int*)malloc(sizeof(int)*size);
	//for(int i = 0; i < size; i++)
	//	best[i] = solution->solution[i];
	//bestSolutions.push_back(best);
	//for(int i = 0; i < size; i ++)
	//{
	//	printf("%d",solution->solution[i]);
	//}
	vector<int> bestFlips;
	bestFlips.push_back(-1);
	int bestClausesSatisfied = solution->clausesSatisfied;
	int bestNumberOfColumns = solution->numberOfColumns;
//	int first = 1;
	for(int i = 0; i < size; i++)
	{
		//for(int i = 0; i < size; i++)
		//{
		//	printf("%d",bestSolutions[0][i]);
		//}
		//printf("\n");

		solution->solution[i] = !(solution->solution[i]);
//		int isBetter = 0;

		if(solution->solution[i]) //era 0
		{
			int satisfied = solution->clausesSatisfied;			
			for(int j = 0; j < cMatrix[i].size(); j++)
			{
				if(cArray[cMatrix[i][j]] == 0)
				{
					satisfied++;
				}
			}
			if(satisfied > bestClausesSatisfied)
			{
				bestFlips.clear();
				bestFlips.push_back(i);
				bestClausesSatisfied = satisfied;
				bestNumberOfColumns = solution->numberOfColumns+1;
			}
			else if(satisfied == bestClausesSatisfied)
			{
				if(solution->numberOfColumns+1 == bestNumberOfColumns)
					bestFlips.push_back(i);
			}
			
		}
		else //era 1
		{
			int satisfied = solution->clausesSatisfied;			
			for(int j = 0; j < cMatrix[i].size(); j++)
			{
				if(cArray[cMatrix[i][j]] == 1)
				{
					satisfied--;
				}
			}
		    if(satisfied == bestClausesSatisfied)
			{
				if(solution->numberOfColumns-1 < bestNumberOfColumns)
				{
					bestFlips.clear();
					bestFlips.push_back(i);
					bestClausesSatisfied = satisfied;
					bestNumberOfColumns = solution->numberOfColumns-1;
				}
				if(solution->numberOfColumns-1 == bestNumberOfColumns)
					bestFlips.push_back(i);
			}
		}
		solution->solution[i] = !(solution->solution[i]);
	}
	int pos = rand()%bestFlips.size();
	if(bestFlips[pos]!=-1)
		solution->solution[bestFlips[pos]] = !solution->solution[bestFlips[pos]];


}
void ImprovementFlip(vector<vector<int>> &scp,vector<vector<int>> &cMatrix, int* cArray, sol* solution, int size)
{
	//vector<int*> bestSolutions;
	//int* best = (int*)malloc(sizeof(int)*size);
	//for(int i = 0; i < size; i++)
	//	best[i] = solution->solution[i];
	//bestSolutions.push_back(best);
	//for(int i = 0; i < size; i ++)
	//{
	//	printf("%d",solution->solution[i]);
	//}
	vector<int> bestFlips;
	bestFlips.push_back(-1);
	int bestClausesSatisfied = solution->clausesSatisfied;
	int bestNumberOfColumns = solution->numberOfColumns;
//	int first = 1;
	for(int i = 0; i < size; i++)
	{
		//for(int i = 0; i < size; i++)
		//{
		//	printf("%d",bestSolutions[0][i]);
		//}
		//printf("\n");

		solution->solution[i] = !(solution->solution[i]);
//		int isBetter = 0;

		if(solution->solution[i]) //era 0
		{
			int satisfied = solution->clausesSatisfied;			
			for(int j = 0; j < cMatrix[i].size(); j++)
			{
				if(cArray[cMatrix[i][j]] == 0)
				{
					satisfied++;
				}
			}
			if(satisfied > bestClausesSatisfied)
			{
				bestFlips.clear();
				bestFlips.push_back(i);
				bestClausesSatisfied = satisfied;
				bestNumberOfColumns = solution->numberOfColumns+1;
			}
			else if(satisfied == bestClausesSatisfied)
			{
				if(solution->numberOfColumns+1 == bestNumberOfColumns)
					bestFlips.push_back(i);
			}
			
		}
		else //era 1
		{
			int satisfied = solution->clausesSatisfied;			
			for(int j = 0; j < cMatrix[i].size(); j++)
			{
				if(cArray[cMatrix[i][j]] == 1)
				{
					satisfied--;
				}
			}
		    if(satisfied == bestClausesSatisfied)
			{
				if(solution->numberOfColumns-1 < bestNumberOfColumns)
				{
					bestFlips.clear();
					bestFlips.push_back(i);
					bestClausesSatisfied = satisfied;
					bestNumberOfColumns = solution->numberOfColumns-1;
				}
				if(solution->numberOfColumns-1 == bestNumberOfColumns)
					bestFlips.push_back(i);
			}
		}
		solution->solution[i] = !(solution->solution[i]);
	}
	int pos = rand()%bestFlips.size();
	if(bestFlips[pos]!=-1)
		solution->solution[bestFlips[pos]] = !solution->solution[bestFlips[pos]];


}
void RandomFlip(int * solution, int size)
{		
	//int* ret = (int*)malloc(sizeof(int)*size);
//	for(int i = 0; i < size; i++)
//		ret[i] = solution[i];
	int pos = rand()%size;
	solution[pos] = !solution[pos];
//	return ret;
}
void RandomDualFlip(int * solution, int size)
{		
	//int* ret = (int*)malloc(sizeof(int)*size);
//	for(int i = 0; i < size; i++)
//		ret[i] = solution[i];
	int pos = rand()%size;
	solution[pos] = !solution[pos];
	pos = rand()%size;
	solution[pos] = !solution[pos];
//	return ret;
}
void RandomTripleFlip(int * solution, int size)
{		
	//int* ret = (int*)malloc(sizeof(int)*size);
//	for(int i = 0; i < size; i++)
//		ret[i] = solution[i];
	int pos = rand()%size;
	solution[pos] = !solution[pos];
	pos = rand()%size;
	solution[pos] = !solution[pos];
	pos = rand()%size;
	solution[pos] = !solution[pos];
//	return ret;
}
int numOfColumnsInSolution(int * solution, int size)
{
	int ret = 0;
	for(int i = 0; i < size; i++)
		if(solution[i] == 1)
			ret++;
	return ret;
}
int clausesSatisfiedBySolution(vector<vector<int>> &scp, int * solution, int size)
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
					teste++;
					
				}
				
			}
		
	}
	return num;
}
int isBetterSolution(vector<vector<int>> &scp, int * newSolution, int * solution, int size)
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

int* counterArray(vector<vector<int>> &cMatrix, sol* solution, int rowSize,int size)
{
	int* cArray = (int*)malloc(sizeof(int)*rowSize);
	for(int i = 0; i < rowSize; i ++)
	{
		cArray[i] = 0;
	}
	for(int i = 0; i < size; i++)
	{

		if(solution->solution[i])
		{
			solution->numberOfColumns++;
			for(int j = 0; j < cMatrix[i].size(); j++)
			{
				if(cArray[cMatrix[i][j]] == 0)
					solution->clausesSatisfied++;
				cArray[cMatrix[i][j]]++;
				
			}
		}
	}
	return cArray;
}

void WalkSat(vector<vector<int>> &scp, int * solution, int size)
{
//	int* newSolution;
	vector<vector<int>> cMatrix = coverageMatrix(scp,size);
	for(int i = 0; i < 10*size; i++)
	{
		
		float r = rand()%100 + 1;
		r = r/100;
		if(r < p)
		{
			//for(int i = 0; i < size; i++)
			//{
			//	printf("%d",solution[i]);
			//}
			sol* solut = (sol*)malloc(sizeof(sol));
			solut->solution = solution;
			solut->clausesSatisfied = 0;
			solut->numberOfColumns = 0;
			int * cArray = counterArray(cMatrix,solut, scp.size(),size);
			

			BestFlip(scp,cMatrix,cArray,solut,size);

			free(cArray);
			//free(solut->solution);
			free(solut);
		}
		else
			RandomFlip(solution,size);
		
		
			
//		free(solution);
//		solution = newSolution;

//		printf("\n");

	}
		for(int i = 0; i < cMatrix.size(); i++)
		{
			cMatrix[i].clear();
		}
		cMatrix.clear();
//	return solution;
}