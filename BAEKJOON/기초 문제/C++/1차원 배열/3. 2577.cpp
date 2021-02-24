#include <iostream>
#include<cmath>

using namespace std;

int main(void)
{
	int A, B, C;
	cin >> A >> B >> C;
	int num = A * B * C;
	int i = (int)log10(num);  // 밑이 10인 log함수 == log10() , 밑이 e인 자연로그 == log()
	//log는 double, float, long double형이 있다. long double log10()

	int *number = new int[i+1];
	int sum[10] = {};
	
	for (int j = 0; j <= i; j++)
	{
		sum[j] = 0;
	}

	for (int j = 0; j <= i; j++)
	{
		number[j] = (int)(num / pow(10, j)) % 10;

		if (number[j] != 0)
		{
			int a;
			a = number[j];
			sum[a]++;
		}
		else if (number[j] == 0)
		{
			sum[0]++;
		}
	}
	for (int j = 0; j <= 9; j++)
	{
		cout << sum[j] << endl;
	}
	

	delete number;

	return 0;
}