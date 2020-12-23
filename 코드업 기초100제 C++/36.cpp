#include <iostream>
using namespace std;


int main(void)
{
	char A;
	cin >> A;
	cout << (int)A << endl;  // (int)A 는 A를 int형으로. 즉, 문자를 아스키 코드(ASCII)로 인식 후 10진수 정수형으로 변환시켜 표현한다.

	return 0;
}