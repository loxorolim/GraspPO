
#include "SetCoveringMethods.h"
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
using namespace std;


void fillMatrixWithNumber(int** mat, int num, int rows, int columns)
{
	int i, j;
	for (i = 0; i < rows;i++)
		for (j = 0; j < columns; j++)
			mat[i][j] = num;
}
void printMatrix(int **mat, int rows, int columns)
{
	int i, j;
	for (i = 0; i < rows; i++)
	{
		for (j = 0; j < columns; j++)
			printf("%d", mat[i][j]);
		printf("\n");
	}
		
			
}

int** createMatrixFromFile(char* name) 
{
	FILE *file;
	int** ret = NULL;
	fopen_s(&file,name, "r");
	if (file)
	{
		int rows,columns,i;		
		fscanf_s(file, " %d  %d", &rows,&columns);
	    ret = (int**)malloc(sizeof(int*)*rows);
		for (i = 0; i < rows; i++)
			ret[i] = (int*)malloc(sizeof(int)*columns);
		fillMatrixWithNumber(ret, 0, rows, columns);
		for (i = 0; i < columns; i++)				
			fscanf_s(file, " %d");		
		for (i = 0; i < rows; i++)
		{
			int num,j;
			fscanf_s(file, " %d",&num);
			for (j = 0; j < num; j++)
			{
				int val;
				fscanf_s(file, " %d", &val);
				ret[i][val-1] = 1;
			}
		}
		fclose(file);
		printMatrix(ret, rows, columns);
	}
	
	return ret;
}
vector<vector<int>> createSCPFromFile(char* name) 
{
	FILE *file;
	vector<vector<int>> ret;
	fopen_s(&file,name, "r");
	if (file)
	{
		int rows,columns,i;		
		fscanf_s(file, " %d  %d", &rows,&columns);
		
		
		
		

		for (i = 0; i < columns; i++)		// LE VALORES QUE NÃO SERÃO UTILIZADOS		
			fscanf_s(file, " %d");		

		for (i = 0; i < rows; i++)
		{
			vector<int> col;
			int num,j;
			fscanf_s(file, " %d",&num);
			for (j = 0; j < num; j++)
			{
				int val;
				fscanf_s(file, " %d", &val);
				col.push_back(val-1);
				//ret[i][val-1] = 1;
			}
			ret.push_back(col);
		}
		fclose(file);

	}
	
	return ret;
}
