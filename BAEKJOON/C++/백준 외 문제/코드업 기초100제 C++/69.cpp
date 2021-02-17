#include <iostream>
using namespace std;

int main(void)
{
	char a;
	cin >> a;
	switch (a)  // switch문 활용
	{
	case 'A': cout << "best!!!" << endl;
		break;
	case 'B': cout << "good!!" << endl;
		break;
	case 'C': cout << "run!" << endl;
		break;
	case 'D':cout << "slowly~" << endl;
		break;
	default: cout << "what?" << endl;
		break;
			
	}

	return 0;
}