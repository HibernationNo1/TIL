# kiwipiepy

(Version: 0.20.1)

docs: https://bab2min.github.io/kiwipiepy/v0.20.0/kr/

kiwipiepy 는 한국어 형태소 분석기 라이브러리로, 한국어 텍스트를 분석하고 처리하는 데 최적화된 도구이다.

이 라이브러리는 **형태소 분석**, **품사 태깅**, **어절 분리**와 같은 작업을 고속으로 수행할 수 있으며, **정확하고 빠른 한국어 자연어 처리**를 목표로 설계되었다.



- **주요 기능**

  - **형태소 분석 (Morpheme Analysis)**

    문장을 형태소 단위로 분리하여 각 형태소의 품사 정보를 제공하고, 어절을 분석하는 기능.

    예시 )  “오늘 날씨가 좋다”라는 문장 >  “오늘/Noun”, “날씨/Noun”, “가/Postposition”, “좋다/Adjective”로 분석된다.

  - **품사 태깅 (Part-of-Speech Tagging)**

    형태소에 대해 **명사(Noun), 동사(Verb), 형용사(Adjective)** 등의 품사 태그를 부여하는 기능.

    품사 정보를 통해 텍스트의 문법 구조와 의미를 파악할 수 있다.

  - **N-gram 추출**

    텍스트에서 단어 N-그램을 추출하여, 연속된 단어 또는 형태소 패턴을 분석할 수 있다.

    N-gram은 검색엔진, 키워드 추출, 문장 유사도 분석 등에 유용하게 사용된다.

    - N-gram이란?

      텍스트에서 연속된 N개의 단어 또는 글자로 이루어진 묶음을 의미한다.

      ````
      N-gram의 종류
      	1.	Unigram (1-gram): 각 단어 또는 글자를 개별적으로 분석합니다.
      		•	예: “오늘 날씨가 좋다” → ["오늘", "날씨가", "좋다"]
      	2.	Bigram (2-gram): 두 단어(또는 글자)를 하나의 묶음으로 분석합니다.
      		•	예: “오늘 날씨가 좋다” → [("오늘", "날씨가"), ("날씨가", "좋다")]
      	3.	Trigram (3-gram): 세 단어(또는 글자)를 하나의 묶음으로 분석합니다.
      		•	예: “오늘 날씨가 좋다” → [("오늘", "날씨가", "좋다")]
      
      N-gram의 주요 활용
      	•	문서 유사도 계산: 두 문서의 N-gram을 비교하여 유사도를 측정할 수 있습니다.
      	•	오타 및 문장 교정: 자주 등장하는 N-gram을 학습해, 오타가 있는 경우 유사한 N-gram을 바탕으로 수정할 수 있습니다.
      	•	문장 패턴 분석: 특정 패턴이 자주 등장하는지 파악하여 텍스트의 주요 흐름이나 주제를 분석할 수 있습니다.
      ````

  - **오타 교정 및 사용자 정의 사전 추가**

    자주 발생하는 오타를 수정하거나, 특정 분야의 전문 용어나 사용자 정의 단어를 추가할 수 있다.

    도메인 특화 텍스트 분석 시, 사용자가 추가한 단어가 효과적으로 반영된다.

  - **고속 처리**

    대규모 텍스트 데이터를 처리하는 데 최적화되어 있으며, 높은 성능을 제공한다.

    Python에서 쉽게 사용할 수 있어, AI 모델이나 머신러닝 파이프라인에 통합하기 좋다.

## Kiwi

```python
from kiwipiepy import Kiwi
kiwi = Kiwi(typos = 'basic_with_continual_and_lengthening', 
            load_default_dict = True, 
            model_type = 'sbg',
            num_workers = 0,
            integrate_allomorph = 0
            )
```

- `typos` (default = None, 사용하지 않음): 오타 보정기능 사용

  사용하고자 할 땐 오타 교정기 타입을 명시해야 한다.

  - `basic`: 형태소 내의 오타를 교정하는 기본적인 오타 정의자
  - `continual`: 형태소 간의 연철 오타(`책을` <- `채글`)를 교정하는 오타 정의자
  - `lengthening`: 한 음절을 여러 음절로 늘려 적은 오타(`진짜` <- `지인짜`)를 교정하는 오타 정의자
  - `basic_with_continual`: basic과 continual 두 오타 정의자를 합친 오타 정의자
  - `basic_with_continual_and_lengthening`: basic, continual, lengthening 세 오타 정의자를 합친 오타 정의자

- `load_default_dict` (default = True):  Kiwi의 기본 사전을 로드할지 여부를 결정

  False로 설정하면 기본 사전을 사용하지 않고, 사용자가 정의한 사전만으로 분석한다.

