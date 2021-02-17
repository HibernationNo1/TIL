#include <iostream>
using namespace std;


int main(void)
{
	double num;
	cin >> num;
	cout << fixed; 
	cout.precision(11);  // 앞에서부터 11자리를 추출하여 마지막 자리 반올림됨.
	// fixed를 먼저 사용하고 precision을 사용하면 소수점 아래 11자리까지 표현하겠다는 의미
	// 표현하고자 하는 자리수 보다 현재 자리수가 적을 경우 나머지 자리수는 0으로 채워진다.
	cout << num << endl;
	return 0;
}