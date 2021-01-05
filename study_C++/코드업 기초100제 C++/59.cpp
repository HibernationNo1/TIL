#include <iostream>
using namespace std;

int main(void)
{
	int a;
	cin >> a;
	a = ~a; // ~: 비트단위로 !을 취해주는 연산자
	// 비트단위 연산자 
	//~(bitwise not), &(bitwise and), |(bitwise or), ^(bitwise xor),
	//<< (bitwise left shift), >> (bitwise right shift)

	cout << a << endl;

	return 0;
}