#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main(void)
{
	int n, i, j;
	cin >> n;
	vector<int> arr(n + 1);
	vector<int> brr(n + 1);

	for (i = 0; i < n; i++) {
		cin >> arr[i];
		brr[i] = i+1;  //1부터 n까지
		for (j = 0; j < i; j++) {
			if (arr[j] < arr[i]) {
				brr[i]--;
			}
		}
		cout << brr[i] << "\n";
	}
	

	return 0;
}