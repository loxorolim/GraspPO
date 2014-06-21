// GraspPO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include "LocalSearch.h"
#include <time.h> 
#include <vector>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
using namespace std;

int const iterations = 200;
void evaluateSolution(vector<vector<int>> &scp, int * solution, int size, int* cSatisfied, int* numColumns)
{
	int num = 0;
	int numC = 0;
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
	for(int i = 0; i < size; i ++)
		if(solution[i])
			numC++;

	*numColumns = numC;
	*cSatisfied = num;
}
int* metaheuristic(vector<vector<int>> &scp,int size, double* totalTimeR, double* bestSolutionTimeR,int* cSatisfied,int* nColumns)
{
	int* solution = initialSolution(size);
	int* newSolution;
	time_t start = time(0);
	double bestSolutionTime;
	double totalTime;
	for(int i = 0; i < iterations; i++)
	{
		newSolution = initialSolution(size);
		newSolution = constructPhase(scp, size, newSolution);
		WalkSat(scp,newSolution,size);
		printf("Iteration %d \n", i);			 
		//for(int i = 0; i < size; i++)
		//{
		//	printf("%d",newSolution[i]);
		//	
		//}
		if(isBetterSolution(scp, newSolution, solution, size) == 1) //MUDAAAAAAAR
		{
			free(solution);
			solution = newSolution;
			bestSolutionTime = difftime( time(0), start);
			int cS = 0, nC =0;
			evaluateSolution(scp,solution,size, &cS, &nC);
			printf("%f \n", bestSolutionTime);
			printf("%d \n", cS);
			printf("%d \n", nC);
		}
		else
		{
			free(newSolution);
		}
		

	}
	totalTime = difftime( time(0), start);
	*bestSolutionTimeR = bestSolutionTime;
	*totalTimeR = totalTime;

	evaluateSolution(scp,solution,size, cSatisfied, nColumns);
	printf("%f \n", totalTime);
	return solution;
}
void resultsToFile(FILE* file,double totalTime, double bestSolutionTime, int cSatisfied, int nColumns, int instance)
{
	//	FILE *file;
	//	vector<vector<int>> ret;

	//	fopen_s(&file,name, "w");
		if (file)
		{
			fprintf(file, "Instância: %d\n", instance);
			fprintf(file, "Linhas cobertas: %d\n", cSatisfied);
			fprintf(file, "Número de colunas na solução: %d\n", nColumns);
			fprintf(file, "Tempo para achar melhor solução: %f\n", bestSolutionTime);
			fprintf(file, "Tempo total de execução da instância: %f\n", totalTime);
			//fclose(file);
		}
}
void saveResults(string name)
{
	int columnsSize = -1;
	int rowsSize = -1;
	int tam = name.length();
	string fileName = name;
	string resultName = name;
	fileName += ".txt";
	resultName += "Result.txt";
	
	const char* fileNameC = fileName.c_str();
	const char* resultNameC = resultName.c_str();
	
	vector<vector<int>> scp = createSCPFromFile(fileNameC, &rowsSize, &columnsSize);
	int i,j;
	int x = scp.size();
	for(i = 0;i<scp.size();i++)
	{
		printf("%d :",i);
		for(j = 0; j < scp[i].size();j++)
		{
			printf("%d ",scp[i][j]);
		}
		printf("\n");
	}
	double totalTime;
	double bestSolutionTime;
	int cSatisfied;
	int nColumns;
	FILE* file;
	fopen_s(&file,resultNameC, "w");
	if(file)
	{
		for(int i = 1; i <= 5 ; i++)
		{
			int* sol = metaheuristic(scp,columnsSize, &totalTime, &bestSolutionTime,&cSatisfied,&nColumns);
			resultsToFile(file,totalTime,bestSolutionTime,cSatisfied,nColumns,i);
		}
	}
	fclose(file);
}
int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL));
	//saveResults("scpcyc07");
//	saveResults("scpcyc07");
	//saveResults("scp51");
	//saveResults("scp61");
	//saveResults("scpa1");
	//saveResults("scpclr10");
		//int columnsSize = -1;
	//int rowsSize = -1;
	
	//vector<vector<int>> teste = createSCPFromFile("scp41.txt", &rowsSize, &columnsSize);
	//int i,j;
	//int x = teste.size();
	//for(i = 0;i<teste.size();i++)
	//{
	//	printf("%d :",i);
	//	for(j = 0; j < teste[i].size();j++)
	//	{
	//		printf("%d ",teste[i][j]);
	//	}
	//	printf("\n");
	//}

//
////	int* cArray = coverageArray(teste,columnsSize);
//	int* sol = metaheuristic(teste,columnsSize);
//	for(int i = 0; i < columnsSize; i++)
//	{
//		printf("%d",sol[i]);
//	}
//	free(sol);
	//for(i = 0;i<teste.size();i++)
	//{
	//	teste[i].clear();
	//	printf("\n");
	//}
	//teste.clear();
	
	//int * solution = constructPhase(teste, columnsSize);
	//WalkSat(teste, solution, columnsSize);
	//int * ini = initialSolution(columnsSize);
	//vector<int> RCL = generateRCL(teste, columnsSize,ini);
	//int cand = selectCandidate(RCL);
//	scanf_s("%d");
	_CrtDumpMemoryLeaks();
	return 0;
}


