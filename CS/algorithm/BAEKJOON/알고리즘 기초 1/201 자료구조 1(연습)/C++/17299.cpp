#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;
	vector<int> arr(n);
	vector<int> cnar(n);
	stack<int> stc;
	vector<int> res(n);
	
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		res[i] = -1;
	}

	int m = *max_element(arr.begin(), arr.end());
	vector<int> cnt(m);
	for (int i = 0; i < n; i++) {
		cnt[arr[i]-1]++;
	}

	for (int i = 0; i < n; i++) {
		if (i == 0) {
			cnar[i] = cnt[arr[i] - 1];
			stc.push(i);
			continue;
		}
		cnar[i] = cnt[arr[i] - 1];

		while (stc.size() > 0 && cnar[stc.top()] < cnar[i]) {
			res[stc.top()] = arr[i];
			stc.pop();
		}

		stc.push(i);
	}

	for (int i = 0; i < n; i++) {
		cout << res[i] << " ";
	}



	return 0;

}