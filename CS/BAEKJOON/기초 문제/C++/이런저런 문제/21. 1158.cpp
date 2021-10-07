#include<iostream>
#include<vector>
#include<list>

using namespace std;

#define endl '\n'

int main(void) {
	
	int n, k;
	cin >> n >> k;
	vector<int> tmp(n);
	for (int i = 0; i < n; i++) {
		tmp[i] = i + 1;
	}
	list<int> foo(tmp.begin(), tmp.end());
	list<int>::iterator first = foo.begin();
	list<int>::iterator last = foo.end();
	last--;

	for (int i = 0; i < n; i++) {
		int j = k-1;

		while (j--) {
			if (first != last) {
				first++;
			}
			else if (first == last) {
				first = foo.begin();
			}
		}
		
		tmp[i] = *first;

		if (last == foo.begin()) {
			break;
		}


		if (first != last) {
			first = foo.erase(first);
			
		}
		else if (first == last) {
			foo.erase(first);
			first = foo.begin();
		}
		
		last = foo.end();
		last--;
	}

	cout << "<";
	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			cout << tmp[i];
			break;
		}
		cout << tmp[i] << ", ";
	}
	cout << ">" << endl;

	return 0;
}