#include<iostream>
#include<time.h>
#include"define.h"
#include"knapsack.h"
#include<ctime>
#include<Windows.h>
#include<cstdlib>


#define CHECK_TIME_START __int64 freq, start, end; if (QueryPerformanceFrequency((_LARGE_INTEGER*)&freq)) {QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a,b) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a=(float)((double)(end - start)/freq*1000); b=TRUE; } else b=FALSE;
using namespace std;
knapsack* gaknap;

int main() {
	float Time;
	BOOL err;
	gaknap = new knapsack(CROSSOVER_RATE, MUTATION_RATE, POP_SIZE, CHROMO_LENGTH, GENE_LENGTH);
	CHECK_TIME_START;
	srand((unsigned int)time(NULL));
	gaknap->gamain();
	CHECK_TIME_END(Time, err);
	cout << "GA-knapsack 수행시간:" << Time << "ms" << endl;


	int a;
	cin >> a;
	return 0;
}