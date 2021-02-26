#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define endl '\n'

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	bool tmp;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	tmp = next_permutation(arr.begin(), arr.end());

	if (!tmp) {
		cout << "-1" << endl;
	}
	else {
		for (int i = 0; i < n; i++) {
			if (i == n - 1) {
				cout << arr[i];
				break;
			}
			cout << arr[i] << " ";
		}
	}

	return 0;
}