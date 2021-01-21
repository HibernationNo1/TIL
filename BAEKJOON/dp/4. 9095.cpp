#include <iostream>
#include <cstring>

using namespace std;

int dp[11];
int res[10];


int main(void)
{
    int t, i, j;
    cin >> t; 

    memset(dp, -1, sizeof(dp));
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for (i = 1; i <= t; i++) {
        int n;
        cin >> n;
        
        for (j = 4; j <= n; j++)
        {
                dp[j] = dp[j - 1] + dp[j - 2] + dp[j - 3] ;
  
        }

        cout << dp[n] <<endl;;
    } 


    return 0;
}