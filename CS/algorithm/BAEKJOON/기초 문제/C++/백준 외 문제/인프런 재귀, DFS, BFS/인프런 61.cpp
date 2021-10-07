#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

int cnt = 0;

void Dfs(int x, int y, vector<int>& z, vector<int>& a, int b)
{
	if (x > y) {
		int sum = 0;
		for (int i = 0; i<int(z.size()); i++) {
			if (a[i] == 2) sum += z[i];
			else if (a[i] == 1) sum -= z[i];
		}
		if (sum == b) cnt++;
	}
	else {
		a[x - 1] = 2;
		Dfs(x + 1, y, z, a, b);
		a[x - 1] = 1;
		Dfs(x + 1, y, z, a, b);
		a[x - 1] = 0;
		Dfs(x + 1, y, z, a, b);
	}

}

int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m;
	cin >> n >> m;
	vector<int> foo(n);
	vector<int> bar(n);
	for (int i = 0; i < n; i++) {
		cin >> foo[i];
	}

	Dfs(1, n, foo, bar, m);

	cout << cnt << endl;

	return 0;
}