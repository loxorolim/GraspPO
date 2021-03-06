
#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <vector>
using namespace std;

int ** createMatrixFromFile(char * name);
vector<vector<int>> createSCPFromFile(const char* name, int* rowsSize, int* columnsSize);
int linesCoveredByColumn(int column);
int linesCoveredBySetOfColumns(int * columns);
void fillMatrixWithNumber(int** mat, int num, int rows, int columns);
