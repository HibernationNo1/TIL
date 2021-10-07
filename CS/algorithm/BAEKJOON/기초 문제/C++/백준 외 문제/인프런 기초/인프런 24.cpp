#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main(void)
{
	int n, now, pre;
	cin >> n;
	vector<int> arr(n);
	cin >> pre;
	for (int i = 1; i < n; i++) {
		cin >> now;
		arr[abs(pre - now)] = abs(pre - now);
		pre = now;
	}
	sort(arr.begin(), arr.end(), less<int>());

	for (int i = 0; i < n; i++) {
		if (arr[i] != i) {
			cout << "NO" << endl;
			pre = -10000;
			break;
		}
	}
	if(pre !=-10000)
	cout << "YES" << endl;

	return 0;
}