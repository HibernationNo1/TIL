#include<iostream>
#include<cstring>
#include<algorithm>

using namespace std;
int cont[101];

int main(void)
{
	int n, m, tmp;
	cin >> n >> m;
	for (int i = 1; i <=n; i++) {
		cin >> tmp;

		if (tmp > m) {
			cont[i] = cont[i-1] + 1;
		}
		else {
			cont[i] = 0;
		}
	}

	sort(begin(cont), end(cont), greater<int>());
	if (cont[0] == 0) {
		cout << -1 << endl;
	}
	else {
		cout << cont[0] << endl;
	}
	
	return 0;
}