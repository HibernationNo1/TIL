#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int dp[1000001];

int gDp(int x)
{
	
	

	for (int i = 2; i <= x; i++) {

		dp[i] = dp[i - 1] + 1;  // i 에서 1을 빼는 연산 실행시
		
		if (!(i % 3)) {
			dp[i] = min(dp[i], dp[i / 3] + 1);  
			// x를 3으로 나눈, 이전의 경우의 수와 x에서 -1 했을때의 경우의 수를 비교, 더 작은 값 반환
		}
		if (!(i % 2)) {
			dp[i] = min(dp[i], dp[i / 2] + 1);
		}
	}  // 2부터 x까지 모든 경우의 수 중 최종적으로 가장 작은 경우의 수가 살아남는다. 
	return dp[x];
}

int main(void)
{
	int n;
	cin >> n;
	memset(dp, -1, sizeof(dp));

	dp[0] = dp[1] = 0;

	cout << gDp(n) << endl;

	return 0;
}