# Transformers

```python
from transformers import AutoConfig
```

 **Hugging Face**에서 제공하는 자연어 처리(NLP) 및 딥러닝 모델 라이브러리로, 다양한 사전 학습된 모델을 쉽게 가져와 사용할 수 있다.

- Hugging Face

  **자연어 처리(NLP)**를 비롯한 머신 러닝 모델을 위한 오픈 소스 라이브러리와 플랫폼을 제공하는 회사



### AutoConfig

AutoConfig는 모델의 설정 정보를 자동으로 불러오는 클래스로, 모델의 구조나 파라미터에 대한 설정을 쉽게 관리하고, 다양한 사전 학습 모델의 설정을 맞춰 불러올 수 있도록 한다.



#### from_pretrained

 특정 사전 학습 모델의 설정 정보를 Hugging Face 모델 허브에서 불러오는 method로, model 이름이나 경로를 전달받아 해당 model에 맞는 구성 정보(Config) 객체를 생성한다.

```python
config = AutoConfig.from_pretrained(pretrained_model_name_or_path = "bert-base-uncased")		# model name을 할당
print(config)

config.id2label = {"1": 'tmp'}			# 이런 식으로 metadata를 추가할 수 있다.
config.label2id = {"2": 'bar'} 		
```

출력

```
BertConfig {
  "_name_or_path": "bert-base-uncased",
  "architectures": [
    "BertForMaskedLM"
  ],
  "attention_probs_dropout_prob": 0.1,
  "classifier_dropout": null,
  "gradient_checkpointing": false,
  "hidden_act": "gelu",
  "hidden_dropout_prob": 0.1,
  "hidden_size": 768,
  "initializer_range": 0.02,
  "intermediate_size": 3072,
  "layer_norm_eps": 1e-12,
  "max_position_embeddings": 512,
  "model_type": "bert",
  "num_attention_heads": 12,
  "num_hidden_layers": 12,
  "pad_token_id": 0,
  "position_embedding_type": "absolute",
  "transformers_version": "4.46.2",
  "type_vocab_size": 2,
  "use_cache": true,
  "vocab_size": 30522
}
```

- pretrained_model_name_or_path

  - **model name**을 input parameter로 할당하는 경우

    Hugging Face의 Model Hub에서 해당 모델 이름의 구성 파일을 다운로드하고, config 객체를 생성한다.

    이 과정에서 **config.json** 파일을 모델 허브에서 다운로드하고, 이를 통해 모델의 설정 값이 지정된다.

    예시 ) 사전 학습된 model 이름 "bert-base-uncased"

  - **model dir path**를 input parameter로 할당하는 경우 (file path가 아니라 dir path를 할당해야 한다.)

     지정된 경로에서 모델의 설정 파일(**config.json**)을 load하여 config 객체를 생성한다.



### AutoModelForSequenceClassification

문장 분류 작업을 위한 사전 학습된 모델을 자동으로 불러오는 클래스로, 감정 분석, 스팸 분류, 주제 분류 등의 **문장 분류(Task)를 수행하는 데 최적화된 아키텍처**를 불러올 수 있다.



#### from_pretrained

사전 학습된 모델을 불러와 **문장 분류 작업에 특화된 아키텍처**로 구성하고, 모델 가중치를 불러온다.

특정 모델이 감정 분석이나 주제 분류와 같은 문장 분류 작업에 맞게끔 가중치가 최적화되기 때문에, 텍스트 분류에 사용된다.

```python
from transformers import AutoModelForSequenceClassification

model = AutoModelForSequenceClassification.from_pretrained(pretrained_model_name_or_path = "bert-base-uncased",
                                                           config = None,
                                                          local_files_only = False)
```

- `pretrained_model_name_or_path`: model name or model dir path

  - Model dir path인 경우

     디렉터리 내에 모델의 가중치 파일 (pytorch_model.bin)과 설정 파일 (config.json)이 있어야 한다.

