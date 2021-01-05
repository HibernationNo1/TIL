#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	int h, b, c, s;
	unsigned int cd;
	double CD;
	cin >> h >> b >> c >> s;
	cd = h * b * c * s;
	CD = cd/pow(2, 23); //2^23 비트 = 1메가바이트
	cout<<fixed;
	cout.precision(1);
	cout << CD << " MB" << endl;

	return 0;
}