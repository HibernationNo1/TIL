#include<iostream>

using namespace std;
int gValue = 10007;
int dp[1001];
int sdp[1001][11];


int gDp(int x)
{
	int i, j;
	if (x == 1) {
		return dp[1] = 10;;
	}

	for (i = 0; i <= 9; i++) {
		sdp[2][i] = i + 1;
	}
	for (int y = 3; y <= x; y++) {
		for (i = 0; i <= 9; i++) {
			for (j = 0; j <= i; j++) {
				sdp[y][i] = sdp[y][i] + sdp[y - 1][j] % gValue;
			}

		}
	}

	for (i = 0; i <= 9; i++) {
		dp[x] = dp[x] + sdp[x][i] % gValue;
	}
	
	return dp[x] % gValue;
}

int main(void)
{
	int n;
	cin >> n;

	cout << gDp(n) << endl;

	return 0;
}