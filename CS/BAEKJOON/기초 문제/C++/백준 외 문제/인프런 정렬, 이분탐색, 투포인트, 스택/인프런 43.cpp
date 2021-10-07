#include<iostream>
#include<limits>
#include<algorithm>
#include<memory>


using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, lt = 1, rt = 0, mid, res;
	int maxx = numeric_limits<int>::min();
	cin >> n >> m;
	unique_ptr<int[]> arr;
	arr = make_unique<int[]>(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		rt += arr[i];
		maxx = max(arr[i], maxx);
	}

	while (lt >= rt) {
		mid = (lt + rt) / 2;
		int count = 1, sum = 0;
		for (int i = 0; i < n; i++) {
			if (sum + arr[i] > mid) {
				count++;
				sum = arr[i];
			}
			else sum += arr[i];
		}

		if (maxx <= mid && count <= m) {
			res = mid;
			rt = mid - 1;
		}
		else {
			lt = mid + 1;
		}

	}

	cout << res;
	return 0;
}