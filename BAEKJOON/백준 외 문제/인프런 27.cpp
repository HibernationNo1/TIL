#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;


int main(void)
{
	int n, i, j, tmp, count, ntmp;
	cin >> n; 
	vector<int> arr(n+1);
	for (i = 2; i <= n; i++) {
		tmp = i;
		j = 2;
		while (tmp != 1) {
			if (!(tmp % j)) {
				tmp = tmp / j;
				arr[j]++;
			}
			else j++;
		}
	}

	
	cout << n << "!" << " = ";
	for (i = 2; i <= n; i++) {
		if (arr[i] != 0) {
			cout << arr[i] << endl;
		}
	}
	
	
	return 0;
}