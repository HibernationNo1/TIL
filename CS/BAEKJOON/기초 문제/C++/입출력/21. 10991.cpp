#include <iostream>

using namespace std;

int main(void)
{
	int n, i, j;
	cin >> n;

	for (i = 1; i <= n; i++) {
		for (j = n - i; j >= 1; j--) {
			cout << " ";
		}

		for (j = 1; j < 2 * i; j++) {
			if (j % 2 == 0) { cout << " "; }
			else { cout << "*"; }
		}
		cout << endl;
	}

	return 0;
}