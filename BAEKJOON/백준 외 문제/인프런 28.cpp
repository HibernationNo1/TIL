#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main(void)
{
	int n, i, j, tmp;
	cin >> n;
	vector<int> arr(n);

	for (i = 2; i <= n; i++) {
		tmp = i;
		j = 2;
		while (tmp != 1) {
			if (!(tmp % j)) {
				tmp = tmp / j;
				arr[i]++;
			}
			else j++;
		}

	}

	
	cout << arr[5] << endl;
	
	
	return 0;
}