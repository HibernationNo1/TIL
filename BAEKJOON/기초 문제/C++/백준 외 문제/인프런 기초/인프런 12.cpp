#include <iostream>
#include <cmath>
using namespace std;

 
int main(void)
{
    int n, count = 0, c = 1, d = 9;
    cin >> n;

    while (pow(10,c)-1 < n) {  //256
        count = count + (c * d);  // 9 + 18
        c++;
        d = d * 10;
    }
    count = count + (n - pow(10, c - 1) + 1)*(c);  //189 + (256 - 99)3
    

    cout << count << endl;

    return 0;
}