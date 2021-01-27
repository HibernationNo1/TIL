#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
	int n, m = 0;
	cin >> n;
	vector<int> arr(n);
	vector<int> dp(n);

	

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		dp[i] = arr[i];
		for (int j = 0; j < i; j++) {  // 0부터 i-1까지
			if (arr[j] < arr[i]) {  //증가부분수열일때
				dp[i] = max(dp[i], dp[j] + arr[i]); // 지금 수열의 합 vs 이전 수열의 합 + 지금 배열의 값
			}
		}
		m = max(dp[i], m);
	}
	cout << m << endl;

	return 0;
}