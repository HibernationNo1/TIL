#include <iostream>
using namespace std;

int main(void)
{
	int i;
	char data[200];
	cin >> data;
	for (i = 0 ; data[i] != '\0'; i++)  // 반복문 for문 활용 (초기, 조건, 스탭)
		// != 의미: R value는 L value가 아니다.  '\0' 의미 = NULL
		// 문자열은 마지막 열에 \0이라는 정보가 담겨있으며 이 것은 문자열의 종료하는 의미 
	{
		cout << "'" << data[i] << "'" << endl;
	}

	return 0;
}