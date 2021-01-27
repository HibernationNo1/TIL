#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
	int n, i, res;
	cin >> n;
	vector<int> arr(n);
	vector<int> dp(n);

	for (i = 0; i < n; i++) {
		cin >> arr[i];
		if (i == 0) {
			res = dp[0] = arr[0];
		}
		else {
			dp[i] = max(dp[i - 1] + arr[i], arr[i]);
			res = max(dp[i], res);
		}	
	}
	cout << res << endl;

	return 0;
}