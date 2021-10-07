#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

#define endl '\n'


int main(void) {
	
	string str;
	int b, sum = 0;
	cin >> str >> b;
	vector<int> num(str.size());

	for (int i = 0; i<int(str.size()); i++) {
		if (str[i] <= 57) {
			num[i] = str[i] - 48;
		}
		else {
			num[i] = str[i] - 55;
		}

		sum = sum + (num[i] * int(pow(b, str.size() - 1 - i)));
	}
	cout << sum << endl;

	return 0;
}