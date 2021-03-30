# cost function

## 개념

적절한 파라미터값을 알아내기 위해서는 현재 파라미터값이 우리가 풀고자 하는 목적에 적합한 값인지 측정이 가능해야 한다. 이를 위해 손실함수를 정의해야 한다.

> H(W, b) = Wx+b라는 식이 있을 때
>
> W =  2 이고 b = 1인, 즉 y = 2x+1인 함수를 컴퓨터에게 학습시키는 과정에서
>
> 임의로 전달된 W와 b가 정답과는 얼마나 다른지를 알려주는 함수를 **cost function(손실함수)** 라고 한다.

- Cost: Loss들의 평균 값



**Linear Regression에서**

Loss: 실제 y값과 prediction value와의 차이 Loss는 (y-y')에 제곱을 취해준다. Loss값은 양수여야 하기 때문이다.

loss값이 2차 함수이기 때문에 cost function는 2차함수와 같은 그래프가 형성되고, cost function이 가장 적으려면 함수의 기울기가 0이 되는 지점이여야 한다. (cost function이 크다는 것은 예측값과 정답값의 오차가 크다는 것이다.)
$$
Loss = (y^{(i)} - (wx^{(i)}+b))^2 \\ Cost = \frac{1}{n} \sum_{i=1}^{n}(y^{(i)} - (wx^{(i)}+b))^2
$$
위의 두 식은 weight가 1개, bias가 1개인 2차 식임을 알 수 있다.`y'`는 아래처럼 벡터로 표현될 수 있다.)
$$
Loss = (y^{(i)} - \overrightarrow{\theta^T}\overrightarrow{x}^{(i)})^2 \\ Cost = \frac{1}{n} \sum_{i=1}^{n}(y^{(i)} - \overrightarrow{\theta^T}\overrightarrow{x}^{(i)})^2
$$

$$
여기서\ \overrightarrow{\theta^T} = (\theta_0,\ \theta_1,\ \theta_2,\ \theta_3)이고\\
\theta_0 = b,\ \ (\theta_1,\ \theta_2,\ \theta_3) = \overrightarrow{w} 이라면\\ 
Loss와\ Cost는\ \theta_0,\ \theta_1,\ \theta_2,\ \theta_3에\ 대한\ 2차 함수이다.\\
즉,\ 4차원\ 공간에서\ 아래로\ 볼록한\ 모양의\ 함수라는\ 것을\ 알\ 수\ 있다.
$$

이 때 b != 0 인 함수를 affine function(아핀 함수)이라고 한다.



- 추가

  y'에 activation function과 affine function이 둘 다 포함된다면 이를 **Logistic Regression**(LOR)이라고 한다.

  affine function만 포함되어 있으면 **Linear Regression**이라고 한다. 

  > y'가 다변수이면 Multi-variate Linear Regression(MVLR) 이라고 하고
  >
  > y'가 변수값 하나에만 영향을 받으면 single-variate Linear Regression(SVLR) 이라 한다.

  y'의 변수가 하나이고, b = 0이면 single-variate Linear Regression Without Bias Term (SVLR Without Bias Term)이라고 한다.





>  cost function 4차 함수와 같이 기울기가 0인 지점이 2개 이상인 그래프를 그린다면, 기울기가 0인 지점을 지나서 다시 기울기가 0이며 함수값이 가장 적은 지점을 찾아야 한다.
>
> 아래 그래프는 전부 y>0 이라는 가정 하에 예를 든다,

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ5BZAzwyJ88eEujeYBzXGlrzH_saUt4mRb_w&usqp=CAU)



## 종류

### 1. MSE(평균제곱오차)

머신러닝 뿐만 아니라 영상처리 영역에서도 자주 사용되는 **추측값에 대한 정확성 측정 방법**이다. 

간단히 말하면 오차의 제곱에 대해 평균을 취한 것이다. 
$$
수식: \ Cost = \frac {1} {2n} \sum_{j=1}^{n}(\widehat{y_i} - y_i)^{2}
$$

$$
\widehat{y_i} : 모델의\ 예측\ 값, \ \  	y_i : 정답\ 값, \ \ \frac {1} {2n}: 평균 \ 을\ 의미함
$$



### 2. Cross-Entropy(크로스 엔트로피) 

크로스 엔트로피 손실 함수는 평균제곱오차(MSE)와 같이 모델의 예측값이 참값과 비슷하면 작은 값, 참값과 다르면 큰 값을 갖는 형태의 함수로 나타내 수 있다.
$$
수식: \ H_{y^{'}(y)} = -\sum_{i}y^{'}_ilog(y_i)
$$

$$
y^{'}: 참값, \ \ y: 모델의\ 예측\ 값
$$

일반적으로 분류 문제에 대해서는 MSE보다 크로스 엔트로피 함수를 사용하는 것이 학습이 더 잘 되는 것으로 알려져 있다. (대부분의 텐서플로 코드들에서 크로스 엔트로피 손실 함수를 사용한다.)

**코드 구현**

```python
@tf.function
def cross_entropy_loss(y_pred, y): #크로스 엔트로피 손실함수
    return tf.reduce_mean(-tf.reduce_sum(y * tf.math.log(y_pred), axis=[1]))
	# 크로스 엔트로피 식 구현
```

또는 

```python
@tf.function
def cross_entropy_loss(y_pred, y): #크로스 엔트로피 손실함수
    return tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits = logits, labels = y))
	# 크로스 엔트로피 식 구현
```

