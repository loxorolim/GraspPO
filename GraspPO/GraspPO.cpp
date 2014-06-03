// GraspPO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SetCoveringMethods.h"
#include <vector>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	vector<vector<int>> teste = createSCPFromFile("teste.txt");
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
	scanf_s("%d");
	return 0;
}

