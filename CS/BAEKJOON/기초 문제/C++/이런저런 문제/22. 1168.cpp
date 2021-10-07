#include<iostream>
#include<vector>


using namespace std;

#define endl '\n'

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, k;
	cin >> n >> k;
	vector<int> left(n);
	vector<int> right;

	for (int i = 0; i < n; i++) {
		left[i] = i + 1;
	}

	int index = 0, i = 0;
	cout << "<";
	while (!left.empty()) {
		index = (index + (k - 1)) % left.size();
		right.push_back(left[index]);
		left.erase(left.begin()+index);	

		if (i == n - 1) {
			cout << right[i];
			break;
		}
		cout << right[i++] << ", ";
	}
	cout << ">" << endl;

	
	return 0;
}