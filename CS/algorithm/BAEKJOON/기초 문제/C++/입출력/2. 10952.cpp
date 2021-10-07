#include <iostream>
using namespace std;

int main(void)
{

	int A, B;
	while(1)
	{
		cin >> A >> B;
		if ((A == B) && (A == 0))
		{
			break;
		}
		cout << A + B << endl;

		
	}
	return 0;
}