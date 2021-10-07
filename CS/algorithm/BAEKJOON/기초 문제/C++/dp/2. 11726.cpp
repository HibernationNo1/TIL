#include <iostream>
#include <cstring>

using namespace std;

int dp[1001];

int main(void)
{
    int n;
    cin >> n; 

    memset(dp, -1, sizeof(dp));
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; i++)
    {
        dp[i] = (dp[i - 2] + dp[i - 1])% 10007;
    }

    cout << dp[n] << endl;

    
    return 0;
}