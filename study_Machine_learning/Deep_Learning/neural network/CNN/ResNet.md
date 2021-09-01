# ResNet

ResNet은 skip connection을 이용한 residual learning을 통해 layer가 깊어짐에 따른 gradient vanishing 문제를 해결한 model이다.

기존의 neural net의 학습 목적은 input(x)을 타겟값(y)으로 mapping하는 함수 H(x)를 찾는 것이였기 때문에 H(x)-y를 최소화하는 방향으로 학습을 진행했다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbTY9tT%2FbtqBQ2AY09e%2FiyaK8IV4AWzjYvAvKK7nok%2Fimg.png)

> 예시 :: 
>
> x가 2개의 layer를 통과하고 나온 output은 H(x)이며, 이 H(x)가 y가 되도록 학습하는 것이 기존 network의 목적이다.

이 때 H(x)는 또 다른 layer의 input이 되고, 해당 layer의 입장에서는 H(x)는 x에 대한 정보가 보존되지 않은 새롭게 생성된 정보이기 때문에 layer가 많아질수록 weight들의 분포가 균등하지 않게 된다.

또한 H(x)의 x에 대한 미분값인 H'(x)가 1보다 작을 경우 layer가 많아질수록 gradient vanishing문제가 발생하게 된다.

이를 해결하기 위해 shortcut connection방법을 추가한 것이 ResNet이다.

shortcut connection은 x값을 여러 layer를 통과한 output에 더해주는 방법이다.

이 때 여러 layer를 통과한 output이 F(x)라고 할 때 H(x) = F(x) + x가 되고, 

H(x)는 기존에 학습한 정보(x)와 추가적으로 학습한 정보(H(x))를 모두 가지게 되어 weight들의 분포가 균등하게 유지되는 것이 가능하게 된다.

또한 H(x)의 x에 대한 미분값인 H'(x)가 F'(x) + 1이 되어 최소한 1이상의 기울기를 전달하기 때문에 gradient vanishing문제또한 해결하게 된다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fu7iAK%2FbtqBNkDoj6y%2F2Mxa3oVsS7SfoOzNZEZGU1%2Fimg.png)

> F(x)는 H(x)-x로 표현할 수 있으며 이를 잔차(Residual)라고 하고, F(x)가 최소가 되도록 학습이 되는 것을 Residual Learning이라고 한다.



#### identity block

Conv+Batch_Norm+ReLU → Conv+Batch_Norm+ReLU → Conv+Batch_Norm + shortcut connection → ReLU

을 수행하는 block을 identity block이라고 한다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fcrj5v9%2FbtqBOrWkyBD%2Fyxk3PchJlnl25RRXYJ1vg0%2Fimg.png)



```python
from tensorflow.keras.layers import Conv2D, BatchNormalization, Activation, Add

# filters = [nb_filter1, nb_filter2, nb_filter3]
def identity_block(input_tensor, filters):
                                                  
    nb_filter1, nb_filter2, nb_filter3 = filters
                                                  
    x = Conv2D(filters = nb_filter1, kernel_size = 1)(input_tensor)
    x = BatchNormalization(axis=-1, momentum=0.99, epsilon=0.001)(x, training=True)
    x = Activation('relu')(X)
    
    x = Conv2D(filters = nb_filter2, kernel_size = 3, padding='same')(x)
    x = BatchNormalization(axis=-1, momentum=0.99, epsilon=0.001)(x, training=True)
    x = Activation('relu')(X)              
    
    x = Conv2D(filters = nb_filter3, kernel_size = 1)(x)
    x = BatchNormalization(axis=-1, momentum=0.99, epsilon=0.001)(x, training=True)

    x = Add()([x, input_tensor])
	x = Activation('relu')(X) 
    return x
```







#### convolution block

convolution block은 identity block의 shortcut connection의 과정에 1x1 conv layer와 batch Normalization을 추가한 동작을 수행하는 layer이다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbQtwY4%2FbtqBSPHVY9d%2FXLSNe8537wDXwnrXBAjJ70%2Fimg.png)

```python
from tensorflow.keras.layers import Conv2D, BatchNormalization, Activation, Add

# filters = [nb_filter1, nb_filter2, nb_filter3]
def conv_block(input_tensor, filters, strides = 2):
    nb_filter1, nb_filter2, nb_filter3 = filters
    
    x = Conv2D(filters = nb_filter1, kernel_size = 1, strides = strides)(input_tensor)
    x = BatchNormalization(axis=-1, momentum=0.99, epsilon=0.001)(x, training=True)
    x = Activation('relu')(X)

    x = Conv2D(filters = nb_filter2, kernel_size = 3, padding='same')(x)
    x = BatchNormalization(axis=-1, momentum=0.99, epsilon=0.001)(x, training=True)
    x = Activation('relu')(X)     
    
    x = Conv2D(filters = nb_filter3, kernel_size = 1)(x)
    x = BatchNormalization(axis=-1, momentum=0.99, epsilon=0.001)(x, training=True)
    
   	shortcut = KL.Conv2D(filters = nb_filter3, kernel_size = 1, strides=2)(input_tensor)
    shortcut = BatchNormalization(axis=-1, momentum=0.99, epsilon=0.001)(shortcut, training=True)
    
    x = Add()([x, shortcut])
	x = Activation('relu')(x) 
    
    return x       
```





### model_ResNet

ResNet은 identity block, convolution block을 아래그림과 같이 쌓아서 구성한다

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FW3dJC%2Fbtq0iWLVavM%2Fqq6Fugu8CHQ6MNBkFOGN40%2Fimg.png)



각각의 ResNet의 구조는 아래와 같다

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FupZbe%2FbtqBOrva4eX%2FiNbnXbFPj1SKFfgZsDFFvk%2Fimg.png)



```python
from tensorflow.keras.layers import Conv2D, BatchNormalization, Activation, ZeroPadding2D, MaxPooling2D

def resnet_graph(input_image, architecture):
    assert architecture in ["resnet50", "resnet101"]
    
    # Stage 1
    x = ZeroPadding2D(padding = 3)(input_image)
    x = Conv2D(filters =64, kernel_size = 7, strides = 2)(x)
    x = BatchNormalization(axis=-1, momentum=0.99, epsilon=0.001)(x, training=True)
    x = Activation('relu')(x) 
    x = MaxPooling2D(poolsize = 3, strides = 2, padding="same")(x)
    C1 = x
    
    # Stage 2
    x = conv_block(x, [64, 64, 256], strides = 1)
    x = identity_block(x, [64, 64, 256])
    x = identity_block(x, [64, 64, 256])
    C2 = x
    
    # Stage 3
    x = conv_block(x, [128, 128, 512])
    x = identity_block(x, [128, 128, 512])
    x = identity_block(x, [128, 128, 512])
    x = identity_block(x, [128, 128, 512])
    C3 = x
    
    # Stage 4
    x = conv_block(x, [256, 256, 1024])
    block_count = {"resnet50": 5, "resnet101": 22}[architecture]
    for i in range(block_count):
        x = identity_block(x, 3, [256, 256, 1024])
    C4 = x
    
    # Stage 5
    x = conv_block(x, [512, 512, 2048])
    x = identity_block(x, [512, 512, 2048])
    x = identity_block(x, [512, 512, 2048])
    C5 = x
    
    return [C1, C2, C3, C4, C5]
```

