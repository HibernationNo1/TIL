#include<iostream>

using namespace std;

#define endl '\n'

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int e, s, m, res = 1;
	cin >> e >> s >> m;

	while (1) {
		if (!((res - e) % 15) && !((res - s) % 28) && !((res - m) % 19)) {
			cout << res << endl;
			return 0;
		}
		res++;
	}

	return 0;
}