#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>

using namespace std;

#define endl '\n'

void divide(string &result, int x, int y) {
	int s;
	while (x != 0) {
		s = x % y;
		if (!(x % y)) {
			result += "0 ";
			x = x / y;
		}
		else {
			string tmp = to_string(x % y);
			reverse(tmp.begin(), tmp.end());
			result += tmp;
			result += ' ';
			x = (x - (x % y)) / y;
		}
	}
	
	reverse(result.begin(), result.end());
	result.erase(result.begin());
}


int main(void) {

	int A, B, m, sum = 0;
	cin >> A >> B >> m;

	vector<int> arr(m);
	
	string result = "";

	for (int i = 0; i < m; i++) {
		cin >> arr[i];
		sum = sum + arr[i] * int(pow(A, m - i - 1));
	}

	
	divide(result, sum, B);

	cout << result << endl;
	


	return 0;
}