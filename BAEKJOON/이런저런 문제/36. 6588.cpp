#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'
bool arr[1000001];


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int c;

	for (int i = 2; i <= 1000000; i++) {
		arr[i] = true;
	}

	for (int i = 2; i * i <= 1000000; i++) {
		if (arr[i]) {
			for (int j = i * i; j <= 1000000; j += i) {
				arr[j] = false;
			}
		}
	}

	vector<int> num;
	for (int i = 3; i <= 1000000; i++) {
		if (arr[i]) {
			num.push_back(i);
		}
	}

	while (1) {
		cin >> c;
		if (c == 0) break;

		for (int i = 0; i<c; i++) {
			if (arr[c - num[i]] == true) {
				cout << c << " = " << num[i] << " + " << c - num[i] << endl;
				break;
			}
		}		
	}

	return 0;
}