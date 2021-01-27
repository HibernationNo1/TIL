#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(void)
{
	int n, i,j;
	cin >> n;
	vector<int> dp(n+1);
	//dp[0] = 0
	for (i = 1; i <= n; i++) {
		dp[i] = i;  
		//숫자가 i일 때의 dp(항의갯수)는 1이 i 개 만큼 있는 것(항의 갯수의 최대값)
	}
	
	for (i = 4; i <= n; i++) {  //dp[1~3]은 1~3과 같음
		for (j = 2; j * j <= i; j++) {  //dp[i - 1] + 1 은 시간만 버리는 꼴
			dp[i] = min(dp[i], dp[i - j * j] + 1);  
		}
	}

	cout << dp[n] << endl;


	return 0;
}