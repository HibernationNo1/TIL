#include<iostream>
#include<vector>

using namespace std;


int main(void)
{
	int n, i, j;
	cin >> n;
	vector<int> arr(n + 1);
	vector<int> brr(n + 1);

	for (i = 0; i < n; i++) {
		cin >> arr[i];
		brr[i] = 1;
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			if (arr[i] < arr[j]) {
				brr[i]++;
			}
		}
		cout << brr[i] << endl;
	}

	

	return 0;
}