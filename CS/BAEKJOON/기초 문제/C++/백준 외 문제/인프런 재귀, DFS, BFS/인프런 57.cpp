#include<iostream>

using namespace std;

#define endl '\n'

void Binary(int x) 
{
	if (x == 0) return;
	else {
		Binary(x / 2);
		cout << x % 2;
	}
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	Binary(n);

	return 0;
}