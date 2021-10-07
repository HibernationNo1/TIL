#include <iostream>
using namespace std;

int main(void)
{
	int a=1;
	while (a != 0)    //while문. 조건이 0(false)일때 동작이 멈춘다. 1을 넣으면 무한루프
	{
		cin >> a;
		if (a != 0)
		{
			cout << a << endl;
		}
		else
		{
			return 0;
		}
}

	return 0;
}
