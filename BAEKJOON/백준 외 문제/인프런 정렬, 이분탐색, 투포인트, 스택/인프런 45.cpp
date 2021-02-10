#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, k, count, tmp = 0;
	cin >> n >> k;
	count = n;
	
	deque<int> arr(n);
	for (int i = 0; i < n; i++) {
		arr[i] = i+1;
	}

	while (count > 1) {
		tmp += (k - 1);
		tmp = tmp % arr.size();
		arr.erase(arr.begin() + tmp);	
		count--;
	}

	cout << arr.front();

	return 0;
}