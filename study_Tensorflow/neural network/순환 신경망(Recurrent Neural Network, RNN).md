# 순환 신경망(Recurrent Neural Network, RNN)

## 1. RNN

자연어 처리 문제에 주로 사용되는 인공신경망 구조(시계열 데이터를 다루기에 최적화된 인공신경망)

> 시계열 데이터: 시간축을 중심으로 현재 시간의 데이터가 앞, 뒤 시간의 데이터와 연관 관계를 가지고 있는 데이터를 의미. 
>
> 주식 가격, 또는 파형으로 표현되는 음성 데이터 등이 대표적인 시계열 데이터이다.

RNN은 기본적인 ANN구조에서 이전 시간(t-1)의 은닉층의 출력값을 다음 시간(t)에 은닉층의 입력값으로 다시 집어넣는 경로가 추가된 형태이다.

RNN을 다른 관점으로 바라보면, 시간축에 따라 인공신경망을 펼친 Unfold 형태로 생각할 수 있다.

> 예를 들어, 5개의 단어로 이루어진 문장을 RNN의 인풋으로 사용한다면, 순환 연결이 없는 인공신경망을 5층으로 쌓은 것으로 바라볼 수 있다.

아래 그림은 Unfold(펼침) 형태의 RNN을 나타냄

![](https://mblogthumb-phinf.pstatic.net/MjAxODAxMThfMjM3/MDAxNTE2Mjc0MzUwNjEw.lLbS6oEbl99TsYt8QZjnZqNMR8VsbdkGbhOfC9Vc4iwg.Fr9keq2hMYz_dSZECHCaz-n6-OuwS5rDxObCq_7RHwkg.PNG.jaeyoon_95/image.png?type=w800)

이는 현재 시간의 결과가 다음 시간(t+1)에 영향을 미치고, 이는 다시 다음 시간에 영향을 미치는 과정이 끊임없이 반복되는 인공신경망 구조이다.

- 길이 T를 가진 입력 시퀀스 x를 I개의 인풋 노드, H개의 히든 노드, K개의 아웃풋 노드를 가진  RNN에 입력한다면 
  $$
  a_{h}^{t} = \sum_{i=1}^{I}w_{ih}x_{i}^{t}+\sum_{h'=1}^{H}w_{h'h}b_{h'}^{t-1}
  $$
  
  $$
  a_{h}^{t}:\ 시간t일때\ 히든\ 레이어의\ 출력값\\
  x_{i}^{t}:\ 시간t일때\ i번째\ 입력 \ 데이터 \\
  w_{ih}:\ input데이터로\ 넘어오는\ 가중치\\
  w_{h'h}:\ 히든\ 유닛에서\ 히든\ 유닛으로\ 되돌아오는\ 가중치\\
  b_{h'}^{t-1}:\ 이전\ 시간(t-1)의\ 히든\ 유닛의\ 활성값
  $$
  시간t일때의 히든 레이어의 출력값에 Sigmoid 또는 ReLU같은 활성 함수를 씌우면 시간 t일때의 히든 유닛의 활성값을 계산할 수 있다.
  $$
  b_{h}^{t} = \sigma_{h}(a_{h}^{t})\\
  b_{h}^{t}:\ 히든\ 유닛의\ 활성값\\
  \sigma_{h}:\ 활성\ 함수
  $$
  시퀀스 처음 시작(t=0)일 때는 이전 시간의 히든 유닛의 활성값이 없기 때문에 임의로 지정해주어야 한다.

  > 보통은 초기 활성값은 0으로 한다.

- **출력층**에서는 

  1. 일반적인 ANN과 같은 방식으로 은닉층으로부터 주어지는 입력값과 가중치를 곱하고 합해서 구한 출력값을 계산
     $$
     a_{out}^{t} = a_{k}^{t} = \sum_{h=1}^{H}w_{hk}x_{h}^{t}\\
     w_{hk}:\ 히든\ 레이어에서\ output레이어로\ 넘어간\ 가중치
     x_{h}^{t}:\ 히든\ 레이어로부터\ 넘어온\ 값
     $$

  2. 시간 t일때 마지막 레이어의 출력값에 활성 함수를 적용해서 출력 유니스이 최종 출력값을 계산
     $$
     b_{out}^{t} = \sigma_{out}(a_{out}^{t})
     $$

**RNN의 장점**

이전 상태에 대한 정보를 일종의 메모리 형태로 저장할 수 있다.

이는 앞에서 얻은 정보가 다음에 얻은 데이터와 연관 관계를 가지는 시계열 데이터를 다룰 때 매우 강력한 효과를 발휘한다.

**RNN의 단점**

Vanishing Gradient Problem(경사도 사라짐 문제)가 발생할 수 있다.

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSsZD1lr3mkJp7ioA758ZQNIqsHz11E5njHHw&usqp=CAU)

시간축 1에서 받은 영향력은 크게 남아있지만, 새로운 시간축에서 들어온 input데이터의 영향력에 의해 영향력이 반복해서 덮어씌워며 점점 약해지는 것

- RNN이 장기 기억력을 가지지 못한다.

  현재 시간축에서 멀리 떨어진 시간축의 데이터의 중요도를 크게 고려하지 못한다.

  >  LSTM(장/단기 기억 네트워크)는 이런 경사도 사라짐 문제를 해결하기 위해서 제안된 RNN의 발전형 구조



#### Cher-RNN

RNN을 처음 배울 때 가장 많이 사용되는 예제 중 하나로서 하나의 글자를 RNN의 입력값으로 받고, RNN은 다음에 올 글자를 예측하는 문제임

> Lenguage Modeling: 어떤 단어 배열이 있을 때, 해당 단어 배열을 기반으로 다음에 어떤 단어가 오는게 적합한지 예측을 하는 모델링

이 문제를 풀기 위해서 트레이닝 데이터를 구성할 때,  타겟 데이터를 인풋 문장에서 한 글자씩 뒤로 민 형태로 구성해야 한다.

> 예를 들어서, "HELLO"라는 문장을 학습시키고 싶을 경우, RNN의 (input data, output data)쌍을 (H, E), (E, L), (L, L), (L, O)로 구성한다.
>
> H다음 E, E다음 L, L다음 L... 형태로

- 과정 설명

  문자로만 구성된 데이터셋일 경우, 전체 문자 집합은 알파벳 글자 개수인 26이 될 것이다.

  input data는 One-hot Encoding 데이터로 받아지고, 이 데이터를 임베딩 매트릭스를 곱하여 임베딩 된 백터로 만든 후 RNN레이어에 넘긴다. 그 후 Softmax 회귀를 수행하고  argmax를 취해서 26개 중에 input 데이터 이후에 오는 것이 가장 자연스러울지 정학 후 두 번째 input으로 넣는다.

  input data1(One-hot Encoding 데이터) -> Emdedding -> RNN -> Softmax -> argmax -> input data2


**코드 구현**

Char-RNN 예제 - Keras API를 이용한 구현

```python
from __future__ import absolute_import, division, print_function, unicode_literals

from absl import app
import tensorflow as tf

import numpy as np
import os
import time

# input 데이터와 input 데이터를 한글자씩 뒤로 민 target 데이터를 생성하는 utility 함수를 정의합니다.
def split_input_target(chunk):
  input_text = chunk[:-1]
  target_text = chunk[1:]

  return input_text, target_text

# 학습에 필요한 설정값들을 지정합니다.
data_dir = tf.keras.utils.get_file('shakespeare.txt', 'https://storage.googleapis.com/download.tensorflow.org/data/shakespeare.txt')  # shakespeare
#data_dir = './data/linux/input.txt'  # linux
batch_size = 64      # Training : 64, Sampling : 1
seq_length = 100     # Training : 100, Sampling : 1
embedding_dim = 256  # Embedding 차원
hidden_size = 1024   # 히든 레이어의 노드 개수
num_epochs = 10

# 학습에 사용할 txt 파일을 읽습니다.
text = open(data_dir, 'rb').read().decode(encoding='utf-8')
# 학습데이터에 포함된 모든 character들을 나타내는 변수인 vocab과
# vocab에 id를 부여해 dict 형태로 만든 char2idx를 선언합니다.
vocab = sorted(set(text))  # 유니크한 character 개수
vocab_size = len(vocab)
print('{} unique characters'.format(vocab_size))
char2idx = {u: i for i, u in enumerate(vocab)}
idx2char = np.array(vocab)

# 학습 데이터를 character에서 integer로 변환합니다.
text_as_int = np.array([char2idx[c] for c in text])

# split_input_target 함수를 이용해서 input 데이터와 input 데이터를 한글자씩 뒤로 민 target 데이터를 생성합니다.
char_dataset = tf.data.Dataset.from_tensor_slices(text_as_int)
sequences = char_dataset.batch(seq_length+1, drop_remainder=True)
dataset = sequences.map(split_input_target)

# tf.data API를 이용해서 데이터를 섞고 batch 형태로 가져옵니다.
dataset = dataset.shuffle(10000).batch(batch_size, drop_remainder=True)

# tf.keras.Model을 이용해서 RNN 모델을 정의합니다.
class RNN(tf.keras.Model):
 def __init__(self, batch_size):
   super(RNN, self).__init__()
   self.embedding_layer = tf.keras.layers.Embedding(vocab_size, embedding_dim,
                                                    batch_input_shape=[batch_size, None])
   self.hidden_layer_1 = tf.keras.layers.LSTM(hidden_size,
                                             return_sequences=True,
                                             stateful=True,
                                             recurrent_initializer='glorot_uniform')
   self.output_layer = tf.keras.layers.Dense(vocab_size)

 def call(self, x):
   embedded_input = self.embedding_layer(x)
   features = self.hidden_layer_1(embedded_input)
   logits = self.output_layer(features)

   return logits

# sparse cross-entropy 손실 함수를 정의합니다.
def sparse_cross_entropy_loss(labels, logits):
  return tf.reduce_mean(tf.keras.losses.sparse_categorical_crossentropy(labels, logits, from_logits=True))

# 최적화를 위한 Adam 옵티마이저를 정의합니다.
optimizer = tf.keras.optimizers.Adam()

# 최적화를 위한 function을 정의합니다.
@tf.function
def train_step(model, input, target):
  with tf.GradientTape() as tape:
    logits = model(input)
    loss = sparse_cross_entropy_loss(target, logits)
  grads = tape.gradient(loss, model.trainable_variables)
  optimizer.apply_gradients(zip(grads, model.trainable_variables))

  return loss

def generate_text(model, start_string):
  num_sampling = 4000  # 생성할 글자(Character)의 개수를 지정합니다.

  # start_sting을 integer 형태로 변환합니다.
  input_eval = [char2idx[s] for s in start_string]
  input_eval = tf.expand_dims(input_eval, 0)

  # 샘플링 결과로 생성된 string을 저장할 배열을 초기화합니다.
  text_generated = []

  # 낮은 temperature 값은 더욱 정확한 텍스트를 생성합니다.
  # 높은 temperature 값은 더욱 다양한 텍스트를 생성합니다.
  temperature = 1.0

  # 여기서 batch size = 1 입니다.
  model.reset_states()
  for i in range(num_sampling):
    predictions = model(input_eval)
    # 불필요한 batch dimension을 삭제합니다.
    predictions = tf.squeeze(predictions, 0)

    # 모델의 예측결과에 기반해서 랜덤 샘플링을 하기위해 categorical distribution을 사용합니다.
    predictions = predictions / temperature
    predicted_id = tf.random.categorical(predictions, num_samples=1)[-1,0].numpy()

    # 예측된 character를 다음 input으로 사용합니다.
    input_eval = tf.expand_dims([predicted_id], 0)
    # 샘플링 결과를 text_generated 배열에 추가합니다.
    text_generated.append(idx2char[predicted_id])

  return (start_string + ''.join(text_generated))

def main(_):
  # Recurrent Neural Networks(RNN) 모델을 선언합니다.
  RNN_model = RNN(batch_size=batch_size)

  # 데이터 구조 파악을 위해서 예제로 임의의 하나의 배치 데이터 에측하고, 예측결과를 출력합니다.
  for input_example_batch, target_example_batch in dataset.take(1):
    example_batch_predictions = RNN_model(input_example_batch)
    print(example_batch_predictions.shape, "# (batch_size, sequence_length, vocab_size)")

  # 모델 정보를 출력합니다.
  RNN_model.summary()

  # checkpoint 데이터를 저장할 경로를 지정합니다.
  checkpoint_dir = './training_checkpoints'
  checkpoint_prefix = os.path.join(checkpoint_dir, "ckpt_{epoch}")

  for epoch in range(num_epochs):
    start = time.time()

    # 매 반복마다 hidden state를 초기화합니다. (최초의 hidden 값은 None입니다.)
    hidden = RNN_model.reset_states()

    for (batch_n, (input, target)) in enumerate(dataset):
      loss = train_step(RNN_model, input, target)

      if batch_n % 100 == 0:
        template = 'Epoch {} Batch {} Loss {}'
        print(template.format(epoch+1, batch_n, loss))

    # 5회 반복마다 파라미터를 checkpoint로 저장합니다.
    if (epoch + 1) % 5 == 0:
      RNN_model.save_weights(checkpoint_prefix.format(epoch=epoch))

    print ('Epoch {} Loss {:.4f}'.format(epoch+1, loss))
    print ('Time taken for 1 epoch {} sec\n'.format(time.time() - start))

  RNN_model.save_weights(checkpoint_prefix.format(epoch=epoch))
  print("트레이닝이 끝났습니다!")

  sampling_RNN_model = RNN(batch_size=1)
  sampling_RNN_model.load_weights(tf.train.latest_checkpoint(checkpoint_dir))
  sampling_RNN_model.build(tf.TensorShape([1, None]))
  sampling_RNN_model.summary()

  # 샘플링을 시작합니다.
  print("샘플링을 시작합니다!")
  print(generate_text(sampling_RNN_model, start_string=u' '))

if __name__ == '__main__':
  # main 함수를 호출합니다.
  app.run(main)
```

## 2. 장/단기 기억 네트워크(Long Short-Term Memory, LSTM)

LSTM은 은닉층을 각각의 노드가 input gate, forget date, output gate로 구성된 메모리 블럭이라는 조금 복잡한 구조로 대체한다. (이를 이용해서 경사도 사라짐 문제를 완화할 수 있다.)

![](https://kr.mathworks.com/help/deeplearning/ref/lstmgates.png)

- 경사도 사라짐 문제 해결 동작

  아래 그림에서 은닉층의 아래는 input gate, 은닉층의 왼쪽은 forget gate, 은닉층의 위쪽은 output gate를 나타낸다. 또한 o은 게이트가 열린 상태, -는 게이트가 닫힌 상태를 나타낸다.

![](https://lh3.googleusercontent.com/proxy/dmo-4IzICGsIfLHVMNp_ZP_M92LBwrr0OeGNarbY2WJm4Uh0L6bmn9JQF_LFFaZawmxV344oILGFyXGc_MnbXjbyDSO9c0jEyVz73lMJhGEnD3XN3hfD02mNl512O2YY8Dp99ufhLMfOZ1qKaXOsUQ)

​	그림에서는, 시간 1에서 인풋 데이트를 열어서 시간 1의 인풋 데이터의 영향력을 가져가고, 시간 6까	지 포겟 게이트를 열어서 시간 1의 영향력을 계속해서 다음 시간으로 가져간다. 그러면서 시간 2에	서부터 시간6까지는 인풋 게이트를 닫아서 해당 시간동안의 인풋 데이터의 영향력을 없앤다. 그리고	시간 1, 2, 3, 5에서는 아웃풋 게이트를 닫고 시간 4, 6에서만 아웃풋 게이트를 연다.

​	이를 통해서 RNN의 출력 결과를 4, 6에서만 방출할 수 있다.

### 

## 3. Gate Recurren Unit, GRU

LSTM의 간략화된 버전으로, 3개의 게이트를 2개의 게이트로 축소한 것이다.

GRU는 메모리 블록으로 **리셋 게이트(r)**와 **업데이트 게이트(z)**를 가지고 있다.

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQiYjHwgdH4fSrc7WsU-sP968fscHtRhwfhlQ&usqp=CAU)

