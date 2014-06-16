#include "stdafx.h"
#include "SetCoveringMethods.h"
#include "Grasp.h"
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <time.h>      
using namespace std;

int const p = 0.75;
int const MAXFLIPS = 10;

void BestFlip(int* solution, int size)
{

}
void RandomFlip(int * solution, int size)
{

}
void WalkSat(int * solution, int size)
{
	for(int i = 0; i < MAXFLIPS; i++)
	{
		int r = rand();
		if(r < p)
			BestFlip(solution,size);
		else
			RandomFlip(solution,size);
	}
}