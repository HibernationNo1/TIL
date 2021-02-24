#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, p2 = 0, p3 = 0, p5 = 0, count = 1, tmp;
	cin >> n;
	deque<int> arr;
	arr.push_back(1);
	while (count < n) {  // 3, 2, 5로만 나눠져야 한다.
		tmp = min({ arr[p2] * 2, arr[p3] * 3, arr[p5] * 5 });
		if (tmp == arr[p2] * 2) {
			if (arr[p2] * 2 == arr.back()) {
				p2++;
				continue;
			}
			arr.push_back(arr[p2] * 2);
			p2++;
		}
		else if (tmp == arr[p3] * 3) {
			if (arr[p3] * 3 == arr.back()) {
				p3++;
				continue;
			}
			arr.push_back(arr[p3] * 3);
			p3++;
		}
		else if (tmp == arr[p5] * 5) {
			if (arr[p5] * 5 == arr.back()) {
				p5++;
				continue;
			}
			arr.push_back(arr[p5] * 5);
			p5++;
		}
		count++;
	}
	cout << arr[count-1] << endl;

	return 0;
}