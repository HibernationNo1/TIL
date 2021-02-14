#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(void)
{
	string two_num;  // [7]
	getline(cin, two_num);
	char* RB_two_num = new char[two_num.size()+1];   // [8]
	fill_n(RB_two_num, two_num.size(), ' ');   // two_num배열 만큼의 크기에 ' ' 공백 입력
	int* num = new int[two_num.size()+1];  // 숫자가 들어갈 two_num 사이즈의 배열
	fill_n(num, two_num.size(), 0);     // num 배열 0으로 초기화
	int sum1 = 0, sum2 = 0;
	
	for (int i = 0; i < two_num.size(); i++)    // 0부터 6까지 7번
	{
		RB_two_num[i] = two_num[two_num.size() - 1 - i];  // RB_two_num 에 two_num 와 반대 순서로 배열 할당
		num[i] = RB_two_num[i] - 48; // 0의 ASCII코드는 48이므로
		if (num[i] == -16)      // 빈 공강
		{
			num[i] = 0;
		}
	}

	for (int i = 0; i < 3; i++)  // sum1에 앞의 세 자리 숫자 100의자리~1의자리 합쳐서 할당
	{
		sum1 = sum1 + (num[i] * pow(10, 2 - i));
	}
  
	for (int i = 4; i < two_num.size(); i++)  // sum2에 뒤의 세 자리 숫자 100의자리~1의자리 합쳐서 할당
	{
		sum2 = sum2 + (num[i] * pow(10, 2 +4- i));
	}

	if (sum2 > sum1)
	{
		cout << sum2 << endl;
	}
	else if (sum2 < sum1)
	{
		cout << sum1 << endl;

	}

	delete RB_two_num;
	delete num;

	return 0;
}