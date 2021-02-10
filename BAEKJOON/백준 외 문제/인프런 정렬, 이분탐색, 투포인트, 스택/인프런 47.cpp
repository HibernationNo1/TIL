#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, count = 0;
	cin >> n;
	vector<vector<int>> arr(n+2, vector<int>(n+2));
	for (int i = 0; i < n+2; i++) {
		if (i == 0 || i == n +1) {
			for (int j = 0; j < n+2; j++) {
				arr[i][j] = 0;
			}
			continue;
		}
		arr[i][0] = 0;
		for (int j = 1; j < n+1; j++) {
			cin >> arr[i][j];
		}
		arr[i][n+1] = 0;
	}

	for (int i = 1; i < n + 1; i++) {
		for (int j = 1; j < n + 1; j++) {
			if (arr[i - 1][j] < arr[i][j] && arr[i + 1][j] < arr[i][j] && arr[i][j - 1] < arr[i][j] && arr[i][j + 1] < arr[i][j]) {
				count++;
				j++;
			}
			else continue;
		}
	}
	
	cout << count << endl;


	return 0;
}