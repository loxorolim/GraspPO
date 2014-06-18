
#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>      
using namespace std;

const float alpha = 0.8;
int matrixinte =0 ;
typedef struct tuple
{
	int pos, cSatisfied;
}duple;
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
vector<vector<int>> coverageMatrix(vector<vector<int>> &scp,int size)
{
	//int* cArray = (int*)malloc(sizeof(int)*size);
	vector<vector<int>> cMatrix;
	cMatrix.resize(size);

	for(int i = 0; i < scp.size(); i++)
	{
		for(int j = 0; j < scp[i].size();j++)
		{
			cMatrix[scp[i][j]].push_back(i);
		}	
	}
	return cMatrix;
	
}
void removeCovered(vector<vector<int>> &scp, vector<vector<int>> &cMatrix, int candidate, int* tam)
{
			
//	int r = 0;
	int newTam = *tam;
	for(int i = 0; i < cMatrix[candidate].size(); i ++)
	{
		int x = cMatrix[candidate][i];
		scp[cMatrix[candidate][i]].clear();	
		newTam--;
	//	scp.erase(scp.begin() + (cMatrix[candidate][i]-r));	
	//	r++;
	}
	*tam = newTam;
}
void eraseFromMatrix(vector<vector<int>> &cMatrix, int pos, int elem)
{
//	printf(" %d",cMatrix[pos].size());
	for(int i = 0; i < cMatrix[pos].size(); i++)
	{
		if(cMatrix[pos][i] == elem)
		{	
			cMatrix[pos].erase(cMatrix[pos].begin() + i);
			matrixinte++;
			break;
		}
	}

}
void updateMatrix(vector<vector<int>> &scp, vector<vector<int>> &cMatrix, int candidate)
{
//	printf("%d", cMatrix[candidate].size());
	while(cMatrix[candidate].size())
	{
		int x = cMatrix[candidate][0];
		//printf(" %d", scp[x].size());
		for(int j = 0 ; j < scp[x].size(); j++)
		{
			
			eraseFromMatrix(cMatrix,scp[x][j],x);
		}
	}

}

int* constructPhase(vector<vector<int>> scp, int size, int* solution)
{
	//vector<vector<int>> scpCopy = copyScp(scp);
	vector<vector<int>> cMatrix = coverageMatrix(scp, size);
	int tam = scp.size() ;
	while(tam > 0)
	{
		matrixinte = 0;
		vector<int> RCL = generateRCL(scp,cMatrix,size,solution);
		int cand = selectCandidate(RCL);
		solution[cand] = 1;
		vector<vector<int>> scpCopy = scp;
		removeCovered(scp,cMatrix,cand,&tam);
		updateMatrix(scpCopy, cMatrix, cand);
		//printf("MATRIX INTER: %d",matrixinte);
	//	printf("%d",tam);
	}

	return solution;
}

int selectCandidate(vector<int> RCL)
{
	int size = RCL.size();
	return RCL[rand()%size];

}
vector<int> generateRCL(vector<vector<int>> &scp,vector<vector<int>> &cMatrix, int size, int* solution)
{
	//int * numSatisfied = (int*)malloc(sizeof(int)*size);
	vector<duple> numSatisfied;
	int max = 0;
	for(int i = 0; i < size; i++)
	{
		if(solution[i] != 1)
		{
			//int s = clausesSatisfied(scp,i);
			int s = cMatrix[i].size();
			if(s > alpha*max && s != 0)
			{
				duple d;
				d.pos = i;
				d.cSatisfied = s;
				numSatisfied.push_back(d);
				if(s > max)
					max = s;
			}
		}
	}
	float L = alpha*max;
	vector<int> RCL;
	for(int i = 0; i < numSatisfied.size(); i++)
		if(numSatisfied[i].cSatisfied >= L)
			RCL.push_back(numSatisfied[i].pos);



	//free(numSatisfied);
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
