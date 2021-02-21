# Dictionary

딕셔너리는 리스트나 튜플처럼 순차적으로(sequential) 해당 요솟값을 구하지 않고 Key를 통해 Value를 얻는다. 

특정 값을 찾기 위해 사전의 내용을 순차적으로 모두 검색하는 것이 아니라 baseball이라는 단어가 있는 곳만 펼쳐 보는 것이다.

**구조**

```python
dic = {Key1:Value1, Key2:Value2, Key3:Value3, ...}
```

> - Key에는 변하지 않는 값을 사용하고, Value에는 변하는 값과 변하지 않는 값 모두 사용할 수 있다.
>
>   Value에는 리스트도 넣을 수 있다.
>
>   ```python
>   dic = { 'a': [1,2,3]}
>   ```
>
> - Key는 고유한 값이므로 중복되는 Key 값을 설정해 놓으면 하나를 제외한 나머지 것들이 모두 무시된다.
>
>   key는 중복되지 않게 사용하자.
>
> - key에는 리스트로 사용할 수 없지만 튜플은 가능하다.



- 활용

  ```python
  # key 추가하기
  dic = {1: 'a'}
  dic[2] = 'b'    # dic = {1: 'a', 2:'b'} 
  
  # 요소 삭제하기
  dle dic[1]   # dic = {2: 'b'}
  
  # 값 반환
  print(dic['2'])  # b 출력
  ```



- 관련 함수

  ```python
  # keys()
  dic = {'name': 'pey', 'phone': '0119993323', 'birth': '1118'}
  a = dic.keys()  # a == ['name', 'phone', 'birth']
  # Key 리스트 만들기
  # keys() 함수로 만들어진 a는 list객체가 아닌, dict_keys 객체임. 객체 종류가 다르기 때문에 리스트 고유의 append, insert, pop, remove, sort 함수는 수행할 수 없다.
  
  b = list(dic.keys())   # b의 객체는 list  
  
  # values()
  c = dic.values()      
  # Value만 얻을 수 있다.
  # c의 객체는 dict_values 임
  
  # items()
  d = dic.items()
  # items 함수는 Key와 Value의 쌍을 튜플로 묶은 값을 dict_items 객체로 돌려준다.
  
  # get()
  print (dic.get('name'))   # 'pey'출력
  # Key에 대응되는 Value를 반환한다.
  # dic[name] 과의 차이점: 
    #  dic[name]는 존재하지 않는 키(nokey)로 값을 가져오려고 할 경우 Key 오류를 발생시킨다.
    #  dic.get('nokey')는 false을 돌려준다. (오류 없음)
  
  # clear()
  dic.clear()
  # clear 함수는 딕셔너리 안의 모든 요소를 삭제한다. 
  ```

  

