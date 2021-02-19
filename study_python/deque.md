# deque

deque에 관한 자세한 내용은 [선형 자료구조](https://github.com/HibernationNo1/TIL/blob/master/Data_structure/%EC%84%A0%ED%98%95%20%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0.md) 여기서



python에서 `collections.deque`는 `list`와 비슷하다. `list`의 `append(), pop()`등의 메소드를 `deque`에서도 제공한다.

### 선언 및 관련 함수

```python
import collections  #collections 모듈 추가

foo = collections.deque(['a', 'b'])  # 각각의 원소가 a, b 순으로 두 개 저장된 deque 생성
bar = collections.deque() #원소가 0개인 deque 생성 

#관련 함수
bar.append(1) 	 #list의 append와 동일
bar.appendleft(1)  #duque의 첫 번째 원소를 뒤로 밀어내고 새 원소 추가

bar.pop()	 #list의 pop과 동일
bar.popleft()  # duque의 첫 번째 원소를 pop

bar.ratate(4)  #4의 숫자만큼 오른 방향으로 모든 원소를 회전. 마지막 원소가 회전되면 첫 번째 원소로 온다. 음수를 넣으면 왼쪽으로 회전 

#추가 내용
bar[3] #과 같이 인덱스로 접근이 가능하다.
len(bar) #len함수 적용 가능
```

