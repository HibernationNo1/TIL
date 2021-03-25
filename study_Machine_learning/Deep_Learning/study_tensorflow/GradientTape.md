# GradientTape

### 1. GradientTape()

- 텐서플로는 자동 미분(주어진 입력 변수에 대한 연산의 편미분(gradient)를 계산하는 것)을 위한 **tf.GradientTape** API를 제공한다. 

- tf.GradientTape는 컨텍스트(context) 안에서 실행된 **모든 연산**을 테이프(tape)에 "기록" 후 후진 방식 자동 미분(reverse mode differentiation)을 사용해 테이프에 "기록된" 연산의 그래디언트를 계산한다.(**동적으로 Gradient 값들을 확인해 볼 수 있다**)

**문법** (with as 키워드 사용)

```python
@tf.function
def train_step(images, labels):
    # 미분을 위한 GradientTape을 적용
    with tf.GradientTape() as tape:
        # 1. 예측 (prediction)
        predictions = model(images)
        # 2. Loss 계산
        loss = loss_function(labels, predictions)
    
    # 3. 그라디언트(gradients) 계산
    gradients = tape.gradient(loss, model.trainable_variables)
    
    # 4. 오차역전파(Backpropagation) - weight 업데이트
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))
    
    # loss와 accuracy를 업데이트
    train_loss(loss)
    train_acc(labels, predictions)
```



또한 tf.GradientTape 컨텍스트 안에서 계산된 중간값에 대한 그래디언트도 구할 수 있다.





### 2. gradient()

gradient 함수는 인자로 가져온 값에 대한 편미분을 계산한다.

GradientTape()에 의한 스코프 안의 변수를 인자로 가져오기 때문에 `스코프 이름.gradient` 형태임 

- `tape.gradient(tmp1, tmp2)` : #tmp1에 대한 tmp2 파라미터의 gradient(편미분)값 반환

  >`tmp1` 은 GradientTape()에 의한 스코프 안의 손실함수의 결과값 인자로 가져온다.
  >
  >`tmp2` 는 가설정의에 쓰인 파라미터를 인자로 가져온다.

**예시**

```python
with tf.GradientTape() as tape:
    y_pred = linear_model(x)   #가설함수
    loss = mse_loss(y_pred, y) #손실함수
gradients = tape.gradient(loss, [w, b] ) #w, b가 가설함수의 파라미터값이라고 가정 
```





### 3. apply_gradients()

gradient 값을 통하여 theta 값을 얻어내기 위한 그래프를 생성하는 함수다.

최적화 도구에 쓰이기 때문에 `optimizer.apply_gradients` 형태로 사용되며 이를 통해 파라미터 갱신이 이루어지게 된다.
$$
\theta_{i+1} 를\ 구하는\ 과정이다
$$
**예시**

```python
optimizer.apply_gradients(zip(gradients, [w, b]))
```



