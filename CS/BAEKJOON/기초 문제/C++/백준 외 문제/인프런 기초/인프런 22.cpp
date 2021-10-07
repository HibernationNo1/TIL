#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>

using namespace std;

int main(void)
{
	int n, k, sum = 0;
	int m = numeric_limits<int>::min();
	cin >> n >> k;
	vector<int> arr(n);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		sum += arr[i];
		if (i >=k) {
			sum -= arr[i - k];
		}
		m = max(sum, m);
		
	}
	cout << m<< endl;

	return 0;
}