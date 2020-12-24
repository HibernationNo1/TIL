#include <iostream>
using namespace std;
int main(void)
{
	int h, w, n, l, d, x, y;
	cin >> h >> w >> n;
	int num[100][100] = {};

	for (int i = 1; i <= n; i++) // 막대의 갯수만큼 반복
	{
		cin >> l;       //각 막대의 길이
		cin >> d;				//방향
		cin >> x >> y;			//좌표
		
		if (d == 1) // 막대가 세로라면 >> x좌표 방향
		{
			for (int i =1; i<=l;i++) // i가 막대의 길이보다 같아질 때 까지
			{
				num[x + i - 1][y] = 1;  // 
			}
		}
		else if (d == 0) // 막대가 가로라면 >> y좌표 방향
		{
			for (int i = 1; i <= l; i++) // i가 막대의 길이보다 같아질 때 까지
			{
				num[x][y+i-1] = 1;
			}
		}
	}

	for (int x_h = 1; x_h <= h; x_h++)  // 세로
	{
		for (int x_w = 1; x_w <= w; x_w++) // 가로 부터 출력
		{
			cout << num[x_h][x_w] << " ";
		}
		cout << endl;
	}
		


	return 0;
}