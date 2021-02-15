# 깊이우선 탐색(DFS, Depth-First Search)

루트 노드(혹은 다른 임의의 노드)에서 시작해서 다음 분기(branch)로 넘어가기 전에 해당 분기를 완벽하게 탐색하는 방법

- 미로를 탐색할 때 한 방향으로 갈 수 있을 때까지 계속 가다가 더 이상 갈 수 없게 되면 다시 가장 가까운 갈림길로 돌아와서 이곳으로부터 다른 방향으로 다시 탐색을 진행하는 방법과 유사하다.

  ![](https://media.vlpt.us/images/sukong/post/b9042f15-fb5b-4272-abe7-8cdeb3f0f22f/DFS.png)

- 즉, 넓게(wide) 탐색하기 전에 깊게(deep) 탐색하는 것이다.

- 깊이 우선 탐색(DFS)이 너비 우선 탐색(BFS)보다 좀 더 간단하다.

- 단순 검색 속도 자체는 너비 우선 탐색(BFS)에 비해서 느리다.

- 자기 자신을 호출하는 순환 알고리즘의 형태 를 가지고 있다.

- 이 알고리즘을 구현할 때 , **그래프 탐색의 경우** 어떤 노드를 방문했었는지 여부를 **반드시 검사** 해야 한다는 것이다.

  > 이를 검사하지 않을 경우 무한루프에 빠질 위험이 있다.



### 사용하는 경우

- 모든 노드를 방문 하고자 하는 경우에 이 방법을 선택한다.

#### 1. 트리에 적용(트리 순회)

트리순회(tree traversal)란 트리의 각 노드를 체계적인 방법으로 방문하는 과정을 말한다.

하나도 빠뜨리지 않고, 정확히 한번만 중복없이 방문하는 것 

노드를 방문하는 순서에 따라 전위순회(preorder), 중위순회(inorder), 후위순회(postorder) 세 가지로 나뉜다.

![](https://i.imgur.com/zfrXerB.png)

##### 1. 전위순회(preorder)

루트 노드에서 시작해서 노드-왼쪽 서브트리-오른쪽 서브트리 순으로 순회하는 방식.

깊이우선순회(depth-first traversal)라고도 함

위 예시 트리에 전위순회 방식을 적용

> 1, 2, 4, 5, 3
>
> 가장 상단 노드에서 내려간다.

##### 2. 중위순회(inorder)

왼쪽 잎새노드부터 시작해서 왼쪽 서브트리-노드-오른쪽 서브트리 순으로 순회하는 방식.

대칭순회(symmetric traversal)라고도 함.

위 예시 트리를 중위순회 방식을 적용

> 4, 2, 5, 1, 3
>
> 가장 하단 노드부터 올라간다.

##### 3. 후위순회(postorder) 

왼쪽 잎새노드부터 왼쪽 서브트리-오른쪽 서브트리-노드 순으로 순회하는 방식. ([병합정렬](https://github.com/HibernationNo1/TIL/blob/master/algorithm/%EC%A0%95%EB%A0%AC.md)에서 사용)   

위 예시 트리를 후위순회 방식을 적용 

> 4, 5, 2, 3, 1
>
> 가장 높은 레벨의 노드부터 시작한다.

##### 코드 예시

![](https://t1.daumcdn.net/cfile/tistory/251FE74B5100D04F2F?download)

```c++
#include<iostream>

using namespace std;

#define endl '\n'

void Binary(int x) //트리 구현
{
	if (x > 15) return;
	else {
        // cout << x <<" ";  여기에서 호출하면 전위순회
		Binary(x * 2);   
        // cout << x <<" ";  여기에서 호출하면 중위순회
		Binary(x * 2 + 1);
     	// cout << x <<" ";	 여기에서 호출하면 후위순회
	}
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	Binary(1);

	return 0;
}
```

