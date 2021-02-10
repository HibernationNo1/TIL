#include<iostream>
#include<deque>
#include<algorithm>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, p2 = 0, p3 = 0, p5 = 0, count = 1,min;
	cin >> n;
	deque<int> arr;
	arr.push_back(1);
	while (count < n) {  // 3, 2, 5로만 나눠져야 한다.
		if (arr[p2] * 2 < arr[p3] * 3) min = arr[p2] * 2;
		else min = arr[p3] * 3;
		if (arr[p5] * 5 < min) min = arr[p5] * 5;

		if (min == arr[p2] * 2) p2++;
		if (min == arr[p3] * 3) p3++;
		if (min == arr[p5] * 5) p5++;

		arr.push_back(min);
		count++;
	}
	cout << arr[count-1] << endl;

	return 0;
}