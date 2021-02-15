#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

void Binary(int x, int y, vector<int>& z) {
	if (x > y) {
		for (int i = 0; i<int(z.size()); i++) {
			if (z[i] == 1) cout << i + 1 << " ";
		}
		cout << endl;
	}
	else {
		z[x - 1] = 1;
		Binary(x + 1, y, z);
		z[x - 1] = 0;
		Binary(x + 1, y, z);
	}
}

int main(void)
{
	int n;
	cin >> n;
	vector<int> arr(n);

	Binary(1, n, arr);

	return 0;
}