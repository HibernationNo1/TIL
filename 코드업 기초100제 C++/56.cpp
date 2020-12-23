#include <iostream>
using namespace std;

int main(void)
{
	bool a, b;
	cin >> a >> b;

	if ((!a&&b)||(a&&!b)) // 두 값이 서로 다를때만 참: XOR연산 사용
	{
		cout << ((!a && b) || (a && !b)) << endl;
	}
	else
	{
		cout << ((!a && b) || (a && !b)) << endl;
	}

	return 0;
}
