#include<iostream>
#include<algorithm>
#include<deque>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, i;
	cin >> n;

	deque<int> arr(n), num(n);

	for (i = 0; i < n; i++) {
		cin >> num[i];
		arr[i] = i + 1;
	}

	for (i = n - 1; i >= 0; i--) {
		arr.pop_back();
		arr.insert(arr.begin()+ num[i], i + 1);
	}

	for (i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}