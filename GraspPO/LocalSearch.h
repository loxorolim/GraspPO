#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>      
using namespace std;

typedef struct solut{
	int clausesSatisfied;
	int numberOfColumns;
	int* solution;
	
}sol;

void BestFlip(vector<vector<int>> &scp,vector<vector<int>> &cMatrix,int* cArray, sol* solution, int size);
void RandomFlip(int * solution, int size);
int numOfColumnsInSolution(int * solution, int size);
int clausesSatisfiedBySolution(vector<vector<int>> &scp, int * solution, int size);
int isBetterSolution(vector<vector<int>> &scp, int * newSolution, int * solution, int size);
void WalkSat(vector<vector<int>> &scp, int * solution, int size);
void RolimSat(vector<vector<int>> &scp, int * solution, int size);
