#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
	int n, i;
	cin >> n;
	vector<int> arr(n);
	vector<int> dp(n);

	for (i = 0; i < n; i++) {
		cin >> arr[i];
	}
	

	dp[0] = arr[0];
	dp[1] = arr[0] + arr[1];
	for (i = 2; i < n; i++) { // 0에서 시작
		dp[i] = max(dp[i - 2] + arr[i], dp[i - 3] + arr[i-1] + arr[i]);
	}

	cout << dp[n-1] << endl;

	return 0;
}