#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
	int t,n, i, j;
	cin >> t;

	long long dp[101];
	dp[0] = dp[1] = dp[2] = 1;
	dp[3] = dp[4] = 2;

	for (i = 1; i <= t; i++)
	{
		cin >> n;
		
		for (j = 5; j < n; j++) {
			dp[j] = dp[j - 1] + dp[j - 5];
		}

		cout << dp[n - 1] << endl;
	}


	return 0;
}