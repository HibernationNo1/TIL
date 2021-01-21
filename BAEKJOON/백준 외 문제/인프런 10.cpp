#include <iostream>
#include <algorithm>
using namespace std;

int digit_sum(int x)  //123  //  12 / 1
{
    int resurt = 0;
   
    if(x/10>=1)
    resurt += digit_sum(x / 10);  // 123

    return resurt += x % 10;  //1 + 2 + 3
}

int main(void)
{
    int n, num, i, sum, res = 0;
    cin >> n;
    int cnt = numeric_limits<int>::min();
    for (i = 1; i <= n; i++) {
        cin >> num;
        sum = digit_sum(num);
        if (cnt < sum) {
            cnt = max(sum, cnt);
            res = num;
        }
        else if (cnt == sum) {
            res = max(res, num);
        }
    }
    
    cout << res;


    return 0;
}