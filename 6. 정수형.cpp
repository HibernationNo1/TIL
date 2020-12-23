#include <iostream>
#include <cmath> // 제곱을 계산하게 위해서 cmath헤더 포함
using namespace std;

int main(void)
{
	short	s = 1;
	int		i = 1;
	long	l = 1;
	long long l2 = 1;

	cout << sizeof(short) << endl;  // short형의 크기 = 2바이트
	cout << pow(2, 16) << endl;  // pow(a,b)  == a의 b제곱을 계산한다.
	// short는 2byte = 2*8bits = 16bits    short형으로 표현 가능한 숫자 범위 = (2^15) -1
	// 맨 앞의 한 비트는 부호를 표현하는데 써야하기 때문, 전체 범위 중 0 또한 하나의 경우.
	cout << sizeof(int) << endl;
	cout << sizeof(long) << endl;
	cout << sizeof(long long) << endl;

	s = 32767;  // short형에서 표현할 수 있는 가장 큰 숫자
	s = s + 1; //32768을 할당하면?
	cout << s << endl; // -32768이 출력이 된다. 이것이 overflow현상
	unsigned int i = -1;  // unsigned int의 overflow. 프로그램에서 오류로 표현하지 않는다.
}