#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define endl '\n'

int main(void)
{

	int n;
	cin >> n;
	
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >>  arr[i];
	}
	sort(arr.begin(), arr.end(), less<int>());
	
	for (int i = 0; i < n; i++) {
		cout << arr[i] << endl;
	}
	 

	return 0;
}