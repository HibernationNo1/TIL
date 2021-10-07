#include<iostream>
#include<algorithm>

using namespace std;

int dp[1001];
int arr[1001];

int main(void)
{
	int n,i, j, sum = 0;
	cin >> n;

	for (i = 0; i <n; i++) {
		cin >> arr[i];
		dp[i] = 1;
		for (j = 0; j < i; j++) {
			if (arr[i] > arr[j]) {
				dp[i] = max(dp[i], dp[j] + 1);  
				// arr[i]가 arr[j]보다 클 때마다 dp비교 후 큰 값 할당
			} // arr[i]가 arr[j]보다 작을 때는 신경 안써도 
		}
		sum = max(sum, dp[i]);  // 여기서 역대 가장 큰 dp가 dp[i]임으로 상관 없음
	}
	
	cout << sum << endl;

	return 0;
}