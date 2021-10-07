#include <iostream>
using namespace std;

int main(void)
{

	int T, A, B, i;
	cin >> T;
	for (i = 1; i <= T; i++) {
		cin >> A >> B;
		cout <<"Case #"<<i<<": "<< A <<" + " << B << " = " << A+B << endl;
	}
	
	return 0;
}