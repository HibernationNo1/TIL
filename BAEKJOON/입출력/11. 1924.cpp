#include <iostream>
#include<string>
using namespace std;

int main(void)
{
	string day[8] = { "SUN", "MON", "TUE" , "WED" , "THU" , "FRI" , "SAT" };
	int month[13] = { 31, 28, 31, 30 ,31, 30, 31, 31, 30, 31, 30, 31 };
	int x, y, i, sum = 0;
	cin >> x >>  y;

	for (i = 0; i < x; i++) {
		if (i == x-1) {
			sum += y;
			cout << day[sum % 7] << endl;
		}
		else
			sum += month[i];

	}

	return 0;
}