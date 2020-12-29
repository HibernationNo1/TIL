#include <iostream>
using namespace std;

int main(void)
{
	string s;
	cin >> s;
	int alphabet[27] = { 2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7,7,7,8,8,8,9,9,9,9 };
	int time = 0, sum_time = 0;
	for (int i = 0; i < s.size(); i++)
	{
		int tmp = s[i] - 65;  // 'A' = 0
		switch(alphabet[tmp])
		{
		case 2: 
			time = 3;
			break;
		case 3:
			time = 4;
			break;
		case 4:
			time = 5;
			break;
		case 5:
			time = 6;
			break;
		case 6:
			time = 7;
			break;
		case 7:
			time = 8;
			break;
		case 8:
			time = 9;
			break;
		case 9:
			time = 10;
			break;
		}		
		sum_time += time;
	}
	cout << sum_time << endl;

	return 0;
}