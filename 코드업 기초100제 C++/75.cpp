#include <iostream>
using namespace std;

int main(void)
{

	int a;

	cin >> a;
	a--;
	while (a >= 0)
	{
		cout << a << endl;
		a--;  // a = a--; 를 해도 되지만 코드업에 소스 제출할때 '출력 한계 초과' 발생
	}

	return 0;
}