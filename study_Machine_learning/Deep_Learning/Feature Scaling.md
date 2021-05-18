# Feature Scaling

서로 다른 feature 값들을 동일한 척도로 변환하는 것





## Normalization

convert a range of value from 0 to 1

> Min-Max Scaling이라고도 한다.

$$
X:= \frac{X - X_{min}}{X_{max} - X_{min}}
$$







---



## standardization

normal distribution에서 standard normal distribution으로 만들어주는 과정을 standardization(표준화) 라고 한다.

> standard normal distribution (Z Score normalization라고도 한다.) 
>
> mean = 0
>
> std = 1

$$
\\ X:= \frac{X - \mu}{\sigma}
$$



### why standardization?

가장 이상적인 cost function을 구하기 위한 조건 2가지

1. **0에 대칭적인 data set**

   data로 입력받은 x값의 평균이 0이면 가장 이상적인 cost function 모양이 나오지만, 그렇지 않다면 (x 평균이 절대값이 0이 아니면) x값에 [곱하기 (-1)]을 한 data를 받아옴으로써 평균을 0으로 맞출 수 있다. 이런 원리처럼, 우리는 data set을 준비할 때 0을 기준으로 대칭을 한 값으로 모아놓은 data set을 준비하는게 학습에 더욱 좋다. 이것이 바로 전처리 과정에서 data set의 평균을 0으로 하고 양-음 data의 대칭을 맞추는 이유이다.  

2. **양, 음의 평균 절대값이 1인 data set**

   위의 loss에서의 Gradient Descent Method에서는 x값에 의해 theta_1, theta_0의 학습 속도가 달라진다는 것을 알아보았으며, 두 theta값의 학습속도를 동일하게 하는 가장 이상적인 x값은 1이라는 것을 알 수 있었다. 

   cost function은 여러 x값의 평균을 사용하기 때문에, x의 양수값들의 평균과 음수값들의 평균이 각각 1, -1을 가지고 있어야 두 theta값의 학습속도를 동일하게 할 수 있다는 것을 알 수 있다. (이를 위해서 큰 값을 가진 x 하나에는 작은 값을 가진 수많은 x값이 함께 있어야 평균 1을 맞출 수 있음을 기억하자.  

   ex) [2, 0.1, 0.1, ...] 의 평균 = 1.00...01)

즉, 0에 대칭적이면서 양, 음수 data들의 평균에 절대값을 씌우면 1이 나오는 data set이 학습이 가장 이상적인 data set이라는 것을 알 수 있다.

이러한 data set이 바로 **standard normal distribution**(표준 정규분포)이다.

