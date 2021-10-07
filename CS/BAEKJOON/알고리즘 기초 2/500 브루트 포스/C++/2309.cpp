#include<iostream>
#include<algorithm>

using namespace std;

#define endl '\n'


int main(void)
{
	int arr[9];
	int sum = 0;
	int res;
	for (int i = 0; i < 9; i++) {
		cin >> arr[i];
		sum += arr[i];
	}
	sort(arr, arr + 9, less<int>());

	for (int i = 0; i < 8; i++) {
		for (int j = i + 1; j < 9; j++) {
			res = sum - arr[i] - arr[j];
			if (res == 100) {
				
				for (int x = 0; x < 9; x++) {
					if (x == i || x == j) {
						continue;
					}
					cout << arr[x] << endl;
				}
				return 0;
				
			}
		}
	}

	return 0;
}