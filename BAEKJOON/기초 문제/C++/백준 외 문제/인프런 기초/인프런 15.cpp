#include<iostream>

using namespace std;

int main(void)
{
	int n, i, j, flag, count = 0;
	cin >> n;
	if (n == 2) {
		cout << 1 << endl;
		return 0;
	}

	for (i = 2; i <= n; i++) {
		flag = 1;
		for(j = 2; j*j<=i; j++) {
			if (i % j == 0) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) { count++; }
	}

	cout << count << endl;

	return 0;
}