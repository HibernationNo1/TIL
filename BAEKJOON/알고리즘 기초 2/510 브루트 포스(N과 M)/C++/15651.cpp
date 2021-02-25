#include<iostream>

using namespace std;

#define endl '\n'

int n, m;
int res[8];
bool stc[8];

void Func(int k) {
	if (m == k) {
		for (int i = 0; i < m; i++) {
			cout << res[i] << " ";
		}
		cout << endl;
		return;
	}

	for (int i = 0; i < n; i++) {
		res[k] = i + 1;
		Func(k + 1);
	}
}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> n >> m;
	Func(0);

	return 0;
}