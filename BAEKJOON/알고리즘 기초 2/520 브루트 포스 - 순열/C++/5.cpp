#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

int main(void) {
	int n;
	cin >> n;
	vector<int> sco(n);
	vector<int> time;
	vector<vector<int>> stage(n, vector<int>(n*n));
	for (int i = 0; i < n * n; i++) {
		cin >> sco[i];
		int tmp;
		cin >> tmp;
		for (int j = 0; j < tmp; j++) {
			
		}
	}
	

	return 0;
}