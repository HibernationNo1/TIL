#include <iostream>
using namespace std;

int main(void)
{
	int a;
here:          //goto문 사용.  이름: 형태. 들여쓰기 안함. 출구
	cin >> a;

	if (a != 0)
	{
		cout << a << endl;
		goto here;    //goto 이름; 형태. 입구

	}
	else if (a == 0)
	{
		return 0;
	}

	return 0;
}