- `model_type` (default = knlm): 형태소 분석에 사용할 모델을 지정

  - 'knlm': **Korean Named Language Model**의 약자로, 한국어에 최적화된 기본 모델.
  - 'sbg': **문장 경계 생성(Sentence Boundary Generator)** 모델로, 문장 구분을 좀 더 정확하게 처리할 수 있다.

- `num_workers` (default = 0): 병렬 처리를 위해 사용할 워커(worker) 프로세스 수를 지정

- `integrate_allomorph` (default = True): 이형태 통합 여부를 지정하며, True로 설정하면 어미 변화를 통합하여 분석한다.

  예시) “먹다”, “먹었다”와 같은 어미 변화를 하나의 기본 형태로 통합한다.

  한국어의 특성상 동사, 형용사 등의 어미가 자주 변형되므로, 이를 통합하면 분석 결과의 일관성을 유지하는 데 도움된다.



### Options

- `kiwi.space_tolerance`: 연속된 공백을 무시하는 정도를 설정하는 option으로, 분석 시 text에 공백이 여러 개 있어도 어느 정도 무시하고 분석을 진행하도록 설정할 수 있다.

  - 값이 클수록 연속된 공백이 많더라도 분석 결과에 영향을 덜 미치며, 여러 공백을 무시하고 연속된 텍스트처럼 처리한다.
  - 값이 작을수록 공백을 구분하여 텍스트를 나누는 데 영향을 준다.

  ```python
  kiwi = Kiwi()
  kiwi.space_tolerance = 5  # 연속된 공백을 최대 5개까지 무시
  ```

- `typo_cost_weight`(defaul = 6): 오타 교정 비용. Kiwi 객체 생성 시 `typos` 인수에 None값 외의, 오타 생성기를 명시했을 경우에만 사용한다.

  값이 낮을수록 더 적극적으로 교정을 수행하며, 맞는 표현도 과도교정이 될 수 있으니 주의하자

  ```python
  from kiwipiepy import Kiwi
  kiwi = Kiwi(typos = 'basic_with_continual_and_lengthening', 
              load_default_dict = True, 
              model_type = 'sbg',
              num_workers = 0,
              integrate_allomorph = 0
              )
  
  kiwi.typo_cost_weight = 3       # 오타 가중치 설정 (default=6)
  
  typos_list = ['오늘은 기분이 매우 조타.', 
                '여기서 기다리셔요, 금방 갈께요.',    
                '웨 지가캤니?',                
                '오늘 날시는 따뜨읏 합니다. 하지만 내일 날씨가 추우니 감기 조심하세오.']
  
  for typo in typos_list:
      tokens = kiwi.tokenize(typo)				# 형태소 분리
      joined_text = kiwi.join(tokens)			# 형태소들을 하나의 문장으로 다시 합치기
      print(f"교정 전 문장: {typo}\n교정 후 문장: {joined_text}\n")
  
  ```
  
  




### method

#### Add_user_word

**Kiwi 형태소 분석기에 사용자 정의 단어를 추가**하여, 분석에 반영되도록 하는 method로, 기본 사전에 없는 단어나 새로운 의미를 가진 단어를 추가하여 **domain 특화된 text 분석**을 수행할 수 있게 한다.

```python
kiwi.add_user_word(word, tag, score=0, user_value = None, orig_word = None)
```

- `word`: 사용자 정의로 추가할 단어

- `tag`: **품사 태그**를 지정. 이 태그는 추가하려는 단어가 어떤 품사인지 나타낸다.

  품사 태그는 Kiwi에서 사용하는 한국어 형태소 분석기 품사 태그 규칙에 따라 입력되며, 주요 태그 예시는 아래와 같다.

  ```
   	•	NNG: 일반 명사
   	•	NNP: 고유 명사
   	•	VV: 동사
   	•	VA: 형용사
   	•	MAG: 일반 부사
   	•	XPN: 접두사
   	•	XSV: 동사 파생 접미사
  	•	NNB: 의존 명사
  	•	NR: 수사
  	•	NP: 대명사
  	•	MM: 관형사
  	•	IC: 감탄사
  	•	MAJ: 접속 부사
  	•	VX: 보조 용언
  	•	VCN: 부정지정사 (예: 아니다)
  	•	VCP: 긍정지정사 (예: 이다)
  	•	SF: 마침표, 물음표, 느낌표
  	•	SP: 쉼표, 가운뎃점, 콜론, 빗금
  	•	SS: 따옴표, 괄호, 줄표
  	•	SE: 줄임표
  	•	SO: 붙임표 (물결, 숨김, 빠짐)
  	•	SW: 기타 기호
  	•	SL: 외국어
  	•	SH: 한자
  	•	SN: 숫자
  ```