- `config`(default = None): 모델의 Config 객체(AutoConfig)를 전달할 수 있다.

- `local_files_only`(default = False): True값을 할당할 경우 model을 다운로드하지 않고 local file만을 사용하여 model을 load한다.





### AutoTokenizer

 텍스트를 모델 입력으로 변환하는 **토크나이저(tokenizer)**를 자동으로 불러오는 클래스로, 텍스트 데이터를 토큰화하고, 각 토큰을 모델이 이해할 수 있는 숫자 인덱스로 변환해주는 역할을 한다.



#### from_pretrained

모델이 학습된 토크나이저 규칙과 어휘(Vocabulary)를 불러온다.

모델이 학습에 사용했던 것과 동일한 방식으로 텍스트를 토큰화해줘야, 예측의 일관성을 유지할 수 있기 때문

```python
from transformers import AutoTokenizer

tokenizer = AutoTokenizer.from_pretrained("bert-base-uncased",
                                         local_files_only = False)
```

- `pretrained_model_name_or_path`: model name or dir path

  - dir path인 경우

    directory 위치에 model의 tokenizer에 필요한 파일들이 있어야 한다.

    이 파일들은 model에 따라, 사용하는 tokenizer 유형에 따라 필요한 파일이 달라진다.

    예시로,

    - tokenizer_config.json: 토크나이저 설정 파일로, Hugging Face 라이브러리가 토크나이저 구성을 이해하는 데 필요하다.
    - 어휘 파일 (vocab.txt, merges.txt, vocab.json 등): 어휘 파일 형식은 모델 아키텍처에 따라 다르다.
      - BERT 계열 모델: vocab.txt (어휘 파일).
      - GPT-2, RoBERTa 계열 모델: merges.txt와 vocab.json (병합 규칙과 어휘 파일).
      - SentencePiece 기반 모델 (예: T5, mBART 등): spiece.model (SentencePiece 모델 파일).

- `local_files_only`(default = False): True값을 할당할 경우 tokenizer를 다운로드하지 않고 local file만을 사용하여 model을 load한다.



위 내용에서, tokenizer 객체를 사용하는 방법을 알려줘

##### tokenizer

tokenizer 객체를 사용하면 텍스트를 model이 학습한 방식으로 token화하여 model input을 위한 data로 변환할 수 있다.

```python
input_data_encode = tokenizer(input_data, 
                             max_length = 512, 
                             truncation = True, 
                             padding = True, 
                             return_tensors = 'pt')
```

- `input_data`: token화 하고나 하는 문장. 여러 문장이 list형태로 구성되거나, 하나의 문장을 string으로 구성되어야 한다.

- `max_length`: incoding될 text의 최대 길이를 지정한다.

  위와 같은 경우, 입력 데이터가 지정된 최대 길이를 초과하면, 512 토큰까지만 포함하고 나머지는 잘린다.

- `truncation`: True값일 경우 최대 길이를 초과하는 text를 잘라낸다.

- `padding`: True값일 경우, 입력 시퀀스의 길이가 다르면 모든 시퀀스가 같은 길이가 되도록 **패딩(padding)**을 추가한다.

- `return_tensors`: `pt`값을 할당하면 토크나이저의 출력 값을 PyTorch 텐서 형식(pt)으로 return한다.



##### save_pretrained

토크나이저 또는 모델 객체를 저장하는 데 사용되는 method

```python
from transformers import AutoTokenizer
tokenizer = AutoTokenizer.from_pretrained(path, local_files_only= True)
tokenizer.save_pretrained(finetuned_dir_path)		# 불러온 정보 그대로 저장하는 동작
```

저장되는 file

- `tokenizer_config.json`: 토크나이저 설정 파일로, 토크나이저가 구성된 방식이 기록되어 있다.

- `vocab.txt`: 모델이 사용하는 어휘 집합(vocabulary)

- `tokenizer.json`: 토크나이저의 사전 토큰화 및 어휘 정보를 포함하는 JSON 형식의 파일

