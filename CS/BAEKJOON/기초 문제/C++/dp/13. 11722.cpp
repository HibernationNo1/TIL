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
		dp[i] = 1;
		for (int j = 0; j < i; j++) { 
			if (arr[j] > arr[i]) {  
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
		m = max(dp[i], m);
	}
	cout << m << endl;

	return 0;
}