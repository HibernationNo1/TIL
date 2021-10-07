#include <iostream>

using namespace std;

int main(void)
{
	int hour, minute;
	char a;
	cin >> hour >> a >> minute;  // int받고 char이 아닌 minute을 바로 받는다면 바로 결과값 출력
	cout << hour << a << minute;

	return 0;
}