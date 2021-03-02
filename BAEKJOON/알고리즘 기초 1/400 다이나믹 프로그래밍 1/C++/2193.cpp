#include<iostream>

using namespace std;

long long dp[91];

long long gDp(int x)
{
	int i;
	dp[1] = 1;
	dp[2] = 1;
	dp[3] = 2;

	for (i = 4; i <= x; i++) {
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	
	return dp[x];
}

int main(void)
{
	int n;
	cin >> n;

	cout << gDp(n) << endl;

	return 0;
}