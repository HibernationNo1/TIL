# GradientTape

### GradientTape()

- 텐서플로는 자동 미분(주어진 입력 변수에 대한 연산의 편미분(gradient)를 계산하는 것)을 위한 **tf.GradientTape** API를 제공한다. 
- tf.GradientTape는 컨텍스트(context) 안에서 실행된 **모든 연산**을 테이프(tape)에 "기록" 후 후진 방식 자동 미분(reverse mode differentiation)을 사용해 테이프에 "기록된" 연산의 그래디언트를 계산한다.(**동적으로 Gradient 값들을 확인해 볼 수 있다**)



>  쉽게 생각하면, forward propagetion 과정을 기록해 둿다가, back propagetion을 진행할 때 사용하기 위한 class라고 이해햐면 된다.
>
> (forward propagation이 진행될 때 사용했던 value들이 back propagetion이 진행될때도 사용될 수 있기 때문에 기록해두는 것)



기본 문법

```python
with tf.GradientTape() as tape:
```



#### gradient()

gradient 함수는 인자로 가져온 값에 대한 편미분을 계산한다.

GradientTape()에 의한 스코프 안의 변수를 인자로 가져오기 때문에 `스코프 이름.gradient` 형태임 

- `tape.gradient(tmp1, tmp2)` : tmp1에 대한 tmp2 파라미터의 gradient(편미분)값 반환

  

ex)

```python
with tf.GradientTape() as tape:
    t3 = t1 * t2
    
gradients = tape.gradient(t3, [t1, t2])
```

> gradients에는 t3에 대한 t1과 t2의 gradient list가 저장된다.



단, gradients는 Variable에 대해서만 연산이 진행된다.

```python
t1 = tf.constant([1, 2, 3], dtype = tf.float32)
t2 = tf.Variable([10, 20, 30], dtype = tf.float32)

with tf.GradientTape() as tape:
    t3 = t1  * t2
    
gradients = tape.gradient(t3, [t1, t2])
print(gradients[0]) # None
print(gradients[1])
```

why? constant는 back propagation이 일어날 필요가 없기 때문에(data set이기 때문에 값 updata가 진행되지 않는다.)



ex) simple linear regression

```python
x_data = tf.random.normal(shape = (1000, ), dtype =tf.float32)
y_data  = 3*x_data + 1
# 3x + 1

w = tf.Variable(-1.)
b = tf.Variable(-1.)

learning_rata = 0.01

w_list, b_list = list(), list()
for x, y in zip(x_data, y_data):
    with tf.GradientTape() as tape:
        predictions = x*w + b
        loss = tf.pow((predictions - y), 2)

    gradients = tape.gradient(loss, [w, b])

    w_list.append(w.numpy())
    b_list.append(b.numpy())

    w = tf.Variable(w - learning_rata*gradients[0]) 
    b = tf.Variable(b - learning_rata*gradients[1])
    

fig, ax = plt.subplots(2, figsize = (10, 5))
ax[0].plot(w_list)
ax[0].set_xlabel('weight')
ax[1].plot(b_list )
ax[1].set_xlabel('bias')
fig.subplots_adjust(hspace=  0.3)
plt.show()
```





#### apply_gradients()

gradient 값을 통하여 theta 값을 얻어내기 위한 그래프를 생성하는 함수다.

최적화 도구에 쓰이기 때문에 `optimizer.apply_gradients` 형태로 사용되며 이를 통해 파라미터 갱신이 이루어지게 된다.
$$
\theta_{i+1} 를\ 구하는\ 과정이다
$$
**예시**

```python
optimizer.apply_gradients(zip(gradients, [w, b]))
```



