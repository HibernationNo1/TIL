#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int gValue = 1000000000;
int dp[202][202];

int main(void)
{
	int n, k, i, j, x;
	cin >> n >> k;


	for (i = 0; i <= n; i++) {
		dp[1][i] = 1;
		dp[2][i] = i + 1;
	}
	
	for (i = 3; i <= k; i++) {
		for (j = 0; j <= n; j++) {
			for (x = 0; x <= j; x++)
			{
				dp[i][j] = (dp[i][j] + dp[i - 1][x]) % gValue;
			}
		}
	}
	
	cout << dp[k][n] << endl;



	return 0;
}