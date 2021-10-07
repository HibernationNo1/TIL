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

	for (int i  = 0; i < n; i++) {
		if (!stc[i]) {
			res[k] = i + 1;
			for (int j = 0; j <= i; j++) {
				stc[j] = true;
			}
			Func(k + 1);
			for (int j = 0; j <= i; j++) {
				stc[j] = false;
			}
		}
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