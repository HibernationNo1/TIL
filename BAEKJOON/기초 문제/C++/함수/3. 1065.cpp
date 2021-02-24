#include <iostream>
#include <string>
using namespace std;

int OneNumber(int x) 
{
	int a, b, n = 0;
	int s[4] = {};      // 1000보다 작거나 같으니 최대 4자리 숫자
	string num = to_string(x);

	for (int i = 0; i<num.size(); i++ )
	{
		s[i] = num[i] - 48;  // s[i] 에 각 자릿수 숫자 들어감
	}
	
	if (num.size() == 3)  // x = 100~999
	{
		a = (s[0] - s[1]) - (s[1] - s[2]);    // ex) 135
		b = (s[1] - s[0]) - (s[2] - s[1]);

		if ((a == 0) || (b == 0))     // 한수인지 아닌지 판별
		{
			n = 1;     // 한수면 1리턴, 한수가 아니면 0 리턴
		}
	}
	else if (num.size() == 4)  // x = 1000
	{
		n = 0;
	}

	


	return n;

}

int main(void)
{

	int N, sum;
	cin >> N;

	if (N >= 100)   // 1~99까지 한수.
	{
		sum = 99;
		for (int i = 100; i <= N; i++)
		{
			sum = sum + OneNumber(i);
		}
	}
	else if (N <= 99)
	{
		sum = N;
	}

	cout << sum << endl;

	return 0;

}