#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {
	
	int n, m, e, tmp, tmpi, res =10000;
	cin >> n >> m >> e;
	vector<int> arr(n);
	vector<bool> num(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		num[i] = false;
		res = min(res, abs(arr[i] - e));
		if (res == abs(arr[i] - e)) {
			tmp = arr[i];
			tmpi = i;
		}
	}
	num[tmpi] = true;

	for (int i = 0; i < n; i++) {
		if (num[i]) {
			continue;
		}
		if (abs(tmp - arr[i]) <= abs(e - arr[i])) {
			res += abs(tmp - arr[i]);
			num[i] = true;
		}

	}
	
	int pl = 0, pr = n-1;


	return 0;
}