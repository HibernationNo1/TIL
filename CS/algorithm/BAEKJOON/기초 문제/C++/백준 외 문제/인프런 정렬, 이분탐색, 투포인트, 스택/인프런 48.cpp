#include<iostream>
#include<vector>
#include<limits>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int res, clos;
	double sum, aver;
	vector<vector<int>> arr(9, vector<int>(9));
	for (int i = 0; i < 9; i++) {
		sum = 0;
		clos = numeric_limits<int>::max();
		res = numeric_limits<int>::min();
		for (int j = 0; j < 9; j++) {
			cin >> arr[i][j];
			sum += arr[i][j];
		}
		aver = round(double(sum / 9));

		for (int j = 0; j < 9; j++) {
			if (int(abs(aver - arr[i][j])) == int(abs(aver - res))) {
				res = max(res, arr[i][j]);
				continue;
			}

			if (clos >= int((abs(aver - arr[i][j])))) {
				clos = int(abs(aver - arr[i][j]));
				res = arr[i][j];
			}		
		}
		
		cout << aver <<" " << res << endl;
	}


	return 0;
}