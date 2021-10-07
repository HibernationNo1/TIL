#include<iostream>
#include<algorithm>

using namespace std;

int dp[10001];
int buff[10001];

 int gDp(int x)
{
	 int i;
	 dp[0] = 0;
	 dp[1] = buff[1];
	 dp[2] = dp[1] + buff[2];

	 for (i = 3; i <= x; i++) {
		 dp[i] = max({ dp[i - 1], dp[i - 2] + buff[i], dp[i - 3] + buff[i - 1] + buff[i] });
	 }
	
	 return dp[x];
}

int main(void)
{
	int n,i;
	cin >> n;
	
	for (i = 1; i <= n; i++) {
		cin >> buff[i];
	}
	cout << gDp(n);

	return 0;
}