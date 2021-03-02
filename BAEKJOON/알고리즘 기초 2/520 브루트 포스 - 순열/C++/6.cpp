#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {
	int n, haf, ml = -1, mr = -1;
	int res = 0;
	cin >> n;
	int lef = 1, rat = n;
	haf = n / 2;
	vector<int> arr(n+1);
	for (int i = lef; i <= rat; i++) {
		cin >> arr[i];
		if (i <= haf) {
			ml = max(arr[i], ml);
		}
		else {
			mr = max(arr[i], mr);
		}
	}

	

	while (lef != rat) {
		if (ml > mr) {
			res += ml;
			lef = haf + 1;
			haf = (haf + n) / 2;
			mr = ml = -1;
			for (int i = lef; i <= rat; i++) {
				if (i <= haf) {
					ml = max(arr[i], ml);
				}
				else {
					mr = max(arr[i], mr);
				}
			}
		}
		else {
			res += mr;
			rat = haf;
			haf = (haf + lef) / 2;
			mr = ml = -1;
			for (int i = lef; i <= rat; i++) {
				if (i <= haf) {
					ml = max(arr[i], ml);
				}
				else {
					mr = max(arr[i], mr);
				}
			}
		}
	}
	cout << res << endl;
	

	return 0;
}