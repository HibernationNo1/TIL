# Single-Variate Logistic Regression

Affine Function	->		Sigmoid Function	->	Binary Cross Entropy Loss
$$
Affine\ Function \ \ \ \ \ \ \ \ z = \theta_1 x + \theta_0 \\
Sigmoid\ Function\ \ \ \ \ \ \ \ \widehat{y} = \frac{1}{1+e^{-z}}\\
Binary\ Cross\ Entropy\ Loss\ \ \ \ \ \ \ \ L =-[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]
$$

$$
data\ set \ \ \ \ \ \  (x^{(i)}, y^{(i)}) = (x, y) \ \ 단, \ y는\ 0\ or\ 1
$$





### Sigmoid Function

- Sigmoid Function의 shape

$$
\sigma({y}) = \frac{1}{1+e^{-(\theta_1 x + \theta_0)}} = \frac{1}{1+e^{-\theta_1(x- (- \frac{\theta_0}{\theta_1})})}
$$

1. **weight의 변화량에 따른 Sigmoid Function 모양의 변화**

   weight의 절대값이 커질수록 Sigmoid Function의 S모양이 더욱 Sharply 된다.

   즉, Model이 이상적인 classifier가 되기 위해서는 weight가 무한대로 발산해야 한다. (updata가 계에에에속해서 일어난다.)

2. **Bias의 변화량에 따른 Sigmoid Function 모양의 변화**

   Bias가 +(또는 -)방향으로 커지면 Sigmoid Function의 Decision Boundary가 +(또는 -)방향으로 이동한다.

   ![](https://github.com/HibernationNo1/TIL/blob/master/image/45.jpg?raw=true)

   하지만 Decision Boundary값을 결정하는 것은 -(bias/weight)이기 때문에 weight와 bias가 변한다 하더라도 둘의 ratio(비율)이 동일하게 유지된다면 Decision Boundary는 제 자리에 유지된다. 그렇기 때문에 weight가 무한대로 발산하며 끊임없이 updata된다면 bias도 Decision Boundary를 유지시키기 위해 끊임없이 updata가 일어난다. 

   그리고 Decision Boundary가 음수일때는  weight의 updata 방향과 bias의 updata 방향은 서로 같은 방향으로 (둘 다 +Infinity 또는 -Infinity),

   Decision Boundary가 양수일때는  weight의 updata 방향과 bias의 updata 방향은 서로 다른 방향으로 (weight가 +Infinity면 bias는 -Infinity) 업데이트 되게 된다.

   ![](https://github.com/HibernationNo1/TIL/blob/master/image/46.jpg?raw=true)



- Linear Regrassion과의 차이점

  Linear Regrassion의 weight와 bias는 각각 label에 맞게 학습하기 위해서 label의 weight와 bias를 찾아간다.

  하지만 Losistic Regrassion의 weight는 label에 맞게 학습하기 위해서 Infinity로 발산하게 되고, bias는 Decision Boundary에 맞게 학습하기 위해서 + 또는 - 방향으로 Infinity하게 발산한다는 것이다.

​	





1. 각각의 Partial Derivative를 구해보자.

$$
\frac{\part z}{\part \theta_1} = x , \ \ \ \ \ \frac{\part z}{\part \theta_0} = 1\\ 
\frac{\part \widehat{y}}{\part z} = \widehat{y}(1-\widehat{y})\\
\frac{\part L}{\part \widehat{y}} = \frac{1-\widehat{y}}{\widehat{y}(1-\widehat{y})}
$$

2. Back Propagation을 진행해서 GDM을 구해보자.

$$
\frac{\part L}{\part \theta_1}  = \frac{\part L }{\part \widehat{y}} \frac{\part \widehat{y}}{\part z} \frac{\part z}{\part \theta_1} = x(\widehat{y} - y) \\
\frac{\part L}{\part \theta_0}  = \frac{\part L }{\part \widehat{y}} \frac{\part \widehat{y}}{\part z} \frac{\part z}{\part \theta_0}  = \widehat{y} - y\\
$$

$$
\theta_1 := \theta_1 + \alpha x_ (y - \widehat{y})\\
\theta_0 :=\theta_{0}+ \alpha (y - \widehat{y})\\
$$

