#include<iostream>
#include<vector>
#include<limits>
#include<string>
#include<algorithm>
using namespace std;

#define endl '\n'

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	
	int num, n, res;
	cin >> num >> n;
	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	int m = numeric_limits<int>::max();
	int len;


	
	for (int i = 0; i < 1000001; i++) {
		bool check = false;
		string str = to_string(i);
		
		for (int j = 0; j<int(str.size()); j++) {
			for (int x = 0; x<int(arr.size()); x++) {
				if (str[j] - 48 == arr[x]) {
					check = true;
					break;
				}
			}
		}

		if (check) {
			continue;
		}
		
		if (m > abs(num - i)) {
			m = abs(num - i);
			len = str.size();
		}

	}
	res = min(m + len, abs(num - 100));
	cout << res << endl;


	return 0;
}