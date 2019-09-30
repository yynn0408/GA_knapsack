#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<Windows.h>
#define CHECK_TIME_START __int64 freq, start, end; if (QueryPerformanceFrequency((_LARGE_INTEGER*)&freq)) {QueryPerformanceCounter((_LARGE_INTEGER*)&start);
#define CHECK_TIME_END(a,b) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a=(float)((double)(end - start)/freq*1000); b=TRUE; } else b=FALSE;

using namespace std;

int maxv(int a, int b);
int knapsack(int W, vector<int>weight, vector<int>val, int n);
int main() {
	float Time;
	BOOL err;
	int n, W;
	cin >> n;
	vector<int> val;
	vector<int> weight;
	val.push_back(0);
	weight.push_back(0);//�ε��� 1�� ���߱� ����
	for (int i = 0; i < n; i++) {
		cout << "Enter weight and value" << endl;
		int v, wt;
		cin >> wt >> v;
		val.push_back(v);
		weight.push_back(wt);
	}
	cout << "Enter capacity" << endl;
	cin >> W;
	CHECK_TIME_START;
	srand((unsigned int)time(NULL));
	cout << knapsack(W, weight, val, n) << endl;
	CHECK_TIME_END(Time, err);
	cout << "DP-knapsack ����ð�:" << Time << "ms" << endl;
	cin >> W;
	return 0;
	//W: ���� ����/ weight: dp���� ����� ����/val: ������ ��ġ/ n:vector ũ�� 
}
int maxv(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int knapsack(int W, vector<int>weight, vector<int>val, int n) {
	//���������� item, W
	//int i, w;
	vector<vector<int>>P(n+2, vector<int>(W+2));//indexȮ��//�⺻���� 0���� �ʱ�ȭ��
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= W; j++) {
				P[i][j] = (weight[i] <= j) ? max(P[i - 1][j], P[i - 1][j-weight[i]] + val[i]): P[i - 1][j] ;
		}
	}
	
	return P[n][W];
}