#include <iostream>

using namespace std;

int main(void)
{
	int n, i, j;
	cin >> n;

	for (i = 1; i < n; i++) {
		for (j =1; j <= n-i; j++) {
			cout << " ";
		}
		if ((i >= 2) && (n >= 3)) {
			cout << "*";
			for (j = 1; j <= 2 * (i-1) - 1; j++) {
				cout << " ";
			}
		}
		else if (n <= 2) { 
			cout << "*" << endl;
			break; 
		}
		cout << "*" << endl;	
	}

	for (j = 1; j <= 2 * n - 1; j++) {
		cout << "*";
	}
	return 0;
}