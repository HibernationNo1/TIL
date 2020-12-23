#include <iostream>

using namespace std;

int main(void)
{
	int year, month, day;
	char dot1, dot2;
	cin >> year >> dot1 >> month >> dot2 >> day;
	cout.width(4); // 출력값 길이 '최소' 4자리 >> 4자리보다 길면 그냥 다 출력
	cout.fill('0'); // 출력값 길이에 남는 자리에 앞자리부터 0을 채워넣는다.
	cout << year << dot1;
	cout.width(2);
	cout.fill('0');
	cout << month << dot2;
	cout.width(2);
	cout.fill('0');
	cout << day << endl;



	return 0;
}