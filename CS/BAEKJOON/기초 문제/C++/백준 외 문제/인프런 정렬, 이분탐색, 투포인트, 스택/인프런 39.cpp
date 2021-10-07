#include<iostream>
#include<algorithm>
#include<memory>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n1, n2, i;
	unique_ptr<int[]> arr1, arr2;
	cin >> n1;
	arr1 = make_unique<int[]>(n1);
	for (i = 0; i < n1; i++) {
		cin >> arr1[i];
	}

	cin >> n2;
	arr2 = make_unique<int[]>(n2+n1);
	for (i = 0; i < n2+n1; i++) {
		if (i >= n2) {
			arr2[i] = arr1[i - n2];
		}
		else {
			cin >> arr2[i];
		}
	}

	sort(arr2.get(), arr2.get() + n2 + n1, less<int>());
	for (i = 0; i < n2 + n1; i++) {
		cout << arr2[i] << " ";
	}

	

	return 0;
}