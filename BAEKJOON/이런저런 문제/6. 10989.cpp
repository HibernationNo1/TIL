#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'



int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n;
	cin >> n;

	int arr[10001] = {};
	int a;

	for (int i = 0; i < n; i++) {
		cin >> a;
		arr[a]++;
	}

	for (int i = 0; i < 10001; i++) {
		for (int j = 0; j < arr[i]; j++) {
			cout << i << endl;
		}
	}


	return 0;
}