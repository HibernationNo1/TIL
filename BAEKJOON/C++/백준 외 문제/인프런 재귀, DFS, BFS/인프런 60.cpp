#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

bool flag = false;

void DFS(vector<int> &x, int y, vector<int> &z, int a)
{
	if (y > a) {
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < int(z.size()); i++) {
			if (z[i] == 1) sum1 += x[i];
			else sum2 += x[i];
		}
		if (sum1 == sum2) flag = true;
	}
	else {
		z[y - 1] = 1;
		DFS(x, y + 1, z, a);
		z[y - 1] = 0;
		DFS(x, y + 1, z, a);
	}
}

int main(void)
{
	int n;
	cin >> n;
	vector<int> foo(n);
	vector<int> bar(n);
	for (int i = 0; i<int(foo.size()); i++) {
		cin >> foo[i];
	}

	DFS(foo, 1, bar, n);

	if (flag == 1) cout << "YES" << endl;
	else cout << "NO" << endl;

	return 0;
}