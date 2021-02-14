#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

int divide(int x, int y) {
	
	if (!(x % y)) return y;
	else return divide(y, x % y);
}

int main(void) {
	
	int x;
	cin >> x;

	for (int i = 0; i < x; i++) {
		int y;
		cin >> y;
		long long sum = 0;
		vector<int> arr(y);
		for (int j = 0; j < y; j++) {
			cin >> arr[j];
		}
		for (int j = 0; j < y; j++) {
			for (int k = j+1; k < y; k++) {
				sum += divide(arr[j], arr[k]);
			}
		}
		cout << sum <<endl;
	}

	return 0;
}