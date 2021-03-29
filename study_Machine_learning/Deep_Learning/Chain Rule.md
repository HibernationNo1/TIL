# Chain Rule

함수가 가진 변수가 또 다른 변수로 이루어진 함수인 것 처럼 각각의 함수가 트리 구조처럼 연결되어 있는 구조를 Chain이라고 이해한다면, Chain Rule은 아래와 같다.
$$
z(x, y) = x^2 - y^2  \ 일 때\\
x(s, t) = s-sin(t) \ 이고,\ y(s, t) = e^s + cos(t)\ 라면\\
z에\ 대한\ s,\ t의 편미분은 \ \ \frac {\partial z(x, y)}{\partial s} \ 와 \frac {\partial z(x, y)}{\partial t} 로\ 두개가\ 존재할\ 수 \ 있다.\\
이\ 개념이 Chain\ Rule이다.
$$
이러한 chain rule의 개념을 이용해서 z의 s와 t에 대한 편미분을 구하는 식은 4 가지가 나올 수 있다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/4.jpg?raw=true)

x(s, t)는 z(x, y)로부터 받은 미분값에 자신이 수행한 미분값을 곱하고 다시 s와 t로 보냄으로써 propagation 동작이 이루어지고 최종적으로는 z의 s와 t에 대한 편미분을 구할 수 있게 되는 것이다.
$$
z의\ s에\ 대한\ 편미분: \frac {\partial z(x, y)}{\partial s}= (\frac{\partial z(x, y)}{\partial x} *  \frac{\partial x(s, t)}{\partial s}) + (\frac{\partial z(x, y)}{\partial y} *  \frac{\partial y(s, t)}{\partial s})
\\ = 2x*(1) + (-2y)*(e^s)
$$

$$
z의\ t에\ 대한\ 편미분: \frac {\partial z(x, y)}{\partial t}= (\frac{\partial z(x, y)}{\partial x} *  \frac{\partial x(s, t)}{\partial t}) + (\frac{\partial z(x, y)}{\partial y} *  \frac{\partial y(s, t)}{\partial t})
\\ = 2x*(-cos(t)) + (-2y)*(-sin(t))
$$



## Vector Chain Rule

- Hadamard product(아다마르 곱): 같은 위치의 entry끼리 element by element 곱셈 연산을 수행한 것으로, 같은 크기의 두 행렬의 각 성분을 곱하는 연산이다. 기호는 `\bigcirc`를 사용한다. 

vector에 대한 Chain Rule의 식을 예시로 들어보자면
$$
\overrightarrow{s} = \begin{pmatrix}
s^{(1)}
\\ 
s^{(2)}
\\ 
\vdots
\\ 
s^{(n)}
\end{pmatrix}\ \ \ \ \ \ \ \ \ \ \ \ \ \ 
\overrightarrow{t} = \begin{pmatrix}
t^{(1)}
\\ 
t^{(2)}
\\ 
\vdots
\\ 
t^{(n)}
\end{pmatrix}\\ 
이고 \\
z(\overrightarrow{x}, \overrightarrow{y}) = \frac{1}{n}\sum_{i = 1}^{n}(x^{(i)}, y^{(i)}) \ \ \ // x,\ y의\ 평균 \\ 
\overrightarrow{x}(\overrightarrow{s}, \overrightarrow{t}) = \overrightarrow{s}\bigcirc\overrightarrow{t}\\
\overrightarrow{y}(\overrightarrow{s}, \overrightarrow{t}) = \overrightarrow{s} - \overrightarrow{t} \\
 \\

이면\\
$$

$$
\overrightarrow{x}(\overrightarrow{s}, \overrightarrow{t})  = \begin{pmatrix}
s^{(1)}*t^{(1)}\\ 
s^{(2)}*t^{(2)}\\ 
\vdots\\ 
s^{(n)}*t^{(n)}
\end{pmatrix}\ \ \ \ \ \ \ \ \ \ \ \ \ \ 
\overrightarrow{y}(\overrightarrow{s}, \overrightarrow{t})  = \begin{pmatrix}
s^{(1)} - t^{(1)}\\ 
s^{(2)} - t^{(2)}\\ 
\vdots\\ 
s^{(n)} - t^{(n)}
\end{pmatrix}\\ 이고
$$

![](https://github.com/HibernationNo1/TIL/blob/master/image/5.jpg?raw=true)

가 성립된다고 할 때, propagation 동작은 아래와 같다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/6.jpg?raw=true)

이러한 과정을 통해 실제 연산 식은 아래와 같이 나오게 된다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/7.jpg?raw=true)

![](https://github.com/HibernationNo1/TIL/blob/master/image/8.jpg?raw=true)

vector의 Chain Rule의 결과에서 z의 s(또는 t)에 대한 편미분 연산의 결과는 scala의 Chain Rule의 결과와는 달리 1*n의 shape을 가진 metric가 나옴을 확인할 수 있다.

이를 통해 
$$
\overrightarrow{f} =\begin{pmatrix}
f^{(1)}\\ f^{(2)}\\ \vdots\\ f^{(m)}
\end{pmatrix}\ \ \ \ \ \ \ \
\overrightarrow{g} =\begin{pmatrix}
g^{(1)}\\ g^{(2)}\\ \vdots\\ g^{(n)}
\end{pmatrix}\ \ \ \ \ \  -> \ \ \ \ \ \frac{\partial \overrightarrow{f}}{\partial \overrightarrow{g}}  의\ shape = (m, n)
$$

$$
\overrightarrow{g} =\begin{pmatrix}
g^{(1)}\\ g^{(2)}\\ \vdots\\ g^{(n)}
\end{pmatrix}\ \ \ \ \ \ \ \
\overrightarrow{h} =\begin{pmatrix}
h^{(1)}\\ h^{(2)}\\ \vdots\\ h^{(o)}
\end{pmatrix}\ \ \ \ \ \  -> \ \ \ \ \ \frac{\partial \overrightarrow{g}}{\partial \overrightarrow{h}}  의\ shape = (n, o)
$$

$$
\overrightarrow{h} =\begin{pmatrix}
h^{(1)}\\ h^{(2)}\\ \vdots\\ h^{(o)}
\end{pmatrix}\ \ \ \ \ \ \ \
\overrightarrow{i} =\begin{pmatrix}
i^{(1)}\\ i^{(2)}\\ \vdots\\ i^{(p)}
\end{pmatrix}\ \ \ \ \ \  -> \ \ \ \ \ \frac{\partial \overrightarrow{h}}{\partial \overrightarrow{i}}  의\ shape = (o, p)
$$

$$
최종적으로, Chain\ Rule의\ shape\ calculation에\ 의해\\
\frac{\partial \overrightarrow{f}}{\partial \overrightarrow{i}}  의\ shape = (m, p)\ 이\ 성립된다.
$$

