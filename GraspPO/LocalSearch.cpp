#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include "LocalSearch.h"
#include "GraspPO.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>      

using namespace std;

float const p = 0.75;
float const p2 = 0.6;

int teste = 0;
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
void BestFlip(vector<vector<int>> &scp,vector<vector<int>> &cMatrix,int* solut, int size, int* csat, int* ncol)
{
	sol* solution = (sol*)malloc(sizeof(sol));
	solution->solution = solut;
	solution->clausesSatisfied = 0;
	solution->numberOfColumns = 0;
	int * cArray = counterArray(cMatrix,solution, scp.size(),size);
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
	*csat = bestClausesSatisfied;
	*ncol = bestNumberOfColumns;
	free(solution);
	free(cArray);

}
//void ImprovementFlip(vector<vector<int>> &scp,vector<vector<int>> &cMatrix,int* solut, int* bestClausesSatisfied,int* bestNumberOfColumns, int size)
//{
//	sol* solution = (sol*)malloc(sizeof(sol));
//	solution->solution = solut;
//	solution->clausesSatisfied = 0;
//	solution->numberOfColumns = 0;
//	int * cArray = counterArray(cMatrix,solution, scp.size(),size);
//	int pos = -1;
//	int* copiaSolut = (int*)malloc(sizeof(int)*size);
//	for(int i = 0; i < size; i ++)
//		copiaSolut[i] =  solut[i];
//	//vector<int> bestFlips;
//	//bestFlips.push_back(-1);
//	
//
//	for(int i = 0; i < size; i++)
//	{
//
//		copiaSolut[i] = !(copiaSolut[i]);
//		if(copiaSolut[i]) //era 0
//		{
//			int satisfied = solution->clausesSatisfied;			
//			for(int j = 0; j < cMatrix[i].size(); j++)
//			{
//				if(cArray[cMatrix[i][j]] == 0)
//				{
//					satisfied++;
//				}
//			}
//			if(satisfied > *bestClausesSatisfied)
//			{
//
//				*bestClausesSatisfied = satisfied;
//				*bestNumberOfColumns = solution->numberOfColumns+1;
//				//ImprovementFlip(scp,cMatrix,solut, bestClausesSatisfied,bestNumberOfColumns,  size);
//				pos = i;
//			}
//
//			
//		}
//		else //era 1
//		{
//			int satisfied = solution->clausesSatisfied;			
//			for(int j = 0; j < cMatrix[i].size(); j++)
//			{
//				if(cArray[cMatrix[i][j]] == 1)
//				{
//					satisfied--;
//				}
//			}
//		    if(satisfied == *bestClausesSatisfied)
//			{
//				if(solution->numberOfColumns-1 < *bestNumberOfColumns)
//				{
//
//					*bestClausesSatisfied = satisfied;
//					*bestNumberOfColumns = solution->numberOfColumns-1;
//					//ImprovementFlip(scp,cMatrix,solut, bestClausesSatisfied,bestNumberOfColumns,  size);
//					pos = i;
//				}
//
//			}
//		}
//		copiaSolut[i] = !(copiaSolut[i]);
//	}
//	if(pos != -1)
//		solut[pos] != solut[pos];
//	free(copiaSolut);
//	free(solution);
//	free(cArray);
//
//}
void BestTwoFlip(vector<vector<int>> &scp,vector<vector<int>> &cMatrix,int* solut, int size, int* csat, int* ncol)
{
	sol* solution = (sol*)malloc(sizeof(sol));
	solution->solution = solut;
	solution->clausesSatisfied = 0;
	solution->numberOfColumns = 0;
	int * cArray = counterArray(cMatrix,solution, scp.size(),size);
	//vector<int*> bestSolutions;
	//int* best = (int*)malloc(sizeof(int)*size);
	//for(int i = 0; i < size; i++)
	//	best[i] = solution->solution[i];
	//bestSolutions.push_back(best);
	//for(int i = 0; i < size; i ++)
	//{
	//	printf("%d",solution->solution[i]);
	//}
	vector<vector<int>> bestFlips;
	vector<int> ini;
	ini.push_back(-1);
	ini.push_back(-1);
	bestFlips.push_back(ini);
	int bestClausesSatisfied = solution->clausesSatisfied;
	int bestNumberOfColumns = solution->numberOfColumns;
//	int first = 1;
	for(int i = 0; i < size; i++)
	{
		//printf("PreMod:");
		//for(int z = 0; z < size; z++)
		//{
		//	printf("%d",solution->solution[z]);
		//}
		//printf("\n");
		solution->solution[i] = !(solution->solution[i]);
		//printf("ROLIM SAT I = %d\n",i);
//			for(int k = i+1; k < size; k++)
//			{
//				solution->solution[k] = !(solution->solution[k]);
				//printf("PosMod:");
				//for(int z = 0; z < size; z++)
				//{
				//	printf("%d",solution->solution[z]);
				//}
				//printf("\n");
				if(solution->solution[i]) //era 0
				{
					int* copyCArray = (int*)malloc(sizeof(int)*scp.size());
					for(int y = 0; y < scp.size(); y++)
						copyCArray[y] = cArray[y];


					int satisfied = solution->clausesSatisfied;			
					int bestNC = solution->numberOfColumns + 1;
					for(int j = 0; j < cMatrix[i].size(); j++)
					{
						if(copyCArray[cMatrix[i][j]] == 0)
						{
							satisfied++;
						}
						copyCArray[cMatrix[i][j]]++;
					}
					for(int k = i+1; k < size; k++)
					{
						solution->solution[k] = !(solution->solution[k]);
						if(solution->solution[k])
						{
							for(int j = 0; j < cMatrix[k].size(); j++)
							{

								if(copyCArray[cMatrix[k][j]] == 0)
								{
									satisfied++;
								}
								copyCArray[cMatrix[k][j]]++;
							}
							bestNC++;
						}
						else
						{
							for(int j = 0; j < cMatrix[k].size(); j++)
							{
								if(cArray[cMatrix[k][j]] == 1)
								{
									satisfied--;
								}
								copyCArray[cMatrix[k][j]]--;
							}
							bestNC--;

						}
					

						if(satisfied > bestClausesSatisfied)
						{
							bestFlips.clear();
							vector<int> pos;
							pos.push_back(i);
							pos.push_back(k);
							bestFlips.push_back(pos);
							bestClausesSatisfied = satisfied;
							bestNumberOfColumns = bestNC;
						}
						else if(satisfied == bestClausesSatisfied)
						{

							if(bestNC < bestNumberOfColumns)
							{
								bestFlips.clear();
								vector<int> pos;
								pos.push_back(i);
								pos.push_back(k);
								bestFlips.push_back(pos);
								bestClausesSatisfied = satisfied;
								bestNumberOfColumns = bestNC;
							}
							else if(bestNC == bestNumberOfColumns)
							{
								vector<int> pos;
								pos.push_back(i);
								pos.push_back(k);
								bestFlips.push_back(pos);
							}
							
						}
						solution->solution[k] = !(solution->solution[k]);
					}
					free(copyCArray);
				}
				else // ERA 1
				{
					//printf("PosMod:");
					//for(int z = 0; z < size; z++)
					//{
					//	printf("%d",solution->solution[z]);
					//}
					//printf("\n");
					int* copyCArray = (int*)malloc(sizeof(int)*scp.size());
					for(int y = 0; y < scp.size(); y++)
						copyCArray[y] = cArray[y];


					int satisfied = solution->clausesSatisfied;			
					int bestNC = solution->numberOfColumns -1;
					for(int j = 0; j < cMatrix[i].size(); j++)
					{
						if(copyCArray[cMatrix[i][j]] == 1)
						{
							satisfied--;
						}
						copyCArray[cMatrix[i][j]]--;
					}
					for(int k = i+1; k < size; k++)
					{
						solution->solution[k] = !(solution->solution[k]);
						if(solution->solution[k])
						{
							for(int j = 0; j < cMatrix[k].size(); j++)
							{

								if(copyCArray[cMatrix[k][j]] == 0)
								{
									satisfied++;
								}
								copyCArray[cMatrix[k][j]]++;
							}
							bestNC++;
						}
						else
						{
							for(int j = 0; j < cMatrix[k].size(); j++)
							{
								if(cArray[cMatrix[k][j]] == 1)
								{
									satisfied--;
								}
								copyCArray[cMatrix[k][j]]--;
							}
							bestNC--;

						}
				//	}
						if(satisfied > bestClausesSatisfied)
						{
							bestFlips.clear();
							vector<int> pos;
							pos.push_back(i);
							pos.push_back(k);
							bestFlips.push_back(pos);
							bestClausesSatisfied = satisfied;
							bestNumberOfColumns = bestNC;
						}
						else if(satisfied == bestClausesSatisfied)
						{
							if(bestNC < bestNumberOfColumns)
							{
								bestFlips.clear();
								vector<int> pos;
								pos.push_back(i);
								pos.push_back(k);
								bestFlips.push_back(pos);
								bestClausesSatisfied = satisfied;
								bestNumberOfColumns = bestNC;
							}
							else if(bestNC == bestNumberOfColumns)
							{
								vector<int> pos;
								pos.push_back(i);
								pos.push_back(k);
								bestFlips.push_back(pos);
							}

							
						}
						solution->solution[k] = !(solution->solution[k]);
					}
					free(copyCArray);
				}				
//				solution->solution[k] = !(solution->solution[k]);
//			}

		
		solution->solution[i] = !(solution->solution[i]);

	}

 	int pos = rand()%bestFlips.size();
	if(bestFlips[pos][0] != -1)
	{
		solution->solution[bestFlips[pos][0]] = !solution->solution[bestFlips[pos][0]];
		solution->solution[bestFlips[pos][1]] = !solution->solution[bestFlips[pos][1]];
	}
	*csat = bestClausesSatisfied;
	*ncol = bestNumberOfColumns;
	free(solution);
	free(cArray);

}
void RandomFlip(int * solution, int size)
{		
	int pos = rand()%size;
	solution[pos] = !solution[pos];
}
void RandomDualFlip(int * solution, int size)
{		
	int pos = rand()%size;
	solution[pos] = !solution[pos];
	pos = rand()%size;
	solution[pos] = !solution[pos];
}
void RandomTripleFlip(int * solution, int size)
{		

	int pos = rand()%size;
	solution[pos] = !solution[pos];
	pos = rand()%size;
	solution[pos] = !solution[pos];
	pos = rand()%size;
	solution[pos] = !solution[pos];
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



void WalkSat(vector<vector<int>> &scp, int * solution, int size)
{
//	int* newSolution;
	vector<vector<int>> cMatrix = coverageMatrix(scp,size);
	int bestClausesSatisfied;
	int bestNumberOfColumns;
	evaluateSolution(scp, solution, size, &bestClausesSatisfied, &bestNumberOfColumns);
	int* solCopy = (int*)malloc(sizeof(int)*size);
	for(int i = 0; i < size; i ++)
		solCopy[i] = solution[i];
	for(int i = 0; i < 10*size; i++)
	{
		
		float r = rand()%100 + 1;
		r = r/100;
		if(r < p)
		{
			int cSatisfied;
			int nColumns;
			BestFlip(scp,cMatrix,solution,size,&cSatisfied,&nColumns);
			if(cSatisfied > bestClausesSatisfied)
			{
				bestClausesSatisfied = cSatisfied;
				bestNumberOfColumns = nColumns;
				for(int i = 0; i < size; i ++)
					solCopy[i] = solution[i];
			}
			else if(cSatisfied == bestClausesSatisfied)
			{
				if(nColumns < bestNumberOfColumns)
					for(int i = 0; i < size; i ++)
						solCopy[i] = solution[i];
			}

		}
		else
			RandomFlip(solution,size);
		
		
			
//		free(solution);
//		solution = newSolution;

//		printf("\n");

	}
	for(int i = 0; i < size; i ++)
	solution[i] = solCopy[i] ;
	free(solCopy);
	for(int i = 0; i < cMatrix.size(); i++)
	{
		cMatrix[i].clear();
	}
	cMatrix.clear();
//	return solution;
}
void RolimSat(vector<vector<int>> &scp, int * solution, int size)
{
//	int* newSolution;
	int bestClausesSatisfied;
	int bestNumberOfColumns;
	evaluateSolution(scp, solution, size, &bestClausesSatisfied, &bestNumberOfColumns);
	int* solCopy = (int*)malloc(sizeof(int)*size);
	for(int i = 0; i < size; i ++)
		solCopy[i] = solution[i];
	vector<vector<int>> cMatrix = coverageMatrix(scp,size);
	for(int i = 0; i < size/10; i++)
	{
		
		float r = rand()%100 + 1;
		r = r/100;
		if(r < p2)
		{
			int cSatisfied;
			int nColumns;
			BestTwoFlip(scp,cMatrix,solution,size,&cSatisfied,&nColumns);
			if(cSatisfied > bestClausesSatisfied)
			{
				bestClausesSatisfied = cSatisfied;
				bestNumberOfColumns = nColumns;
				for(int i = 0; i < size; i ++)
					solCopy[i] = solution[i];
			}
			else if(cSatisfied == bestClausesSatisfied)
			{
				if(nColumns < bestNumberOfColumns)
					for(int i = 0; i < size; i ++)
						solCopy[i] = solution[i];
			}
//			BestFlip(scp,cMatrix,solution,size);
		}
		else
		{
			RandomFlip(solution,size);
			//if(r>= p2 && r < 0.90)
			//	RandomDualFlip(solution,size);
			//else
			//	RandomTripleFlip(solution,size);
		}
//		printf("%d\n",i);
		

	}
		for(int i = 0; i < cMatrix.size(); i++)
		{
			cMatrix[i].clear();
		}
		cMatrix.clear();

}