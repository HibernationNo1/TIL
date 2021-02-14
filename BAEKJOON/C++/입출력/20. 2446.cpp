#include <iostream>

using namespace std;

int main(void)
{
	int n, i, j;
	cin >> n;

	for (i = 1; i <= n; i++) {  
		for (j = 1; j <= i-1; j++) {
			cout << " ";
		}
		for (j = 1; j <= 2 * (n - i) + 1; j++) {   
			cout << "*";
		}
		cout << endl;
	}
	for (i = 2; i <= n; i++) {
		for (j = n - (i); j >= 1; j--) {
			cout << " ";
		}
		for (j = 1; j <= 2*i-1 ; j++) {
			cout << "*";
		}
		cout << endl;
	}

	return 0;
}