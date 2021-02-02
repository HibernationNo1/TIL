#include<iostream>
#include<vector>
#include<algorithm>
#include<limits>

using namespace std;

#define endl '\n'



int main(void)
{
	int n, temp =1,  count = 1;
	long long num;
	cin >> n;

	vector<long long> arr(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	sort(arr.begin(), arr.end());

	num = arr[0];

	for (int i = 1; i < n; i++) {
		if (arr[i] == arr[i - 1]) {
			count++;
		}
		else {
			count = 1;
		}


		if (count > temp) {
			num = arr[i];
			temp = count;
		}
	}

	cout << num;

	return 0;
}