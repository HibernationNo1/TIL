#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'


int main(void) {

	int num;
	cin >> num;
	
	if (num == 0) {
		cout << 0 << endl;
		return 0;
	}

	string str = "";
	while (num != 0) {

		if (!(num % 2)) {
			str += '0';
			num = num / -2;
		}
		else {
			str += '1';
			num = (num - 1) / -2;
		}
	}

	reverse(str.begin(), str.end());

	cout << str << endl;

	return 0;
}