#include<iostream>

using namespace std;

#define endl '\n'

int n, m;
int arr[8];
bool stc[8];

void Foo(int k) {
	if (k == m) {
		for (int i = 0; i < m; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		return;
	}

	for (int i = 0; i < n; i++) {
		if (!stc[i]) {
			arr[k] = i + 1;
			stc[i] = true;
			Foo(k + 1);
			stc[i] = false;
		}
	}
	return;
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n >> m;

	Foo(0);

	return 0;
}