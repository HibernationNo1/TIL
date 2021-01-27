#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
	int n, m = 0, count2 = 1, count1 = 1;
	cin >> n;
	vector<int> arr(n);
	vector<int> dp(n);
	vector<int> rdp(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		dp[i] = 1;
		for (int j = 0; j < i; j++) { 
			if (arr[j] < arr[i]) {  
				dp[i] = max(dp[i], dp[j] + 1);
			}
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		rdp[i] = 1;
		for (int j = n - 1; j > i; j--) {
			if (arr[j] < arr[i]) {
				rdp[i] = max(rdp[i], rdp[j] + 1);
			}
		}
	}

	for (int i = 0; i < n; i++) {
		m = max(m, dp[i] + rdp[i] - 1);
	}

	cout << m << endl;

	return 0;
}