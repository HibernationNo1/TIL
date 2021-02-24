#include<iostream>

using namespace std;

#define endl '\n'

int dp[100001][3];
int m = 1000000009;

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int t;
	cin >> t;

	dp[1][0] = 1;
	dp[2][1] = 1;
	dp[3][0] = dp[3][1] = dp[3][2] = 1;


	for (int j = 4; j <= 100001; j++) {
		dp[j][0] = (dp[j - 1][1] + dp[j - 1][2]) % m;
		dp[j][1] = (dp[j - 2][0] + dp[j - 2][2]) % m;
		dp[j][2] = (dp[j - 3][0] + dp[j - 3][1]) % m;
	}

	for (int i = 0; i < t; i++) {
		int n, sum = 0;
		cin >> n;

		for (int j = 0; j < 3; j++) {
			sum = (sum + dp[n][j]) % m;
		}
		cout << sum << endl;
	}

	return 0;
}