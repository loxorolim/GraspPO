// GraspPO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include "LocalSearch.h"
#include <time.h> 
#include <vector>
using namespace std;

int const iterations = 500;
int* metaheuristic(vector<vector<int>> scp,int size)
{
	int* solution = initialSolution(size);
	int* newSolution;
	for(int i = 0; i < iterations; i++)
	{
		newSolution = initialSolution(size);
		newSolution = constructPhase(scp, size, newSolution);
	//	newSolution = WalkSat(scp,newSolution,size);
		if(isBetterSolution(scp, newSolution, solution, size) == 1)
		{
			free(solution);
			solution = newSolution;
		}
	}
	return solution;
}
int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL));
	int columnsSize = -1;
	int rowsSize = -1;
	
	vector<vector<int>> teste = createSCPFromFile("scp41.txt", &rowsSize, &columnsSize);
	int i,j;
	int x = teste.size();
	for(i = 0;i<teste.size();i++)
	{
		printf("%d :",i);
		for(j = 0; j < teste[i].size();j++)
		{
			printf("%d ",teste[i][j]);
		}
		printf("\n");
	}


	int* sol = metaheuristic(teste,columnsSize);
	for(int i = 0; i < columnsSize; i++)
	{
		printf("%d",sol[i]);
	}
	//int * solution = constructPhase(teste, columnsSize);
	//WalkSat(teste, solution, columnsSize);
	//int * ini = initialSolution(columnsSize);
	//vector<int> RCL = generateRCL(teste, columnsSize,ini);
	//int cand = selectCandidate(RCL);
	scanf_s("%d");
	return 0;
}


