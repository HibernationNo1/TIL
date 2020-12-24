#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	int h, b, c;
	unsigned int cd;
	double CD;
	cin >> h >> b >> c ;
	cd = h * b * c ;
	CD = cd/pow(2, 23); //2^23 비트 = 1메가바이트
	cout<<fixed;
	cout.precision(2);
	cout << CD << " MB" << endl;

	return 0;
}