- `special_tokens_map.json`: 특별 토큰([CLS], [SEP], [PAD], [UNK])에 대한 매핑 정보가 들어있다.

  ```
  {
    "cls_token": "[CLS]",				
    "mask_token": "[MASK]",
    "pad_token": "[PAD]",
    "sep_token": "[SEP]",
    "unk_token": "[UNK]"
  }
  ```

  - cls_token (”[CLS]”)

    - 사용 목적: 분류 작업에서 문장의 시작을 나타내기 위해 사용되는 토큰. 

      예를 들어, 문장 분류나 감정 분석과 같은 작업에서는 문장 전체의 특징을 학습할 때 이 토큰의 위치에서 추출된 벡터를 사용한다.

    - 위치: 입력 문장의 가장 앞에 추가된다.

  - mask_token (”[MASK]”)

    - 사용 목적: 마스킹 언어 모델링(Masked Language Modeling, MLM)에서 특정 단어를 가리기 위해 사용된다. 

      이 토큰이 있는 위치의 단어는 모델이 추론해야 하는 목표가 된다.

    - 위치: 모델 학습 과정에서 임의의 단어를 마스킹할 때 해당 단어 자리에 삽입된다.

  - pad_token (”[PAD]”)

    - 사용 목적: 입력 시퀀스의 길이를 맞추기 위해 사용된다. 

      모델에 들어가는 문장이 서로 다른 길이일 때 동일한 길이로 맞추기 위해 문장의 끝에 pad_token을 추가하여 패딩을 진행한다.

    - 위치: 문장 끝 부분에 추가되며, 최종 시퀀스 길이에 맞추기 위해 필요한 만큼 반복 삽입된다.

  - sep_token (”[SEP]”)

    - 사용 목적: 두 개의 문장을 구분하는 역할을 하며, 예를 들어 문장 간 관계를 학습하는 자연어 추론(NLI) 작업에서 사용된다.
    - 위치: 두 문장 사이에 삽입되거나, 단일 문장 끝에 추가된다.

  - unk_token (”[UNK]”)

    - 사용 목적: 사전에 없는 단어(알 수 없는 단어)에 대해 사용되는 토큰으로, 토크나이저가 처리 중인 텍스트에서 사전에 없는 단어를 만나면 unk_token으로 대체된다.
    - 위치: 사전에 없는 단어의 자리에 해당 토큰이 삽입된다.

보통 학습된 모델 weight파일과 같이 둔다.

```
model name/              
├── config.json								# 모델의 구조 및 하이퍼파라미터 정보
├── pytorch_model.bin					# model weight file
├── special_tokens_map.json		# 모델에서 사용되는 특수 토큰들의 매핑 정보
├── tokenizer.json						# 실제 토크나이저의 규칙과 어휘 정보를 담고 있는 JSON 
├── tokenizer_config.json			# 토크나이저의 설정 파일로, 토크나이저의 동작 방식을 설정
└── vocab.txt									# 모델이 사용하는 어휘 집합(vocabulary)
```





### Seq2SeqTrainingArguments

**시퀀스-투-시퀀스(Seq2Seq) 모델**을 훈련하기 위한 설정을 정의하는 class로, 주로 기계 번역, 요약, 텍스트 생성과 같은 Seq2Seq 작업에서 활용된다.

```python
from transformers import Seq2SeqTrainingArguments

training_args = Seq2SeqTrainingArguments(
  	seed=42,
  do_train = True,
  do_eval = True,
  num_train_epochs = 5,
  weight_decay = 0.01,
  warmup_steps = 200,
  per_device_train_batch_size = 16,
  dataloader_pin_memory = False if 'cuda' in device else True,
  logging_steps = 500,
  logging_strategy = 'steps',
  logging_dir = f"/logs",
  disable_tqdm = True,
  metric_for_best_model = 'f1',
  learning_rate = 3e-5,
  save_strategy = "no",
  eval_steps=0.1,
  evaluation_strategy = 'no',
  load_best_model_at_end = False
)
```

