#include <iostream>

using namespace std;

int main(void)
{
	int N, result = -1;
	cin >> N;
		
	if (N % 5 == 0)
	{
		cout << N / 5 << endl;
	}
	else
	{
		int N2;
		N2 = N - (N / 5 * 5);     //  
		if (N2 % 3 == 0)
		{
			result = (N / 5) + (N2 / 3);
			cout << result << endl;
		}
		else
		{
			for (int i = 1; i <= N / 5; i++)
			{
				int N3 = N - (N / 5 - i) * 5;           
				if (N3 % 3 == 0)
				{
					result = (N / 5) - i + (N3 / 3);     
					cout << result << endl;
					break;
				}
				continue;
			}       
			
			if (result == -1)
			{
				cout << result << endl;
			}
		}
	}

		
	return 0;
}