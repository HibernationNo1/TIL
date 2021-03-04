# With as 

파이썬에서는 파일을 다루는 처리를 할때는 필수적으로 파일 오픈(open) 파일 닫기(close) 과정을 거치게 되고, 코드가 복잡해지면서 개발자는 파일을 열어놓고 닫지 않는 실수를 할 경우가 생길때도 있다. 

with ... as 구문을 사용하게 되면 파일을 열고 해당 구문이 끝나면 자동으로 닫히게 되어서 이러한 실수를 줄일 수 있다.

**문법**

`with open(파일 경로, 모드) as 파일 객체:`

```python
with open("sample.txt", "w") as file:
	file.write("It's simple code")
```



#### Tensorflow에서의 사용

 with를 통해 API를 열어 테이프 기록에 사용할 수 있다.

**예시**

```python
x = tf.ones((2, 2))

with tf.GradientTape() as t:
  t.watch(x)
  y = tf.reduce_sum(x)
  z = tf.multiply(y, y)
```

