#include <iostream>
using namespace std;
int main(void)
{
	int num[11][11] = {};
	
	for (int y = 1; y <= 10; y++) //10번 실행
	{
		for (int x = 1; x <= 10; x++) //10번 실행
		{
			cin >> num[y][x];
		}
	}
	
	
	int x, y;
	x = y = 2;
	if (num[2][2] == 0) // 시작지점에 먹이가 없을 때
	{
		num[2][2] = 9;
		while (1)
		{

			if (num[y][x + 1] == 1) // 오른쪽에 벽이 있을 때
			{
				if (num[y + 1][x] == 2) //오른쪽에 벽이 있어서 아래를 봤는데 먹이가 있을 때
				{
					num[y + 1][x] = 9;      // 아래로 이동 후 break;
					break;
				}
				else if (num[y + 1][x] == 0) // 아래 벽이 없을 때 
				{
					num[y + 1][x] = 9;      // 아래로 이동 후 해당 좌표 저장
					y++;
				}
				else if (num[y + 1][x] == 1) // 아래도 벽이 있을 때
				{
					break; // 동작 금지
				}
			}
			else if (num[y][x + 1] == 0) //오른쪽에 벽이 없을 때
			{
				num[y][x + 1] = 9; // 오른쪽으로 이동 후 해당 좌표 저장
				x++;
			}
			else if (num[y][x + 1] == 2) // 오른쪽에 먹이가 있을 때
			{
				num[y][x + 1] = 9; // 오른쪽으로 이동 후 break;
				break;
			}
			
		}
	}
	else if (num[2][2] == 2)  //시작부터 먹이가 있을 때 
	{
		num[2][2] = 9;
	}


	for (int y = 1; y <= 10; y++) //10번 실행
	{
		for (int x = 1; x <= 10; x++) //10번 실행
		{
			cout << num[y][x] << " ";
		}
		cout << endl;
	}

	return 0;
}