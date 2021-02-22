#include <iostream>
#include <algorithm>
using namespace std;

int dp[1000001];

int gDp(int x)
{
	for (int i = 2; i <= x; i++) {
		dp[i] = dp[i - 1] + 1;

		if (!(i % 3)) {
			dp[i] = min(dp[i], dp[i / 3] + 1);
		}

		if (!(i % 2)) {
			dp[i] = min(dp[i], dp[i / 2] + 1);
		}
	}
	return dp[x];
}


int main() {

	int n;
	cin >> n;
	
	memset(dp, -1, sizeof(dp));

	dp[0] = dp[1] = 0;

	cout << gDp(n) << endl;

	return 0;
}