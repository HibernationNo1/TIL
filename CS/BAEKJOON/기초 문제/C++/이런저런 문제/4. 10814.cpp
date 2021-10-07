#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>

using namespace std;

#define endl '\n'

bool cmd(const pair<int, string>& x, const pair<int, string>& y)
{
	return x.first < y.first;
}

int main(void)
{
	int n;
	cin >> n;

	vector< pair<int, string>> arr(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i].first >> arr[i].second;
	}

	stable_sort(arr.begin(), arr.end(), cmd);


	for (int i = 0; i < n; i++) {
		cout << arr[i].first << " " << arr[i].second << endl;
	}

	return 0;
}