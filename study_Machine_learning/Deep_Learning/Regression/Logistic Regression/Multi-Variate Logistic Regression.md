# Multi-Variate Logistic Regression

- Affine Function
  $$
  z = \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0
  $$

- Sigmoid Function
  $$
  \widehat{y} = \sigma(z) \\
  = \frac{1}{1 + e^{(\theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0))}}
  $$

- Binary Cross Entropy
  $$
  L = - [y log(\widehat{y}) + (1-y)log(1-\widehat{y})]
  $$
  

> - Linear Regression에서 feature scaling을 하는 이유: x값이 너무 크면 학습 과정에서 발산을 할 위험이 있다.
>
> - Logistic Regression에서 feature scaling을 하는 이유: x값이 너무 크면 학습에 별 도움이 안되는 data라서



### Sigmoid Function

- Decision Boundary
  $$
  D.B. => \ \ \ \ \ z = \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0 = 0
  $$
  각각의 theta가 target theta라면, 아래의 식이 만족함을 알 수 있다.
  $$
  \left\{\begin{matrix}
  y = 1, \ \ \ if \ \ \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0  > 0
  \\ 
  \\ 
  y = 0, \ \ \ if \ \ \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0  < 0
  \end{matrix}\right.
  $$
  또한 각각의 x에 대한 식이 D.B.가 될 수 있다는 것을 통해 D.B.가 Linear한 모양이 나온다는 것을 할 수 있다.
  $$
  x_m = -\frac{\theta_{m-1}}{\theta_{m}}x_{m-1} -\frac{\theta_{m-2}}{\theta_{m}}x_{m-2}-...-\frac{\theta_{1}}{\theta_{m}}x_{1} - \frac{\theta_0}{\theta_{m}}
  $$

  > 예)
  >
  > - target theta가 3개 있고, 각각이 (1, 1, 0)이라 할 때
  >   $$
  >   (\theta_{2}, \theta_{1}, \theta_{0}) = (1, 1, 0)
  >   \\x_2 = -x
  >   $$
  >
  > -  target theta가 3개 있고, 각각이 (2, 1, 0)이라 할 때
  >   $$
  >   (\theta_{2}, \theta_{1}, \theta_{0}) = (1, 1, 0)
  >   \\x_2 = -\frac{1}{2}x
  >   $$
  >
  > -  target theta가 3개 있고, 각각이 (1, 1, 1)이라 할 때
  >   $$
  >   (\theta_{2}, \theta_{1}, \theta_{0}) = (1, 1, 0)
  >   \\x_2 = -x - 1
  >   $$
  >
  > 이를 통해 theta_0는 D.B.의 평행이동에 관여를 한다는 것을 알 수 있다.

  즉, D.B. 는 target theta에 의해서 결정되며 그 모양은 data의 column이 고차원적이라 해도 그 차원에 맞는 Linear한 모양이 만들어진다는 것을 알 수 있다. 



### Propagation

![](https://github.com/HibernationNo1/TIL/blob/master/image/37.jpg?raw=true)

>Affine Function
>$$
>z = \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0
>\\ = \vec{\theta^T}\vec{x}
>$$
>
>$$
>(\frac{\part z}{\part \theta_{m}}, \frac{\part z}{\part \theta_{m-1}}, ..., \frac{\part z}{\part \theta_{1}}, \frac{\part z}{\part \theta_{0}}) = (x_{m}, x_{m-1},..., x_{1}, 1)
>$$

$$
weight : \ \ \ \ \ \ \frac{\part J}{\part \theta_m} =\frac{1}{n}* \frac{\widehat{y}-1}{\widehat{y}(1-\widehat{y})} * \widehat{y}(1-\widehat{y})*x_m \\
= -\frac{x_m}{n}* (y-\widehat{y}) \ \ \ \ \ ( m \geq 1)\\
bias: \ \ \ \ \ \ \frac{\part J}{\part \theta_0} = \frac{1}{n}*\frac{\widehat{y}-1}{\widehat{y}(1-\widehat{y})} * \widehat{y}(1-\widehat{y})*1 \\
= -\frac{1}{n}*(y - \widehat{y})
$$

$$
\theta_m := \theta_m - \alpha\frac{\part J}{\part \theta_m}  = \theta_m + \frac{\alpha}{n}x_m (y-\widehat{y}) \ \ \ \ \ ( m \geq 1)\\
\theta_0 := \theta_0 - \alpha\frac{\part J}{\part \theta_0}  = \theta_0 + \frac{\alpha}{n}(y-\widehat{y})
$$

