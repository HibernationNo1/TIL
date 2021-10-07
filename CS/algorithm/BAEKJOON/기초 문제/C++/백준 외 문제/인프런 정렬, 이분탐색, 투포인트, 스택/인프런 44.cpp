#include<iostream>
#include<algorithm>
#include<memory>


using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n, m, res, pos, count;
	cin >> n >> m;
	unique_ptr<int[]> arr;
	arr = make_unique<int[]>(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr.get(), arr.get() + n, less<int>());

	int lt = arr[0], rt = arr[n - 1], mid = (lt + rt) / 2;

	while (lt <= rt) {
		pos = arr[0];
		count = 1;
		for (int i = 0; i < n; i++) {
			if (arr[i] - pos >= mid) {
				count++;
				pos = arr[i];
			}
		}
		if (count >= m) {
			lt = mid + 1;
			res = mid;
		}
		else {
			rt = mid - 1;
		}	
		mid = (lt + rt) / 2;
	}
	
	cout << res << endl;
	return 0;
}