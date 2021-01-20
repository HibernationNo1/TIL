// 이 코드는 스마트포인터를 활용, 백준에서는 컴파일 에러로 뜬다.
#include <iostream>
#include <algorithm>

using namespace std;

int main(void)
{
	int n, i; 
	cin >> n;
	unique_ptr<int[]> a;
	a = make_unique<int[]>(n);

	for (i = 0; i < n; i++) {
		cin >> a[i];
	}

	sort(a.get(), a.get() + n, less<int>());

	cout << a[0] << " " << a[n-1];

	return 0;
}