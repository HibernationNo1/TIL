#include <iostream>
using namespace std;

int main(void)
{
    int n, i, tmp, count = 0;
    cin >> n;
    for (i = 1; i <= n; i++) {
        tmp = i;
        while (1) { 
            if (!(tmp / 10)) {
                count++;  
                break;
            }
            else {
                tmp = (tmp / 10);  
                count++;
            }
        }
    }
    cout << count << endl;

    return 0;
}