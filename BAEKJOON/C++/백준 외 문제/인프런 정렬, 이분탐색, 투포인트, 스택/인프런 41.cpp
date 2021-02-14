#include<iostream>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n,sum, count = 0;
	cin >> n;

	for (int i = 2; i * (i + 1) / 2 <= n; i++) {
		sum = i * (i + 1) / 2;
		if (!((n - sum) % i)) {
			for (int j = 1; j <= i; j++) {
				cout << j + ((n - sum) / i);
				if (j != i) cout << " + ";
				else cout << " = " << n;
			}
			count++;
			cout << endl;
		}
	}
	cout << count;

	return 0;
}