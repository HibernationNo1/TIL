#include <iostream>

using namespace std;

int main(void)
{
	char Alphabet;
	
	while (1)
	{
		cin >> Alphabet;
		if (Alphabet == 'q')
		{
			cout << Alphabet << endl;
			break;
		}
		else
		{
			cout << Alphabet << endl;	
			continue;
		}
	}

	return 0;
}