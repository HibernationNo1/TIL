#include<iostream>
#include<algorithm>
#include<memory>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	
	unique_ptr<int[]> arr;
	arr = make_unique<int[]>(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	sort(arr.get(), arr.get() + n, less<int>());

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}