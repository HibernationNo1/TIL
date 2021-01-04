#include <iostream>

using namespace std;

int main(void)
{
	int T;
	cin >> T;
	int* h = new int[T + 1];
	int* w = new int[T + 1];
	int* n = new int[T + 1];



	for (int i = 1; i <= T; i++)
	{
		cin >> h[i] >> w[i] >> n[i];
		//y는 최대 h만큼, x는 최대 w만큼
		int tmp_y, tmp_x;
		tmp_x = (n[i] / h[i]) + 1;   // h[i] 높이의 층을 돈 횟수. 즉, 호수
		tmp_y = n[i] % h[i];   // 층을 돌고 남은 횟수. 즉, 들어갈 층

		if (tmp_y == 0)      // 맨 윗층이면
		{
			cout << h[i] * 100 + tmp_x - 1 << endl;
		}
		else
		{
			cout << tmp_y * 100 + tmp_x << endl;
		}

	}

	delete[] h;
	delete[] w;
	delete[] n;

	return 0;

}