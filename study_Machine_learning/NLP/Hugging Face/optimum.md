# Hugging Face Optimum

**Hugging Face Optimum**은 Hugging Face Transformers 모델을 다양한 하드웨어와 추론 가속 라이브러리에서 쉽게 최적화하고 실행하기 위한 툴킷이다. 
Optimum은 ONNX Runtime, TensorRT, OpenVINO, Habana Gaudi, Intel Neural Compressor 등 여러 가속화 기술과 통합되어, 모델의 추론 속도를 높이고 효율성을 극대화할 수 있도록 지원한다.

**주요 특징**

- **멀티-백엔드 지원**

  다양한 추론 백엔드와 하드웨어 플랫폼을 지원하며, 각각의 플랫폼에 최적화된 실행을 가능하게 한다.

  예: ONNX Runtime, TensorRT, OpenVINO, Habana Gaudi, Intel Neural Compressor.

- **Transformers와 통합**

  Hugging Face Transformers 모델을 기반으로 한 워크플로우를 자연스럽게 통합할 수 있도록 설계되었기 때문에 Transformers 모델을 쉽게 변환하고 최적화할 수 있다.

- **모델 변환 및 최적화**

  PyTorch 또는 TensorFlow 모델을 ONNX 형식으로 변환하여 추론 속도를 개선할 수 있다.

  양자화, 프루닝(pruning) 등의 기술을 통해 모델 크기와 실행 시간을 줄일 수 있다.

- **사용 편의성**

  Transformers API와 유사한 고수준 인터페이스를 제공하여 기존 Hugging Face 워크플로우와 쉽게 통합할 수 있다. 이 덕분에 사용자는 코드의 큰 변경 없이 최적화된 모델을 실행할 수 있다.

  

## Optimum

### onnxruntime

Hugging Face의 Optimum 라이브러리에서 제공하는 **ONNX Runtime** 관련 기능에 접근할 수 있도록 해주는 module로,  Hugging Face 모델을 ONNX 형식으로 변환하여, ONNX Runtime에서 **빠르고 최적화된 추론**을 실행할 수 있게 한다.



#### ORTModelForSequenceClassification

ONNX로 변환된 **텍스트 분류** 모델을 로드하고 추론할 수 있도록 지원한다.

> Transformers의 AutoModelForSequenceClassification과 유사한 사용법을 제공

```python
from optimum.onnxruntime import ORTModelForSequenceClassification
from transformers import AutoTokenizer

# ONNX 형식으로 저장된 모델과 토크나이저 로드
model = ORTModelForSequenceClassification.from_pretrained("path/to/onnx/model")
tokenizer = AutoTokenizer.from_pretrained("path/to/tokenizer")

# 텍스트 데이터 전처리 및 모델 추론
inputs = tokenizer("Sample text for classification", return_tensors="pt")
outputs = model(**inputs)
print(outputs)
```

