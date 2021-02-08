#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n1, n2, i, p1 = 0, p2 = 0 ;
	
	cin >> n1;
	vector<int> arr1(n1);
	for (i = 0; i < n1; i++) {
		cin >> arr1[i];
	}
	sort(arr1.begin(), arr1.end());

	cin >> n2;
	vector<int> arr2(n2);
	for (i = 0; i < n2; i++) {
		cin >> arr2[i];
	}
	sort(arr2.begin(), arr2.end());

	while (p1 < n1 && p2 < n2) {
		if (arr1[p1] == arr2[p2]) {
			cout << arr1[p1]<< " ";
			p1++;
			p2++;
		}
		else if (arr1[p1] > arr2[p2]) {
			p2++;
		}
		else p1++;
	}

	return 0;
}