- `do_train`: model 학습을 수행할지 결정
- `do_eval`: mode 평가를 진행할지 결정
- `num_train_epochs`: Epoch 결정
- `weight_decay`:가중치 감소 인자
- `warmup_steps`: 학습 초기에 학습률을 점진적으로 증가시키는 단계 수를 설정
- `dataloader_pin_memory`: True로 설정하면 DataLoader가 메모리에 고정된 텐서를 생성해, GPU로 데이터를 더 빠르게 전송할 수 있다.
- `per_device_train_batch_size`: batch size 결정
- `logging_steps`: 로그를 남길 단계의 빈도를 설정. 예를 들어, 100으로 설정하면 매 100 스텝마다 로그를 기록
- `logging_strategy`: 로깅 전략을 설정. steps 또는 epoch을 선택할 수 있으며, steps로 설정 시 logging_steps마다 로깅이 이루어진다.
- `logging_dir`: logging 파일을 저장할 dir 결정
- `disable_tqdm`: True로 설정하면 tqdm 진행 바가 비활성화
- `metric_for_best_model`: 최적 모델을 선택할 때 사용할 평가 기준을 설정.
- `save_strategy`: 모델을 저장하는 주기를 설정. epoch 또는 steps 중 선택하며, steps로 설정하면 지정한 save_steps마다 모델을 저장
- `eval_steps`:  평가를 수행하는 단계 수를 지정. 예를 들어, 100으로 설정 시 매 100 스텝마다 평가가 이루어진다. [0,1] 사이의 값일 경우 총 학습 단계의 비율로 해석된다.
- `evaluation_strategy`: 평가 전략을 지정. epoch, steps, no 중에서 선택하며, epoch은 각 에폭 후 평가를 수행하고 steps는 eval_steps마다 평가를 수행한다.
- `per_device_eval_batch_size`: 평가 시 각 디바이스에 할당할 배치 크기를 설정
- `load_best_model_at_end`: 학습 종료 시점에서 가장 성능이 좋은 모델 가중치를 불러온다. True로 설정하면 학습 종료 시점에 자동으로 최적 모델을 로드한다.





### Trainer

모델 학습 및 평가를 위한 고수준 API를 제공한다.

```python
from transformers import Trainer
trainer = Trainer(
    model=None,                       # 학습할 모델 (transformers의 모델 클래스)
    args=None,                        # TrainingArguments 객체
    data_collator=None,               # 데이터 전처리 방식 지정
    train_dataset=None,               # 학습 데이터셋
    eval_dataset=None,                # 평가 데이터셋
    tokenizer=None,                   # 모델에 사용된 토크나이저 (선택 사항)
    model_init=None,                  # 모델 초기화 함수 (선택 사항)
    compute_metrics=None,             # 평가에 사용할 메트릭 함수 (선택 사항)
    callbacks=None,                   # 학습 중간에 호출할 콜백 리스트
    optimizers=(None, None)           # 옵티마이저와 학습률 스케줄러
)

trainer.train()
trainer.save_model()
```

#### train

모델 학습 시작

#### save_model

train()으로 학습이 완료된 모델의 가중치를 디스크에 저장한다.

`Seq2SeqTrainingArguments`에서 output_dir 인자에 지정된 경로에 저장한다.

저장되는 파일은 아래와 같다.

- `pytorch_model.bin` : 모델의 가중치 
- `config.json`: 모델의 구조 및 하이퍼파라미터 정보





### TrainerCallback

Trainer 클래스를 사용할 때, 학습 중 특정 이벤트가 발생할 때마다 실행할 수 있는 맞춤형 동작을 정의할 수 있도록 하는 콜백 클래스

