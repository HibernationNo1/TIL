#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
	int n, i, j;
	cin >> n;
	vector<int> dp(n+1);

	dp[0] = 1;
	dp[2] = 3;
	dp[4] = 11;
	for (i = 6; i<= n; i += 2) {
		dp[i] = (dp[i-2]*3);
		for (j = 2; j <= i / 2; j++) {
			dp[i] += dp[i - 2 * j] * 2;
		}
	}

	cout << dp[n] << endl;

	return 0;
}