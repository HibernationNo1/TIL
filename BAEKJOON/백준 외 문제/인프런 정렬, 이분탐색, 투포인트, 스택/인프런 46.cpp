#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, k, i, sum = 0;
	cin >> n;
	deque<int> arr(n);
	for (i = 0; i < n; i++) {
		cin >> arr[i];
		sum += arr[i];
	}

	i = -1;
	cin >> k;
	if (sum <= k) {
		cout << -1;
		return 0;
	}
	
	while (k) {
		i++;
		if (i == n) i = 0;

		if (arr[i] > 0) {
			//cout << i << " ";
			k -= 1;
			arr[i]--;
		}
	}

	while (1) {
		
		i++;
		if (i == n) i = 0;

		if (arr[i] == 0) continue;
		else break;
		
	}
	cout << i+1;
	

	return 0;
}