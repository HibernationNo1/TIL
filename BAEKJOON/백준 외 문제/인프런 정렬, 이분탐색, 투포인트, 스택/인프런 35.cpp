#include<iostream>
#include<algorithm>
#include<memory>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, tmp, count = 0;
	cin >> n;
	
	unique_ptr<int[]> arr;
	arr = make_unique<int[]>(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	for (int i = 0; i < n-1; i++) {
		if (arr[i] > 0 && arr[i + 1] < 0) {
			for (int j = i; j >= count; j--) {
				tmp = arr[j + 1];
				arr[j + 1] = arr[j];
				arr[j] = tmp;
			}
			count++;
		}
		else if (arr[i] < 0) count++;
	}

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}