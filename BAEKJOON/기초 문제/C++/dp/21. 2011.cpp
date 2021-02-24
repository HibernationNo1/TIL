#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int gValue = 1000000;

int main(void)
{
	string str;
	cin >> str;
	
	if (str.size() == 1 && (str[0] == '0'))
	{
		cout << 0 << endl;
		return 0;
	}
	
	vector<int> arr(str.size() + 1);
	vector<int> dp(str.size() + 1);

	for (int i = 1; i <= int(str.size()); i++) {
		arr[i] = str[i-1] - 48;
		dp[i] = 0;
	}

	dp[0] = 1;
	int a = 0;

	for (int i = 1; i<=int(str.size()); i++) {
		if (i == 1) {
			if (1 <= arr[i] && arr[i] <= 9) {
				dp[i] = (dp[i] + dp[i - 1]) % gValue;
			}
			continue;
		}
		
		if (1 <= arr[i] && arr[i] <= 9) {
			dp[i] = (dp[i] + dp[i - 1]) % gValue;
		}

		a = (arr[i - 1] * 10 + arr[i]);

		if (10<=a &&a <= 26) {
			dp[i] = (dp[i] + dp[i-2]) % gValue;
		}
		
		if (30 <= a && a % 10 == 0) {
			a = -1000;
			break;
		}
		else if (a == 0) {
			a = -1000;
			break;
		}
		
	}

	if (a == -1000) {
		cout << 0 << endl;
	}
	else {
		cout << dp[str.size()];
	}

	return 0;
}