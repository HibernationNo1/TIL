#include<iostream>
#include<algorithm>
#include<memory>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, key, le, ra, mid;
	unique_ptr<int[]> arr;
	cin >> n >> key;
	arr = make_unique<int[]>(n);
	le = 0;
	ra = n - 1;
	mid = (le + ra) / 2;

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	sort(arr.get(), arr.get() + n, less<int>());
	
	while (le <= ra) {
		
		if (arr[mid] == key) {
			cout << mid + 1 << endl;
			break;
		}
		else if (arr[mid] < key) le = mid + 1;
		else if (arr[mid] > key) ra = mid - 1;

		mid = (le + ra) / 2;
	}

	return 0;
}