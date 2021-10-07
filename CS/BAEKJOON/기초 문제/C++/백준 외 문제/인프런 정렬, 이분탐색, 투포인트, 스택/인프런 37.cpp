#include<iostream>
#include<algorithm>
#include<deque>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int s, n, i, num;
	cin >> s >> n;

	deque<int> arr(s);


	for (i = 0; i < n; i++) {
		cin >> num;
		for (int j = 0; j < s; j++) {
			if (arr[j] == num) {
				arr.erase(arr.begin() + j);
				arr.push_front(num);
				//cache hit
				break;
			}

			if (j == s - 1) {
				arr.erase(arr.end()-1);
				arr.push_front(num);
				//cache miss
				break;
			}
		}
	}

	for (i = 0; i < s; i++) {
		cout << arr[i] << endl;
	}

	return 0;
}