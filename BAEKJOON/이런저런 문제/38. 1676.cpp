#include<iostream>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	int n, count = 0;
	cin >> n;
	
	count += (n / 5);
	count += (n / 25);
	count += (n / 125);

	cout << count << endl;
	
	return 0;
}