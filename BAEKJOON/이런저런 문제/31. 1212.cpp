#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'


int main(void) {

	string oct;
	int t = 0;
	cin >> oct;
	vector<int> arr(oct.size() * 3);

	for (int i = 0; i<int(oct.size()); i++) {
		oct[i] -= 48;

		if (oct[i] >= 4) {
			arr[t++] = 1;
			oct[i] -= 4;
		}
		else arr[t++] = 0;

		if (oct[i] >= 2) {
			arr[t++] = 1;
			oct[i] -= 2;
		}
		else arr[t++] = 0;

		if (oct[i] == 1) {
			arr[t++] = 1;
		}
		else arr[t++] = 0;

	}

	if (arr[0] == 0) {
		arr.erase(arr.begin());
		if (arr[0] == 0) {
			arr.erase(arr.begin());
		}
	}

	for (int x : arr) {
		cout << x;
	}
	cout << endl;

	return 0;
}