#include<iostream>
#include<algorithm>

using namespace std;

 int dp[1][100001]; // [0 또는 1][n의 개수]  0 또는 1에서 시작할때의 최대값
 int buff[1][100001]; // [0 또는 1][n의 개수] 실제 칸에 들어갈 수

 int gDp(int x)
{
	int sum;
	dp[0][0] = buff[0][0]; // dp[0][0]
	dp[1][0] = buff[1][0];
	dp[0][1] = buff[1][0] + buff[0][1];
	dp[1][1] = buff[0][0] + buff[1][1];
	
	for (int i = 2; i < x; i++) {
		dp[0][i] = buff[0][i] + max(dp[1][i - 1], dp[1][i - 2]);
		dp[1][i] = buff[1][i] + max(dp[0][i - 1], dp[0][i - 2]);
	}
	

	return sum = max(dp[0][x-1], dp[1][x-1]);
}

int main(void)
{
	int t, n, i, j;
	cin >> t;
	for (i = 1; i <= t; i++) {
		cin >> n;
		for (j = 0; j < n; j++) {
			cin >> buff[0][j];
		}
		for (j = 0; j < n; j++) {
			cin >> buff[1][j];
		}
		cout << gDp(n) << endl;
	}

	

	return 0;
}