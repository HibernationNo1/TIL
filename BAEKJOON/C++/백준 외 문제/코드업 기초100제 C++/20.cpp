#include <iostream>

using namespace std;

int main(void)
{
	int front, back;
	char slash;

	cin >> front >> slash >> back;
	cout.width(6);
	cout.fill('0');
	cout << front;
	cout.width(7);
	cout.fill('0');
	cout << back;


	return 0;
}