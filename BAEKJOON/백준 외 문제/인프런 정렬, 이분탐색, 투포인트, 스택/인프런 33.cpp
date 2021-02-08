#include<iostream>
#include<algorithm>
#include<memory>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, count = 1;
	cin >> n;
	
	unique_ptr<int[]> arr;
	arr = make_unique<int[]>(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	sort(arr.get(), arr.get() + n, greater<int>());

	for (int i = 1; i < n; i++) {
		if (arr[i] != arr[i - 1]) {
			count++;
		}
		

		if (count == 3) {
			cout << arr[i] << endl;
			break;
		}			
	}

	return 0;
}