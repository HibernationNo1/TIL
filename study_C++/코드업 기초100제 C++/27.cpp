#include <iostream>
using namespace std;

int short1(int S)
{
	cout.width(2);
	cout.fill('0');
	cout << S << "-";
	return 0;

}

int main(void)
{
	int a, b, c;
	char x, y;
	cin >> a >> x >> b >> y >> c;
	short1(c);
	short1(b);
	cout.width(4);
	cout.fill('0');
	cout << a << endl;

	cout.width(2);
	cout.fill('0');

	return 0;
}