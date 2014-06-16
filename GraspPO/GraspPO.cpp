// GraspPO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include <time.h> 
#include <vector>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	srand (time(NULL));
	int columnsSize = -1;
	int rowsSize = -1;
	vector<vector<int>> teste = createSCPFromFile("teste.txt", &rowsSize, &columnsSize);
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
	constructPhase(teste, columnsSize);
	//int * ini = initialSolution(columnsSize);
	//vector<int> RCL = generateRCL(teste, columnsSize,ini);
	//int cand = selectCandidate(RCL);
	scanf_s("%d");
	return 0;
}

