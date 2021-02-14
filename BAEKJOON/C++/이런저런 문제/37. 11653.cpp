#include<iostream>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, i = 2;
	cin >> n;
	if (n == 1) return 0;



	while (n-1) {
		if (!(n % i)) {
			cout << i << endl;
			n = n / i;
		}
		else {
			i++;
		}
		
	}
	
	return 0;
}