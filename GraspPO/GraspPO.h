#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>      
using namespace std;

void evaluateSolution(vector<vector<int>> &scp, int * solution, int size, int* cSatisfied, int* numColumns);