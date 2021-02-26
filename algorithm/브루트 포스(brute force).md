# 브루트 포스(brute force)

- brute: 무식한, force: 힘  무식한 힘으로 해석할 수 있다.

- 완전탐색 알고리즘이며 해가 존재할 것으로 예상되는 모든 영역을 전체 탐색하는 방법으로 가능한 모든 경우의 수를 모두 탐색하면서 요구조건에 충족되는 결과만을 가져온다.(모든 경우의 수를 다 대입해본다.)

- 이 알고리즘의 강력한 점은 예외 없이 100%의 확률로 정답만을 출력한다.

- 선형 구조를 전체적으로 탐색하는 **순차 탐색**, 비선형 구조를 전체적으로 탐색하는 **깊이 우선 탐색(DFS, Depth FirstSearch)**과 **너비 우선 탐색(BFS, breadth first search)**이 가장 기본적인 도구이다.

  > 그 외에대 여러 도구가 있음





**브루트 포스 문제해결방법**

1. 주어진 문제를 선형 구조로 구조화한다.
2. 구조화된 문제공간을 적절한 방법으로 해를 구성할 때까지 탐색한다.
3. 구성된 해를 정리한다.



## 1. 백트래킹

### 특징

- 조건 만족 문제를 풀기 위해 사용되는 알고리즘으로, 조건이 만족할 때 모든 조합의 수를 살펴보는 알고리즘이다.

- 한정 조건을 가진 문제를 해결할때 사용된다.

- **어떤 노드의 true여부를 점검 후, false이면 그 노드의 부모노드로 되돌아간 후 다른 자손노드를 검색한다.** 즉 false이면 배제를 하고 부모노드로 되돌아가면서 풀이 시간이 단축되는 것.

  ![](http://computing.or.kr/wp-content/uploads/2020/06/noname01-2.png)

- 깊이우선탐색(DFS)와 다른 점

  > DFS는 각 지점을 스택에 넣어가며 여러 지점을 한 단계씩 거치며 탐색. 이후 스택의 top에 저장된 위치로 돌아가며 탐색
  >
  > 백트래킹은 각 지점을 스택에 넣기 전에 ture판단을 한 후 false이면 배제하고, ture면 스택에 넣어가며 여러 지점을 한 단계씩 거치며 탐색. 이후 스택의 top에 저장된 위치로 돌아가며 탐색
  >
  > (여기서 말하는 스택은 FIFO의 스택이 아닌, 저장공간을 뜻함)



### 코드(백준15649)

- C++

```c++
#include<iostream>

using namespace std;

#define endl '\n'

int n, m;
int arr[8];
bool stc[8];

void Foo(int k) {
	if (k == m) {
		for (int i = 0; i < m; i++) {
			cout << arr[i] << " ";
		}
		cout << endl;
		return;
	}

	for (int i = 0; i < n; i++) {
		if (!stc[i]) {
			arr[k] = i + 1;
			stc[i] = true;
			Foo(k + 1);
			stc[i] = false;
		}
	}
	return;
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	
	cin >> n >> m;

	Foo(0);

	return 0;
}
```

- python

```python
import sys
input = sys.stdin.readline
print = sys.stdout.write

n, m = map(int, input().split())

res = [i for i in range(1, m+1)]
stc = [False for _ in range(n)]

def func(k):
	if k == m:
		for i in range(m):
			print(f"{res[i]} ")
		print('\n')
		return
	
	for i in range(n):
		if stc[i] == False:
			res[k] = i+1
			stc[i] = True
			func(k+1)
			stc[i] = False


func(0)
```



## 2. 순열

- 수학에서, 순열 또는 치환은 서로 다른 n개의 원소에서 r(≤n)개를 뽑아 한 줄로 세우는 경우의 수이며, nPr로 나타낸다. 순서가 부여된 임의의 집합을 다른 순서로 뒤섞는 연산이다.

- 브루트포스에서 순열은 **순서**와 관련된 경우, **선택**과 관련된 경우, 그**수가 고정**된 경우 사용된다.

  