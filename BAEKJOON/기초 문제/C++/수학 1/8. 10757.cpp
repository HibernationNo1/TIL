#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int num_sum = 0;     // 올림수
string a, b;
string result;

string sum()
{
	for (int i = 0; i < a.size(); i++)
	{
		int num_A, num_B;
		num_A = a[i] - 48;       // ASCII 에서 숫자로 
		num_B = b[i] - 48;		//  size - (i+1) 는 1의자리부터 계산함을 의미

		if (num_A + num_B + num_sum >= 10)		// 두 수 + 올림수의 의 합이 10보다 크면
		{
			
			result += to_string((num_A + num_B+ num_sum) % 10);	// 해당 자리의 숫자
			num_sum = 1;					// 다음자리의 숫자  + 1
		}
		else
		{
			
			result += to_string(num_A + num_B + num_sum);
			num_sum = 0;
		}
	}

	if (num_sum == 1)       // 만약 마지막 올림수가 1이라면
	{
		result += to_string(1);   // result 배열의 마지막에 1 추가.
	}

	return result;
}

int main(void)
{
	cin >> a >> b;
	
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());

	if (a.size() >= b.size())
	{
		b.resize(a.size(), '0');   // b배열의 사이즈를 a만큼 키우고 원소 값을 문자 '0'으로 채운다. 
	}
	else
	{
		a.resize(b.size(), '0');
	}
	
	sum();

	reverse(result.begin(), result.end());

	cout << result << endl;

	return 0;
}