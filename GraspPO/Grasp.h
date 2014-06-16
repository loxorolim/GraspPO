#include "SetCoveringMethods.h"
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;


int clausesSatisfied(vector<vector<int>> scp, int column);
int* initialSolution(int size);
int selectCandidate(vector<int> RCL);
vector<int> generateRCL(vector<vector<int>> scp, int size, int* solution);
vector<vector<int>> copyScp(vector<vector<int>> scp);
void constructPhase(vector<vector<int>> scp, int size);
vector<vector<int>> removeCovered(vector<vector<int>> scp, int candidate);