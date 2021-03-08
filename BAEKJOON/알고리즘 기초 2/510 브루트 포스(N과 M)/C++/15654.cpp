#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
#define endl '\n'

int n, m;
int res[8];
bool stc[8];

void foo(int k, vector<int> arr) {
	if (k == m) {
		for (int i = 0; i < m; i++) {
			if (i == m - 1) {
				cout << res[i]<<" ";
				break;
			}
			cout << res[i] << " ";
		}
		cout << endl;
		return;
	}

	for (int i = 0; i < n; i++) {
		if (stc[i]) {
			continue;
		}
		res[k] = arr[i];
		stc[i] = true;
		foo(k + 1, arr);
		stc[i] = false;
	}
	return;
}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end(), less<int>());
	foo(0, arr);
}