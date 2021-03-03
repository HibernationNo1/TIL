# Tensors

## 1. 기초 개념

텐서는 일관된 유형을 가진 다차원 배열이다. (매우 수학적인 개념으로 데이터의 배열이라고 볼 수 있음)

하나의 벡터로 이해해야 한다.

모든 텐서는 Python 숫자 및 문자열과 같이 변경할 수 없다. 텐서의 내용을 업데이트할 수 없으며 새로운 텐서를 만들 수만 있다.

텐서를 이야기할 때에는 Rank, Shapes, Type 등을 알아야 한다.

### 1. Rank

텐서의 Rank는 간단히 말해서 몇 차원 배열인가를 의미한다.

| **RANK** | **TYPE**     | **EXAMPLE**                                     |
| -------- | ------------ | ----------------------------------------------- |
| **0**    | **scalar**   | **[1]**                                         |
| **1**    | **vector**   | **[1,1]**                                       |
| **2**    | **matrix**   | **[[1,1],[1,1]]**                               |
| **3**    | **3-tensor** | **[[[1,1],[1,1]],[[1,1],[1,1]],[[1,2],[2,1]]]** |
| **n**    | **n-tensor** |                                                 |

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FqS1NF%2FbtqubStze09%2F5sbnC8DVd3aQsUULgjv6Kk%2Fimg.png)

- 0차 텐서: 벡터가 없기 때문에 스칼라임
- 1차 텐서: 벡터가 하나 있기 때문에 벡터임
- 2차 텐서: 벡터가 두 개 일렬로 있기 때문에 행렬이나 다이애드임
- 3차 텐서: 벡터가 세 개 일렬로 있기 때문에 트라이애드임
- ...

### 2. Shape

텐서의 Shape은 각 축이 몇 개의 엘리먼트(Element)들로 구성되었는지 나타내는 값이다. 

Rank가 1인 텐서를 생각해보면 1차원 배열인 벡터(Vector)다. 차원과 함께 중요한 것이 몇 개의 원소들로 이루어져 있는지 여부다. Shape이 [3]이라면 엘리먼트(Element)가 3개인 벡터임을 나타낸다. Shape이 [2, 3]이면 Rank가 2인 텐서, 즉 행렬을 의미하며 2 * 3 행렬을 의미한다. 

> Shape이 [2, 6, 3]이면 Rank가 3인 텐서이며 x = 2, y = 6, z = 3의 크기를 가진 3차원 행렬이라고 생각하면 된다.



### 3. Type

텐서가 담을 수 있는 데이터의 타입을 의미한다. 

tf.float32, tf.int32 등이 표현하는 바는 텐서가 실수를 담을 수 있는지 정수를 담을 수 있는지 여부다. 대부분은 32로 끝나는 타입을 많이 사용한다.



---

## 2. 코드에 적용하기

### 1. 클래스

tensors에는 두 개의 클래스가 있다.

1. **constant tensors** : 변화가 불가능한 값

   > 클랙스: EagerTensor 
   >
   > input, 이미지와 같은 data set 은 EagerTensor로 사용한다.

2. **Variable tensors** : 변화가 가능한 값

   > 클랙스: ResourceVariable
   >
   > 업데이트가 필요한 파라미터는 ResourceVariable로 사용한다.

**예시**

```python
import tensorflow as tf
foo = [1, 2, 3]

t1 = tf.constant(foo)  
# t1은 EagerTensor 클랙스의 list [1, 2, 3] 이 된다 
print(t1) # tf.Tensor([1 2 3], shape=(3,), dtype=int32 출력
print(type(t1))


t2 = tf.Variable(foo)
# t2은 ResourceVariable 클랙스의 list [1, 2, 3] 이 된다 
print(t2)
print(type(t2))

t3 = tf.constant(t2)
# t2는 변화가 가능한 ResourceVariable 클랙스이기 때문에 EagerTensor 클랙스로 변환이 가능하다.
# t3은 EagerTensor 클랙스의 list [1, 2, 3] 이 된다 
print(t3)
print(type(t3))

#=============================덧셈 연산
t3 = t1 + t2  #EagerTensor + ResourceVariable
print(t3) # [1,2,3,1,2,3] 이 아닌, [2, 4, 6]이 출력된다.
print(type(t3))  #EagerTensor + ResourceVariable = EagerTensor 클랙스
```

> tensor끼리의 연산은 각 원소끼리의 연산이 적용된다.





+ 추가

  constant 대신 convert_to_tensor를 사용하는사람도 많다.

  ```python
  import tensorflow as tf
  foo = [1, 2, 3]
  t1 = tf.convert_to_tensor(foo)
  print(type(t1))  #EagerTensor 클랙스
  ```

  > constant와 convert_to_tensor의 output은 동일하다



### 2. Tensor 만들기