```python
from transformers import TrainerCallback

class CustomCallback(TrainerCallback):
    def __init__(self, **kwargs):

        self.domain_id = kwargs.get("domain_id")
        self.model_id = kwargs.get("model_id")
        self.training_id = kwargs.get("training_id")
        self.debug = kwargs.get("debug")
        self._type = kwargs.get("mode")
        self.state_object = kwargs.get("state")
        self.id = self.training_id
    
    def on_train_begin(self, args, state, control, **kwargs):
        self.current_step = 0
  	
    def on_epoch_end(self, args, state, control, **kwargs):
        print(f"Epoch {state.epoch} has ended.")
    
    ...
```

**사용법**

- 위의 CustomLoggingCallback 객체를 list에 담아서 Trainer 선언 시 callbacks 에 전달한다.

- **on_train_begin**: 학습이 시작될 때 호출된다. 주로 설정 초기화, 로그 초기화 등에 사용된다.

  ```python
  def on_train_begin(self, args, state, control, **kwargs):
      pass
  ```

  - `args`: TrainingArguments 객체
  - `state`: 학습 상태를 관리하는 객체

- **on_train_end**: 학습이 종료될 때 호출된다. 

  ```python
  def on_train_end(self, args, state, control, **kwargs):
      pass
  ```

- **on_epoch_begin**: 각 에포크가 시작될 때 호출

  ```python
  def on_epoch_begin(self, args, state, control, **kwargs):
      pass
  ```

  

- **on_epoch_end**: 각 에포크가 종료될 때 호출

  ```python
  def on_epoch_end(self, args, state, control, **kwargs):
      pass
  ```

  

- **on_step_begin**: 각 스텝이 시작될 때 호출

  ```python
  def on_step_begin(self, args, state, control, **kwargs):
      pass
  ```

  

- **on_step_end**: 각 스텝이 끝날 때 호출

  ```python
  def on_step_end(self, args, state, control, **kwargs):
      pass
  ```

  

- **on_log**: 로깅 시 호출. 주로 로그 추가 작업 시 사용

  ```python
  def on_log(self, args, state, control, logs=None, **kwargs):
      pass
  ```

  

- **on_evaluate**: 평가 중 호출. 평가 후 통계나 특수 작업에 사용

  ```python
  def on_evaluate(self, args, state, control, metrics, **kwargs):
      pass
  ```

  

- **on_save**: 모델을 저장할 때 호출

  ```python
  def on_save(self, args, state, control, **kwargs):
      pass





### pipelines

사전 훈련된 모델을 여러 자연어 처리(NLP) 작업에 즉시 사용할 수 있도록 도와주는 간편한 추론 API 

```python
from transformers import pipelines
```



#### TextClassificationPipeline

텍스트 분류를 위한 전문 pipeline

```python
from transformers.pipelines import TextClassificationPipeline
from optimum.onnxruntime import ORTModelForSequenceClassification
from transformers import AutoModelForSequenceClassification, AutoTokenizer

# 사용할 모델의 경로 설정
model_path = "path/to/model_directory"

# 모델 및 토크나이저 로드
try:
  	# onnxruntime 을 사용하여 onnx 모델 load
    classifier_model = ORTModelForSequenceClassification.from_pretrained(model_path)
except:
    # transformer로 학습된 모델 load
    classifier_model = AutoModelForSequenceClassification.from_pretrained(model_path)

# 토크나이저 로드
tokenizer = AutoTokenizer.from_pretrained(model_path)

# TextClassificationPipeline 생성
text_classifier = TextClassificationPipeline(
    model=classifier_model, 
    tokenizer=tokenizer,
    top_k=None,
    truncation=True
)

# 예시 텍스트 분류
result = text_classifier("This is an amazing library for NLP!")
print(result)
```

- `model`: TextClassificationPipeline에 사용할 모델 지정
- `tokenizer`: tokenizer 지정
- `top_k`: 반환할 상위 예측의 개수를 지정
- `truncation`: 입력 텍스트가 모델의 최대 입력 길이를 초과할 때, 이를 자를지 여부를 결정하는 인수