![](https://cdn.scribbr.com/wp-content/uploads/2020/10/standard-normal-distribution-1024x633.png)

그렇다면 normal distribution에서 어떻게 standard normal distribution으로 값을 바꿀 수 있을까?  

- Feature Scaling - standardization(표준화)
  $$
  X : data, \ \ \ \mu: mean, \ \ \ \sigma: standard\ deviation \\
  \\ x:= \frac{X - \mu}{\sigma}
  $$

  > mean: 평균
  >
  > variance: 분산 = (data의 평균 - data**2의 평균)
  >
  > std: 표준편차 = variance**(0.5)


standardization 을 통해 normal distribution의 mean과 std는 0, 1이 된다.





#### 코드 예시

```python
score = [10, 20, 30]
mean = sum(score)/len(score)


sum_of_score = 0
for i in score:
    sum_of_score +=i**2 
square_of_mean = mean**2
mean_of_square = sum_of_score/len(score)
variance = mean_of_square - square_of_mean
std = variance**0.5
print(f"mean: {mean}, std: {std} \n \n")

for i in range(len(score)):
    score[i] = (score[i]-mean)/std

mean = sum(score)/len(score)
sum_of_score = 0
for i in score:
    sum_of_score += i**2
mean_of_square = sum_of_score/len(score)
square_of_mean = mean**2
variance = mean_of_square - square_of_mean
std = variance**0.5
print(f"mean: {mean}, std: {std}")
    
```





# Weight Initialization

좋은 가중치 초기화 조건

1. 값이 동일해서는 안된다
2. 충분히 작아야 한다
3. 적당한 분산(또는 표준편차)를 가져야 한다.



이를 위해서 여러 가지의 Weight Initialization 방법이 있다.



> Batch Normalization을 하면 
>
> Xavier Glorot Initialization이나 He Initialization이나 큰 차이는 없다.



## Xavier Glorot Initialization

input node와 output node의 갯수를 감안하여 동적으로 weight Initialization 수행



### glorot_uniform

Uniform Distrubution(- 한도값, +한도값)
$$
한도값 = \sqrt{\frac{6}{fan\ in + fan \ out}}
$$
fan = num of node(units)

> fan_in : input leyer의 unit 개수
>
> fan_in : output leyer의 unit 개수

```python
fan_in = 10,
fan_out = 8

limit = np.sqrt(6/(fan_in+fan_out))
weights = np.random.uniform(-1*limit, limit = sacle_value, size=(100, 100))
```





### glorot_normal

Normal Distribution(mean = 0, std)
$$
std = \sqrt{\frac{2}{fan\ in + fan \ out}}
$$


```python
fan_in = 10,
fan_out = 8

scale_value= np.sqrt(2/(fan_in+fan_out))
weights = np.random.normal(loc = 0., sacle = sacle_value, size=(100, 100))
```





## He Initialization

Relu에 보다 최적화된 weight Initialization

> tf.keras.Conv2D의 weight initialization은 Xavier Glorot Initialization을 따른다.
>
>  activation function이 Relu인데 왜 He Initialization가 아니고?
>
> 그래서 Conv2D의 arg에서 설정 가능
>
> `kernel_initialization = 'he_normal'`
>
> ```python
> Conv2D(filter = 32, kernel_size = (3, 3), padding = 'same', activation = 'relu', kernel_initialization = 'he_normal')
> ```
>
> data에 따라서 result는 다르겠지만, Mnist 기준, 학습에 따른 정확도에는 큰 변화가 없다



### he_uniform

Uniform Distrubution(- 한도값, +한도값)
$$
한도값 = \sqrt{\frac{6}{fan\ in}}
$$


```python
fan_in = 10,

limit = np.sqrt(6/fan_in)
weights = np.random.uniform(-1*limit, limit = sacle_value, size=(100, 100))
```



### he_normal

Normal Distribution(mean = 0, std)
$$
std = \sqrt{\frac{2}{fan\ in }}
$$


```python
fan_in = 10,

scale_value= np.sqrt(2/fan_in)
weights = np.random.normal(loc = 0., sacle = sacle_value, size=(100, 100))
```





---



# Batch Normalization

why need batch normalization?

Arise 'internal Convariate Shift' issue when data passed through a filter. Batch Normalization need to prevent for this issue

> internal Convariate Shift 
>
> 각 layer를 통과 할 때마다 input 데이터의 분포가 조금씩 변하는 현상



![](https://blog.kakaocdn.net/dn/r5elS/btqBPXN1ib0/SKLvm2ZQj4pky6MyYOst3K/img.png)


$$
layer\ output \Rightarrow \   x \Rightarrow \  \widehat{x} = \frac{x-u}{\sigma} \Rightarrow \  y = \gamma\widehat{x} \\
\Rightarrow y = \gamma\widehat{x} + \beta \ \ \ \ \ (BN)\\ 
\gamma : Scaling\ 파라미터\\
\beta : \ shift\ 파라미터 
$$
layer를 통과한 data가 weight에 의해 한 쪽에 치우친 형태로 나오면 Batch Normalization 을 shift 파라미터로 사용해서 data 위치를 보정해준다.

> 동적으로 layer의 output을 조절할 수 있게 된다.



언제 적용할까?

Conv2D -> BN -> Activation Function

단, test data에는 적용하지 않는다.

> Scaling파라미터와 beta 파라미터는 학습시에 최종 결정된 값을 이용 







어떤 효과가 있나?

- performance improvements

- Regularization 

  > Normalization 후에 scaling, shift로 일종의 noise추가 효과

- Weight Initialization설정을 크게 신경 쓸 필요가 없다.



```python
from tensorflow.keras.layers import BatchNormalization
x = Conv2D(filter = 32, kernel_size = 3, padding = 'same')(input)
x = BatchNormalization()(x)
x = Activation('relu')(x)
```