- **ones()** : 모든 원소가 1

  ```python
  t1 = tf.ones(shape=(100, ))
  # 1의 원소를 100개 가진 Rank 1 형태의 배열
  
  t2 = tf.ones(shape=(100,3))
  # 1의 원소를 3개 가진 배열이 100개 있는 Rank 2 형태의 배열(2차원)
  
  t3 = tf.ones(shape=(100,100, 3))
  # 1의 원소를 3개 가진 배열이 100개 있는 행렬이 100개 있는 Rank 3 형태의 배열(3차원)
  
  foo = [[1,2,3], [4,5,6]]
  t4 = tf.Variable(foo)	# shape = (2, 3) 형태의 텐서
  
  tmp = tf.ones(shape = (1, 4))
  # 4행 1열 형태의 2차원 텐서 
  tmp = tf.ones(shape = (4, 1))
  # 1행 4열 형태의 2차원 텐서 
  ```

  - 원소에 스칼라 적용하여 값 할당하기

    ```python
    t1 = 5*tf.ones(shape = (128, 103, 10))
    # 여기서 5는 스칼라, tf.ones(shape = (128, 128, 10))는 벡터이므로
    # 스칼라 * 벡터 = 각 요소마다 스칼라를 곱해주기 때문에
    # 5의 원소를 10개 가진 배열이 103개 있는 행렬이 128개 있는 Rank 3 형태의 배열(3차원)
    ```

  - ones_like()

    원소가 1인, 매개변수로 받은 텐서와 같은 형태의 텐서를 만든다.

    ```python
    t1 = 3*tf.ones(shape=(100,100, 3))
    # 3의 원소를 3개 가진 배열이 100개 있는 행렬이 100개 있는 Rank 3 형태의 배열(3차원)
    
    t2 = tf.ones_like(t1)
    # 1의 원소를 3개 가진 배열이 100개 있는 행렬이 100개 있는 Rank 3 형태의 배열(3차원)
    ```

- **zeros()** : 모든 원소가 0

  > 보통은 텐서에 0을 곱해서 모든 원소가 0인 텐서를 만든다.
  >
  > zeros_like() 도 지원한다.

- **random.normal()** : 정규분포로부터 추출한 무작위의 실수값을 할당

  ```python
  t1 = tf.random.normal(shape = (10, 10))
  # 각 원소에 무작위의 값을 할당한 텐서
  ```

  - random.set_seed(0) : 무작위 값이 고정 후 반복적으로 할당

    ```python
    tf.random.set_seed(0) 
    t1 = tf.random.normal(shape = (3, 3)) 
    # 이후 계속 t = tf.random.normal(shape = (3, 3)) 을 선언해도 각 원소는 고정된 값이 할당된다.
    ```

    > 랜텀 이펙트를 준 후 같은 결과를 내보내고 싶을 때 사용

  - mean(평균)과 stddev(표준편차) 적용

    ```python
    t1 = tf.random.normal(mean = 3, stddev = 1, shape = (10, 10))
    #평균이 3이고 표준편차가 1인 Rank 2 텐서 생성
    ```


- **random.uniform()** :  균등분포로부터 추출한 무작위의 실수값을 할당 (디폴트 = 0부터 1까지)

  ```python
  t1 = tf.random.uniform(shape = (3, 3, 3))
  ```

  - minval(최소값), maxval(최대값) 적용

    ```python
    t1 = tf.random.uniform(shape = (10, 10, 10), minval = -10, maxval = 10)
    #최소값이 -10이고 최대값이 10인 Rank 3 균등분포 텐서 생성
    ```





### 3. Tensor에서 정보 추출

- **shape** : shape을 반환

  ```python
  t1 = tf.random.uniform(shape = (10, 10, 10), minval = -10, maxval = 10)
  
  print(t1.shape)  # (10, 10, 10) 출력
  ```

- **dtype** : 데이터 타입을 반환

  ```python
  print(t1.dtype) # <dtype: 'float32'> 출력
  ```

  > tensorflow 는 dtype: 'float32' 를 데이터로 사용하기를 원함
  
  ```python
  t1 = ft.constant(foo, dtype = tf.float32)
  # 이런 식으로 데이터 타입을 치환할 수 있다.
  ```
  
  

### 4. 형 변환

- **cast()**: 형 변환

  ```python
  t1 = tf.random.normal(shape = (3, 4), mean = 3, stddev = 1)
  t2 = tf.random.normal(shape = (3, 4), mean = 3, stddev = 1)
  
  t1 = tf.cast(t1, dtype = tf.int16)  # 실수를 정수로 변환
  t2 = tf.cast(t2, dtype = tf.int16)
  print(t1+t2) # 정수에 대한 결과가 나옴
  ```

  

### 5. Tensor 연산

**기본적으로 Tensor의 연산은 각 원소끼리 적용되는 동작을 수행한다.**

```python
import tensorflow as tf

t1 = tf.constant([1, 2, 3])
t2 = tf.constant([11, 22, 33])
# 연산이 적용될 원소가 없으면 오류  //  t2 = tf.constant([22, 33]) 와 같이

print(t1+t2) # tf.Tensor([12 24 36], shape=(3,), dtype=int32) 출력
print(t1-t2) # tf.Tensor([-10 -20 -30], shape=(3,), dtype=int32)
print(t1*t2) # tf.Tensor([11 44 99], shape=(3,), dtype=int32)
print(t1/t2) # tf.Tensor([0.09090909 0.09090909 0.09090909], shape=(3,), dtype=float64)
print(t1%t2) # tf.Tensor([1 2 3], shape=(3,), dtype=int32)
print(t1//t2)# tf.Tensor([0 0 0], shape=(3,), dtype=int32)
```



- broadcasting 적용

```python
t1 = 2*tf.ones(shape = (1, 4)) 
# 4행 1열 형태의 2차원 텐서 
t2 = 5*tf.ones(shape = (3, 1))
# 1행 3열 형태의 2차원 텐서
t3 = t1 + t2
# 2차원이기 때문에 

# 			  5		2 2 2 2	  5 5 5 5	  7 7 7 7
# 2 2 2 2  +  5  => 2 2 2 2 + 5 5 5 5  == 7 7 7 7   의 계산결과가 된다
# 			  5		2 2 2 2   5 5 5 5	  7 7 7 7
# 
```



