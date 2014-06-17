#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>      
using namespace std;


int* BestFlip(vector<vector<int>> scp, int* solution, int size);
int* RandomFlip(int * solution, int size);
int numOfColumnsInSolution(int * solution, int size);
int clausesSatisfiedBySolution(vector<vector<int>> scp, int * solution, int size);
int isBetterSolution(vector<vector<int>> scp, int * newSolution, int * solution, int size);
int* WalkSat(vector<vector<int>> scp, int * solution, int size);
