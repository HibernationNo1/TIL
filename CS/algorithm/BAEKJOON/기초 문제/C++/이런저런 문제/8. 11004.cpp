#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, k;
	cin >> n>>k;

	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	sort(arr.begin(), arr.end());

	cout << arr[k-1];

	return 0;
}