#include<iostream>
#include<algorithm>
#include<memory>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, tmp, j;
	cin >> n;
	
	unique_ptr<int[]> arr;
	arr = make_unique<int[]>(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	for (int i = 1; i < n; i++) {
		tmp = arr[i];
		for (j = i - 1; j >= 0; j--) {
			if (arr[j] > tmp) {
				arr[j + 1] = arr[j];	
			}
			else break;
		}
		arr[j+1] = tmp;
	}

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	return 0;
}