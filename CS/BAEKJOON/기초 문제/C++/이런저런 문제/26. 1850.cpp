#include<iostream>

using namespace std;

#define endl '\n'

long long divide(long long x, long long y) {
	
	if (!(x % y)) return y;
	else return divide(y, x % y);
}

int main(void) {
	
	long long a, b, c;
	cin >> a >> b;

	c = divide(a, b);
		
	string num;
	


	for (long long i = 1; i <= c; i++) {
		num += '1';
	}

	cout << num << endl;

	return 0;
}