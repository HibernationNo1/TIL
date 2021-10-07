#include <iostream>


using namespace std;

int main(void)
{
	int series;
	int a, d, n;
	cin >> a >> d >> n;
	series = a + (d * (n-1));
	cout << series << endl;
	

	return 0;
}