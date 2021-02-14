#include<iostream>
#include<cmath>
#include<vector>

using namespace std;

#define endl '\n'


int main(void) {

	string two;
	cin >> two;

	int tmp = two.size();

	if (tmp % 3 == 1) {
		cout << two[0] - 48;
	}
	else if (tmp % 3 == 2) {
		cout << (two[0] - 48) * 2 + two[1] - 48;
	}
	
	for (int i = tmp % 3; i < tmp; i +=3) {
		cout << ((two[i] - 48) * 4) + ((two[i + 1] - 48) * 2) + (two[i + 2] - 48);
	}

	cout << endl;

	return 0;
}