- `score`(default): 해당 단어의 우선순위를 나타내는 점수로, 높을수록 형태소 분석 시 해당 단어가 더 자주 선택된다.

  특정 단어가 자주 사용되는 도메인에서는 score 값을 높여 그 단어가 분석 시 우선적으로 선택되도록 설정할 수 있다.

- `orig_word`: 추가할 형태소의 원본 형태소.

  추가할 형태소가 특정 형태소의 변이형인 경우 이 인자로 원본 형태소를 넘겨줄 수 있으며, `orig_word`가 주어진 경우 현재 사전 내에 `orig_word`/`tag` 조합의 형태소가 반드시 존재해야 하며, 그렇지 않으면 `ValueError` 예외를 발생시킨다.

- `user_value`: 추가할 형태소의 사용자 지정값. 이 값은 형태소 분석 결과를 담는 `Token` 클래스의 `Token.user_value`값에 반영된다. (형태소 분석 출력 시 같이 담기게 될 meta data)

  만약 `{'tag':'SPECIAL'}`와 같이 dict형태로 'tag'인 key를 제공하는 경우, 형태소 분석 결과의 tag값이 SPECIAL로 덮어씌워져서 출력된다.



#### tokenize

Kiwi morpheme analysis에서 text를 형태소 단위로 나누고 각 형태소에 품사 태그를 부여하는 method

```python
text = "오늘 날씨가 매우 좋다."
tokens = kiwi.tokenize(text)

# 분석 결과 출력
for token in tokens:
    print(token)
    print(f"형태소: {token.form}, 품사: {token.tag}, 시작 위치: {token.start}, 종료 위치: {token.end}\n")
   
user_value = token.user_value		# add_user_word 에서 user_value 값으로 넣은 데이터에 접근할 수 있다.
```

```
('오늘', 'NNG', 0, 2)
형태소: 오늘, 품사: NNG, 시작 위치: 0, 종료 위치: 2

('날씨', 'NNG', 3, 5)
형태소: 날씨, 품사: NNG, 시작 위치: 3, 종료 위치: 5

('가', 'JKS', 5, 6)
형태소: 가, 품사: JKS, 시작 위치: 5, 종료 위치: 6

('매우', 'MAG', 7, 9)
형태소: 매우, 품사: MAG, 시작 위치: 7, 종료 위치: 9

('좋다', 'VA', 10, 12)
형태소: 좋다, 품사: VA, 시작 위치: 10, 종료 위치: 12

('.', 'SF', 12, 13)
형태소: ., 품사: SF, 시작 위치: 12, 종료 위치: 13
```

반환 값

- **형태소(단어)**: 의미를 가진 최소 단위인 형태소 자체.
- **품사 태그**: 해당 형태소의 품사 정보.
- **시작 위치**: 형태소가 입력 텍스트에서 시작되는 위치 인덱스.
- **종료 위치**: 형태소가 입력 텍스트에서 끝나는 위치 인덱스.



#### join

Kiwi 형태소 분석기로 분석한 형태소들을 하나의 문장으로 다시 합치는 기능으로, kiwi.tokenize로 분리된 morpheme 분석 결과를 원래 문장 형태로 복원할 때 유용하게 사용된다.

```python
# 형태소 분석 수행
text = "오늘 날씨가 매우 좋다."
tokens = kiwi.tokenize(text)

# 분석된 형태소를 하나의 문장으로 합치기
joined_text = kiwi.join(tokens, lm_search = False)

print(joined_text)
```

- `tokens`: 합치고자 하는 형태소

- `lm_search`(default = False): 언어 model 검색 여부를 설정 

  `lm_search=True`로 설정하면 언어 모델을 사용하여 결합 과정을 보다 자연스럽게 만든다.

용도

- **형태소 분석 후 문장 복원**: 텍스트에서 특정 단어를 변환하거나 제거한 후, 다시 자연스러운 문장으로 합쳐야 할 때 kiwi.join을 사용할 수 있다.

- **자연어 처리 파이프라인**: 형태소 분석 후 일부 형태소를 처리한 뒤, 문장 형태로 다시 출력해야 하는 경우가 있다. 

  예를 들어, 키워드 추출 후 복원된 문장을 출력할 때 유용하다.



#### space

입력 텍스트에서 띄어쓰기를 교정한다.

