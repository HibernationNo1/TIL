# Jacobian Matrices

- scala function: 우리가 일반적으로 표현하는 방향성이 없는 함수

$$
f(t) = t*sin(t) \ \ \ \ \ \ g(t) = cos(t) \ \ \ \ \ \ h(t) = t^2
$$



- vactor function: 각각의 원소가 scala function으로 구성되어 있는 방향성이 있는 함수 (다수의 scala function을 다루는 function)

$$
\overrightarrow{r} = (f(t), g(t), h(t))
$$

​		이미지 1



우리가 vector function에 대해서 미분을 하게 되면, 4가지의 경우의 수가 나올 수 있다.
$$
\begin{pmatrix}
x_1\\
x_2\\
\vdots \\
x_m
\end{pmatrix}  = \overrightarrow{x} \ 이고, \ 
\begin{pmatrix}
f_1\\
f_2\\
\vdots \\
f_m
\end{pmatrix} = \overrightarrow{f} \ 일 때\\ \frac{\partial f}{\partial x},\ \frac{\partial f}{\partial \overrightarrow{x}},\ \frac{\partial \overrightarrow{f}}{\partial x},\ \frac{\partial \overrightarrow{f}}{\partial \overrightarrow{x}}  \ \ 이렇게\ 4\ 가지의\ 경우의\ 수가\ 나올 \ 수\ 있다.
$$
이미지 2
$$
여기서 \ \frac{\partial \overrightarrow{f}}{\partial \overrightarrow{x}}\ 에\ 대한\ 식을\ jacobian\ matrices\ 라고\ 한다.
$$
이미지 3

즉, jacobian matrices란 다변수 벡터 함수의 도함수 행렬을 의미한다.

a라는 변수의 식을 가지고 있는 n * n 크기의 metrices와 b라는 변수의 식을 가지고 있는 n * n 크기의 metrices가 있을 때, a와 b가 서로 독립적인 변수라면 이 두 metrices에 사칙연산을 수행하면 element-wise binary operration이 이루어지게 된다.  사직 연산으로 만들어진 n * n 크기의 metrices에 미분을 적용해서 jacobian matrices가 만들어진다고 할 때, 어떤 연산을 했는지(+ - * /) 그리고 어떤 변수(a or b)에 대해서 미분을 했는지에 따라 그 값은 달라지지만, 형태는 단위행렬과 같이 대각선 값만 존재하고 나머지는 0의 값을 가진 '**대각행렬**'이 만들어진다.

> 이 때 +, - 연산으로 만들어진 matrices에 a에 대해서 미분을 수행하면 a변수의 계수가 되는 값만 남는 대각 jacobian matrices이 만들어진다. (b도 마찬가지)
>
> 하지만 * 또는 / 연산으로 만들어진 matrices에 a에 대해서 미분을 수행하면 b변수의 계수가 되는 값만 남는 대각 jacobian matrices이 만들어진다. (a도 마찬가지)

