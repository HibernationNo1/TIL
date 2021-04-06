# standardization

normal distribution에서 어떻게 standard normal distribution으로 만들어주는 과정을 standardization(표준화) 라고 한다.



### 표준화를 하는 이유

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

- Feature Scaling - standardiztion(표준화)
  $$
  x : data, \ \ \ \mu: mean, \ \ \ \sigma: standard\ deviation \\
  \\ x:= \frac{x - \mu}{\sigma}
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

