# Counter

데이터의 개수를 셀 때 유용한 파이썬의 `collections` 모듈의 `Counter` 클래스

list 또는 문자를 매개로 사용하며 list개체로 반환한다.

Counter 클래스는 Dictionary 의 subclass이기 때문에  Dictionary 에 있는 모든 메소드가 사용가능하며 추가로 Counter 클래스가 제공하는 메소드도 사용가능.

**예시**

```python
from collections import Counter

arr = [1, 1, 2, 3, 4, 2, 1]
cnt = Counter(arr)
#cnt = {1: 3, 2: 2, 3: 1, 4:1}
alphabet = Counter('hello world') 
#alphabet = {'h': 1, 'e': 1, 'l': 3, 'o': 2, ' ': 1 'w': 1, 'r': 1, 'd':1}
```



- 활용

  dictionary처럼 사용할 수 있다.

```python
#위 코드와 이어서...

print (cnt[1])  # 3 출력
print (cnt[2])  # 2 출력
print (alphabet['h'])  # 1출력
```





- 메서드

  ```python
  most_common()
  Counter('hello world').most_common()
  # [('l', 3), ('o', 2), ('h', 1), ('e', 1), (' ', 1), ('w', 1), ('r', 1), ('d', 1)]
  ```

  > 데이터의 개수가 많은 순으로 정렬된 사전을 리턴하는 `most_common`이라는 메서드를 제공
  >
  > 반환타입은 dictionary . (정확하게는 Counter class. 엄연히 다른 class type 이지만 위의 이유로
  >
  > dictionary와 같이 동작.)