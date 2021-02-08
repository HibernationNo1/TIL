# 투포인터 알고리즘(Two Pointers Algorithm)

말 그대로 두 개의 포인터를 사용하는 알고리즘. 여기서 포인터는 C/C++의 포인터가 아니라, 어느 위치를 가르키는 개념적인 포인터다.

문제 조건이 연속/선행적으로 무언가를 해야할때 사용된다

하나의 1차원 배열의 부분집합을 활용할때 사용할 수 있다.

두 개 이상의 배열의 교집합을 구하는데 활용할 수 있다.



![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fk2s9r%2FbtqEKxMPNIN%2FHRjgjyWIHkaFwdk8XKpktK%2Fimg.png)



- 배열의 index에 접근하는 두 개의 변수를 포인터로 활용한다.

  > 변수 두 개 p = 0, q = 0 를 선언하고
  >
  > 조건을 통해 p 또는 q를 한 칸씩 이동하며 답을 찾는다. 원하는 답을 찾으면 조건에 알맞게 q또는 q(또는 둘 다)를 한 칸씩 이동한다.



**문제(교집합 구하기)**

n1의 크기를 가진 배열과 n2의 크기를 가진 배열을 입력받고 두 배열의 교집합을 출력하는 문제

```c++
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
```



**문제(배열 안에서 부분집합 활용)**

[백준 2003번](https://www.acmicpc.net/problem/2003)

```c++
#include<iostream>
#include<memory>

using namespace std;

#define endl '\n'


int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, i, p = 0, q = 0, count = 0;
	unique_ptr<int[]> arr;
	cin >> n >> m;
	arr = make_unique<int[]>(n);
	for (i = 0; i < n; i++) {
		cin >> arr[i];
	}
	while (p < n && q < n) {
		int sum = 0;
		for (i = p; i <= q; i++) {
			sum += arr[i];
			
		}
		if (sum == m) {
			count++;
			q++;
		}
		else if (sum > m) p++;
		else if (sum < m) q++;
	}
	
	cout << count << endl;
	

	return 0;
}
```

