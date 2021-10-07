#include<iostream>
using namespace std;

#define endl '\n'

int devide(int x, int y)
{
	if (!(x % y)) return y;
	else return devide(y, x % y);
}

int main(void) {
	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		int a, b, g;
		cin >> a >> b;

		g = devide(a, b);

		cout << (a * b) / g << endl;
	}

	

	return 0;
}