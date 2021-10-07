# 이분검색(이진탐색 - Binart Search)

검색할 자료를 반씩 나누어 나머지 반만 검색하는 방식을 반복하여 자료를 찾는 검색(탐색) 방법으로, 정렬된 1차원 배열의 자료에서 원하는 값을 빠르게 찾는 알고리즘이다.

- 시간 복잡도: O(log n)

- 알고리즘 원리

  > 배열의 중간에 있는 임의의 값을 선택하여 찾고자 하는 값 X와 비교한다. X가 중간 값보다 작으면 중간 값을 기준으로 좌측의 데이터들을 대상으로, X가 중간값보다 크면 배열의 우측을 대상으로 다시 탐색한다. 동일한 방법으로 다시 중간의 값을 임의로 선택하고 비교한다. 해당 값을 찾을 때까지 이 과정을 반복한다.
  >
  > (up, down 게임)

**코드 예시**

```c++
#include<iostream>
#include<algorithm>
#include<memory>

using namespace std;

#define endl '\n'

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, key, le, ra, mid;
	unique_ptr<int[]> arr;
	cin >> n >> key;
	arr = make_unique<int[]>(n);
	le = 0;  // 왼쪽부터
	ra = n - 1;  // 오른쪽부터
	mid = (le + ra) / 2;  // 중간 값

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	
	sort(arr.get(), arr.get() + n, less<int>()); // 데이터 정렬
	
	while (le <= ra) {
		
		if (arr[mid] == key) {
			cout << mid + 1 << endl;
			break;
		}
		else if (arr[mid] < key) le = mid + 1;
		else if (arr[mid] > key) ra = mid - 1;

		mid = (le + ra) / 2;
	}

	return 0;
}
```