```python
from kiwipiepy import Kiwi

kiwi = Kiwi()
text = "오늘 날씨가 매우 좋다."
refine_space = kiwi.space("오늘날씨가매우좋다.", reset_whitespace = False)			# 붙어 있는 단어를 띄어쓰는 교정 위주로 수행
print(f"refine_space: {refine_space}")
refine_space = kiwi.space("오 늘    날 씨 가    매우    좋 다.", reset_whitespace = True)		# 이미 띄어쓰기된 부분을 붙이는 교정도 적극적으로 수행
print(f"refine_space: {refine_space}")
```

- `reset_whitespace`(default = False)

  False:   붙어 있는 단어를 띄어쓰는 교정 위주로 수행

  True: 이미 띄어쓰기된 부분을 붙이는 교정도 적극적으로 수행



#### split_into_sents

텍스트를 문장 단위로 분리하고 각 문장의 위치와 형태소 분석 정보를 제공하는 동작을 수행한다.

```python
from kiwipiepy import Kiwi

kiwi = Kiwi()
text = "오늘은 날씨가 좋다. 내일은 비가 온다."		# 여러 문장 입력

# 문장 분리
sentences = kiwi.split_into_sents(text, return_tokens=True)

# 결과 출력
for sentence in sentences:
    print(f"문장: {sentence.text}, 시작: {sentence.start}, 종료: {sentence.end}")
    if sentence.tokens:
        print("형태소 분석 결과:", [(token.form, token.tag) for token in sentence.tokens])
```

```
문장: 오늘은 날씨가 좋다., 시작: 0, 종료: 11
형태소 분석 결과: [('오늘', 'NNG'), ('은', 'JX'), ('날씨', 'NNG'), ('가', 'JKS'), ('좋', 'VA'), ('다', 'EF'), ('.', 'SF')]
문장: 내일은 비가 온다., 시작: 12, 종료: 22
형태소 분석 결과: [('내일', 'NNG'), ('은', 'JX'), ('비', 'NNG'), ('가', 'JKS'), ('오', 'VV'), ('ᆫ다', 'EF'), ('.', 'SF')]
```

- `text`: 문장으로 분리할 전체 text 문자열
- `return_tokens` (bool, defaut = False): 분리된 각 문장의 morpheme analysis 결과를 함께 return할지 여부를 설정





### Others

#### `difflib.SequenceMatcher` 

두 문장 간 비교시 사용

두 개의 문자열이나 시퀀스 간의 유사성을 비교하고, 차이점을 찾거나 유사도를 계산하는 데 사용되는 Python 표준 라이브러리



**예시 code**

```python
import difflib

# 두 문자열 비교
str1 = "apple pie"
str2 = "apple pie with cream"

# 공백을 불필요한 문자로 지정하는 isjunk 함수
isjunk = lambda x: x in " "

# SequenceMatcher 객체 생성
matcher = difflib.SequenceMatcher(isjunk=isjunk, str1, str2)
```

- `isjunk`(default = None): “불필요한 문자”로 간주되는 요소를 지정할 수 있는 함수

  예를 들어, 공백이나 구두점과 같이 비교에서 중요하지 않다고 판단되는 문자를 필터링할 수 있다.

  일반적으로 None을 사용



##### ratio

두 문자열 또는 시퀀스의 유사도를 0.0에서 1.0 사이의 값으로 반환한다.  ( 별도의 input parameter 없음)

```python
import difflib

# 문자열 비교
matcher = difflib.SequenceMatcher(None, "apple pie", "apple pie with cream")
print(matcher.ratio())  # 두 문자열의 유사도 비율 출력
```



##### **get_opcodes**

 두 시퀀스의 차이점과 일치하는 부분을 상세하게 분석해준다.  ( 별도의 input parameter 없음)

```python
import difflib

matcher = difflib.SequenceMatcher(None, "apple pie", "apple pie with cream")
for tag, i1, i2, j1, j2 in matcher.get_opcodes():
    print(f"{tag}: a[{i1}:{i2}] -> b[{j1}:{j2}]")
```

```
equal: a[0:9] -> b[0:9]
insert: a[9:9] -> b[9:20]
```

**출력 형식**: [('tag', i1, i2, j1, j2), ...] 형태로, i1:i2는 첫 번째 시퀀스, j1:j2는 두 번째 시퀀스의 비교 범위를 나타낸다.

- `tag`: 두 시퀀스 간의 차이점을 나타낸다.

  Tag 종류

  - "replace": 두 시퀀스에서 교체된 부분
  - "delete": 첫 번째 시퀀스에서 제거된 부분
  - "insert": 첫 번째 시퀀스에 추가된 부분
  - "equal": 두 시퀀스에서 일치하는 부분

  

