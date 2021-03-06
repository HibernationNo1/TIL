#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void)
{
	int n;
	cin >> n;

	vector<vector<int>> arr(n, vector<int>(2));  // 2중 백터 배열

	for (int i = 0; i < n; i++) {
		cin >> arr[i][1];
		cin >> arr[i][0];
	}

	sort(arr.begin(), arr.end());

	for (int i = 0; i < n; i++) {
		cout << arr[i][1] << " " << arr[i][0] << endl;
	}

	return 0;
}