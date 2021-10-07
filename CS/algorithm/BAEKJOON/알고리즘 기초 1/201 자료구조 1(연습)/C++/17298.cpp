#include<iostream>
#include<vector>
#include<stack>

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
	vector<int> res(n);
	stack<int> stc;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		res[i] = -1;
		if (i == 0) {
			stc.push(i);
			continue;
		}
		
		
		while (stc.size() > 0 && arr[stc.top()] < arr[i]) {
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