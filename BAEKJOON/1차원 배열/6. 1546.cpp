#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{ 
	int N;
	cin >> N;
	double sum = 0;
	double* num = new double[N + 1];
	double *score = new double[N+1];

	for (int i = 1; i <= N; i++)
	{
		cin >> score[i];
	}

	sort(score +1, score + N+1, greater<int>());
	

	for (int i = 1; i <= N; i++)
	{
		num[i] = score[i] / score[1] * 100;     // num대신 score을 넣으면 계산식이 적용 안됨.
		sum = sum + num[i];
	}

	cout << sum / N << endl;

	delete score;

	return 0;
}