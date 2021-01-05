#include <iostream>
using namespace std;
int main(void)
{
	int num[20][20] = {};
	for (int y = 1; y <= 19; y++)
	{
		for (int x = 1; x <= 19; x++)
		{
			cin >> num[y][x];
		}
	}

	int n;
	cin >> n;

	for (int i = 1; i <= n; i++)
	{
		int a, b, c;
		cin >> a >> b;  // x좌표 받은 후 y좌표 받는다.
		c = num[a][b];  // 근데 x좌표인 a를 y좌표로, y좌표인 b를 x좌표로 바꿔 입력해야 정답이 나온다. 왜?
		for (int y = 1; y <= 19; y++)
		{
			if (num[y][b] != 0)
			{
				num[y][b] = 0;
			}
			else if (num[y][b] == 0)
			{
				num[y][b] = 1;
			}
		}
		for (int x = 1; x <= 19; x++)
		{
			if (num[a][x] != 0)
			{
				num[a][x] = 0;
			}
			else if (num[a][x] == 0)
			{
				num[a][x] = 1;
			}
		}
		num[a][b] = c;

	}

	for (int y = 1; y <= 19; y++)
	{
		for (int x = 1; x <= 19; x++)
		{
			cout << num[y][x] << " ";
		}
		cout << endl;
	}

	return 0;
}