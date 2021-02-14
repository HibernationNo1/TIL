#include <iostream>

using namespace std;

int main(void)
{
	int u_num = 1, d_num = 1;
	int num = 1, X;
	cin >> X;

	if (X == 1)
		goto out;

	if (u_num == 1 && (d_num % 2 == 1)) // 분자 1, 분모 홀수 
	{
		here2:
		d_num++;  // 가로 한 칸 이동
		num++;
		if (num == X)
		{
			goto out;
		}

		while(1)  // 아래 대각 이동
		{
			
			u_num++;
			d_num--;
			num++;
			if (num == X)
			{
				goto out;
			}
			else if (d_num == 1 && (u_num % 2 == 0)) // 분자 짝수, 분모 홀수
			{
				goto here1;
			}

		}
	}

	if (d_num == 1 && (u_num % 2 == 0)) // 분자 짝수, 분모 홀수  >> 새로 이동
	{
	    here1:
		u_num++;  // 새로 한 칸 이동
		num++;
		if (num == X)
		{
			goto out;
		}

		while (1)  // 윗 대각 이동
		{
			u_num--;
			d_num++;
			num++;
			if (num == X)
			{
				goto out;
			}
			else if (u_num == 1 && (d_num % 2 == 1)) // 분자 1, 분모 홀수 
			{
				goto here2;
			}
		}
	}

out:

	cout << u_num << "/" << d_num << endl;
	return 0;

}