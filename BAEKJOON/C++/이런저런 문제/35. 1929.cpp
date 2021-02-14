#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int m, n;
	cin >> m >> n;

	vector<bool> arr(n+1);
	for (int i = 2; i <= n; i++) {
		arr[i] = true;
	}

	for (int i = 2; i * i <= n; i++) {
		if (arr[i]) {
			for (int j = i * i; j <= n; j += i) {
				arr[j] = false;
			}
		}
	}

	for (int i = m; i <= n; i++) {
		if (arr[i]) cout << i << endl;
	}
	


	return 0;
}