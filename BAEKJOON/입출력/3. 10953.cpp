#include <iostream>
using namespace std;

int main(void)
{

	int T, A, B, i;
	char C;
	cin >> T;
	for (i = 1; i <= T; i++) {
		cin >> A >> C >> B;
		cout << A + B << endl;
	}
	
	return 0;
}