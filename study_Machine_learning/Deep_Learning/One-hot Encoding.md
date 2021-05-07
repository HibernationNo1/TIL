# One-hot Encoding

One-hot Encoding은 범주형 값을 이진화된 값으로 바꿔서 표현하는 것을 의미한다.  이를 범주형 데이터의 '표준화' 라고도 한다.

> ex)
>
> - interger Encoding(범주형 값)
>
>   개, 고양이, 말 이라는 3개의 데이터가 있을 때 이를 ['개' = 1, '고양이' = 2, '말' = 3 ] 이라고 단순하게 interger Encoding으로 변환하여 표현하는 것.
>
>   > 이러한 Encoding의 문제점은 머신러닝 알고리즘이 정수 값으로부터 잘못된 경향성을 학습하게 될 수도 있다. ['개' 와 '말' 의 평균은 '고양이' 이다.] 라는 잘못된 학습이 이루어질 수 있기 때문이다.
>
> - One-hot Encoding
>
>   범주형 데이터를 '개' = [1 0 0], '고양이' = [0 1 0], '말' = [0 0 1] 형태로 해당 레이블을 나타내는 인덱스만 1의 값을 가지고 나머지 부분은 0의 값을 가진 Binary Value로 표현한 것



- Label data

$$
(\overrightarrow{y}^{(1)})^T = (1 \ 0 \ .. 0), \ \alpha = 1 \\
(\overrightarrow{y}^{(2)})^T = (0 \ 1 \ .. 0), \ \alpha = 2 \\
\vdots\\
(\overrightarrow{y}^{(K)})^T = (0 \ 0 \ .. 1), \ \alpha = K \\
$$

​	이 처럼 각각의 class를 0과 1만을 표현해서 분류한다.



**code implementation**

```python
Y = tf.one_hot(Y_vec, depth = , dtype = tf.int32)
```

> `Y_vec` : must be a vector. not matrix.
>
> `depth` : number of class