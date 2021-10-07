#include <iostream>
using namespace std;


int main(void)
{
	int a;
	long long int b;
	cin >> a ;
	b = static_cast<long long> (a) +1;  // int 형인 a를 int형보다 상위 long long int 형인 b에 할당하려면
	// static_cast<long long>(a)를 해줘야 한다. 안해도 빌드는 되긴 된다.
	// 프로그램에서 노란전구로 알려줌

	cout << b << endl;


	return 0;
}