#include <iostream>
using namespace std;

int main(void)
{
	
	int a;

	cin >> a;

	here:
		cout << a << endl;
		a--;
	if(a !=0)
	{
		goto here;
	}
	else if (a==0)
	{
		return 0;
	}

	return 0;
}