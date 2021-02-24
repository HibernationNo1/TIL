#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	vector<int> p(n);
	vector<int> dp(n);

	for (int i = 0; i < n; i++) {
		cin >> p[i];
		dp[i] = 10000;
	}
	dp[0] = p[0];

	for (int i = 1; i < n; i++) {
		for (int j = 0; j <= i - 1; j++) {
			dp[i] = min(dp[i], dp[j] + p[i - 1 - j]);
		}
		dp[i] = min(dp[i], p[i]);
	}

	cout << dp[n - 1] << endl;

	return 0;
}
