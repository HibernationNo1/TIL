#include <iostream>

#define endl "\n"
using namespace std;

long long dp[101][11];  // [자릿수][마지막 자릿수의 숫자]
// 1의자리부터 n의 자리까지 올라가며 경우의 수를 구한다고 생각하자
int gvalue = 1000000000;

int gdp(int n)
{
    long long resurt = 0;
    for (int i = 1; i <= 9; i++) {
        dp[1][i] = 1;
    }
    dp[1][0] = 0;

    for (int i = 2; i <= n; i++) {
        for (int j = 0; j <= 9; j++) {
            if (j == 0) {
                dp[i][j] = dp[i - 1][1] % gvalue;  // 마지막 자리가 1일때의 경우만 다음에 0이 올 수 있음
            }
            else if (j == 9) {
                dp[i][j] = dp[i - 1][8] % gvalue;  // 마지막 자리가 8일때의 경우만 다음에 9이 올 수 있음
            }
            else
            {
                dp[i][j] = dp[i - 1][j + 1] + dp[i - 1][j - 1] % gvalue;
            }
            // i자릿수의 마지막 j숫자의 경우의 수는 
            // i-1자릿수에서의 마지막 숫자가 j-1와 j+1일때의 경우의 수를 합한 것
        }
    }

    for (int i = 0; i <= 9; i++) {
        resurt += (dp[n][i]) ;
    }
    resurt = resurt % gvalue;  
    // 0부터 9까지의 값을 더했으니 gvalue보다 큰 값이 나올 수 있다. 한번 더 나눠주자
    return resurt;
}

int main(void)
{
    int n;
    cin >> n; 

    cout << gdp(n) << endl;

    return 0;
}