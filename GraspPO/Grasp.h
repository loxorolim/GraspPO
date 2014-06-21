#include "SetCoveringMethods.h"
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;


int clausesSatisfied(vector<vector<int>> &scp, int column);
int* initialSolution(int size);
int selectCandidate(vector<int> RCL);
vector<int> generateRCL(vector<vector<int>> &scp,vector<vector<int>> &cMatrix, int size, int* solution);
vector<vector<int>> copyScp(vector<vector<int>> &scp);
int* constructPhase(vector<vector<int>> scp, int size, int* solution);
void removeCovered(vector<vector<int>> &scp,vector<vector<int>> &cMatrix, int candidate, int* tam);
vector<vector<int>> coverageMatrix(vector<vector<int>> &scp,int size);