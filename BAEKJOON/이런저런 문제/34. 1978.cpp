#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

int main(void) {



	int n, count = 0;
	cin >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		int c = 0;
		cin >> arr[i];

		if (arr[i] == 1) { continue; }
		
		int j = arr[i];
		while (j) {
			
			if (!(arr[i] % j)) {
				c++;
			}
			if (c > 2) break;
			j--;
		}
		if (c == 2) count++;
		
	}

	cout << count << endl;
	return 0;
}