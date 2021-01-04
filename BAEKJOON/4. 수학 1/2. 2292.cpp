#include <iostream>
#include <cmath>

using namespace std;

int main(void)
{
	int N;
	cin >> N;
	int num1=0, num2=0, a, b = 2;
	
	num1 = (3 * pow(b, 2)) - (3 * b) + 1;
	a = b - 1;
	num2 = (3 * pow(a, 2)) - (3 * a) + 1;

		while (1)
		{ 
			if (N == 1)
			{
				cout << 1 << endl;
				break;
			}
			else if (num2 < N && N <= num1)
			{
				cout << b << endl;
				break;
			}

		 b++;
		 num1 = (3 * pow(b, 2)) - (3 * b) + 1;
		 a = b - 1;
		 num2 = (3 * pow(a, 2)) - (3 * a) + 1;
		}

	return 0;

}