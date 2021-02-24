#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;

int dp[101];

int main(void)
{
	int n, count = 0, max = 0;
	cin >> n;
	for (int i = 0; i <n; i++) {
		cin >> dp[i];
	}
	
	for (int i = n-1; i >=1; i--) {
		if (dp[i] < dp[i - 1]) {
			
			count++;
		}
		else { dp[i - 1] = dp[i]; }
	}
	
	cout << count << endl;
	
	return 0;
}