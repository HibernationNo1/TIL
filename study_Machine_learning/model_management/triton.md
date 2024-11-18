## Triton Inference Server

NVIDIA에서 개발한 open source model inference server로, 다양한 machin learning 및 deep learning modelf을 **효율적이고 확장 가능하게 배포**할 수 있도록 설계되었다. 

Triton은 model을 여러 framework와 hardware 환경에서 쉽게 inference를 진행할 수 있도록 하며, cloud 및 edge 환경에서 대규모 inference 작업을 효율적으로 수행할 수 있도록 지원한다.

- **다양한 프레임워크 지원**

  PyTorch, TensorFlow, TensorRT, ONNX, Python, XGBoost 등의 다양한 프레임워크 모델을 지원한다.

  이를 통해 하나의 서버에서 여러 프레임워크 모델을 동시에 배포할 수 있다.

  > 동일한 인프라에서 PyTorch 기반의 NLP 모델과 TensorFlow 기반의 이미지 분류 모델을 함께 서비스할 수 있음

- **고성능 최적화 및 배치 처리**

  자동 배치 기능을 제공하여, 단일 요청뿐만 아니라 여러 요청을 한 번에 묶어 처리함으로써 추론 성능을 극대화할 수 있다.

  GPU 및 CPU를 모두 지원하며, TensorRT와 같은 최적화 엔진을 사용하여 GPU에서 매우 빠른 속도로 추론을 수행할 수 있다.

- **동적 모델 관리**

  Triton은 서버가 실행 중일 때 모델을 동적으로 추가하거나 제거할 수 있는 기능을 제공한다. 

  이를 통해 서버를 중단하지 않고도 새로운 모델을 배포하거나 업데이트할 수 있다.

- **다양한 배포 옵션과 확장성**

  Triton은 Docker를 통해 손쉽게 배포할 수 있으며, Kubernetes와도 통합하여 확장 가능한 추론 서비스를 구축할 수 있다.

  Google Cloud, AWS, Azure와 같은 클라우드 환경에서도 쉽게 배포할 수 있도록 지원된다.

- **HTTP/gRPC API 제공**

   HTTP와 gRPC 인터페이스를 제공하여 클라이언트 애플리케이션이 모델에 쉽게 요청을 보내고 추론 결과를 받을 수 있게 한다.

  RESTful API를 통해 모델의 배포 상태, 추론 요청, 모델 상태 등을 확인할 수 있다.

- **monitering과 logging**

  Triton은 Prometheus와 통합되어 모델의 추론 성능 및 리소스 사용량을 모니터링할 수 있다.

- **멀티 모델 및 동시 모델 실행**

  하나의 Triton 서버에서 여러 모델을 동시에 실행하고 서비스할 수 있으며, 각 모델에 대한 배치 설정과 추론 빈도를 조정할 수 있다.
  이를 통해 다양한 모델을 동시에 운영하고, 필요한 리소스를 효율적으로 관리할 수 있다.



#### install

- with docker container

  container를 사용한다면 nvidia의 [triton inference server](https://catalog.ngc.nvidia.com/orgs/nvidia/containers/tritonserver/tags) 에서 tag를 확인할 수 있다.

  - run

    ```
    docker run -it nvcr.io/nvidia/tritonserver:24.08-pyt-python-py3 /bin/bash
    ```

  - docker compose

    ```yaml
    version: '3.8'
    
    services:
      triton-server:
        image: nvcr.io/nvidia/tritonserver:24.08-pyt-python-py3
        container_name: triton_server_container
        runtime: nvidia  # GPU 사용을 위한 설정
        environment:
          - NVIDIA_VISIBLE_DEVICES=all  # 모든 GPU 사용
        ports:
          - "8000:8000"  # HTTP 포트
          - "8001:8001"  # gRPC 포트
          - "8002:8002"  # Prometheus 메트릭 포트
        volumes:
          - ./model_repository:/models  # 로컬 모델 디렉터리와 컨테이너 디렉터리 연결
        command: >
          tritonserver
          --model-repository=/models
          --allow-grpc=true
          --allow-http=true
          --allow-metrics=true
          --log-verbose=1
    ```

    반드시 command에서 tritonserver에 관한 명령어를 실행해야 한다.

    



## tritonserver command

#### --model-repository

##### with python script

Python 스크립트를 사용해 동적으로 모델을 다운로드하거나 초기화하는 방법

```shell
$ tritonserver --model-repository=<model-repository-path>
```

위와 같이 명령어 사용 시 아래와 같은 directory 구성이 이루어져야 한다.

```
path/
└── model-repository-path/        # model-repository 경로
    ├── model_name_1/     			  # model 이름 
    │	  ├── 1/								# model version 
    │	  │   └── model.py
    │	  └── config.pbtxt  	
    └── model_name_2/   			# model 이름
    	  ├── 1/
    	  │   └── model.py
    	  ├── 2/
    	  │   └── model.py    
    	  └── config.pbtxt  	    
```

- model.py 스크립트는 model version 폴더 안에 위치해야 하며

  Python backend 모델이기 때문에, model.py 내부에서 필요한 모델을 다운로드하고, 이를 Triton에서 사용하는 포맷으로 변환하거나 메모리로 로드하도록 구성해야 한다.

  - model.py script는 반드시 `TritonPythonModel` 라는 이름의 class를 정의해야 한다.
  - model version이 여러개라면 (1, 2, ...)  그 중 가장 높은 값의 dir 내부의  model.py 만 실행된다.

- model name 내부에 `config.pbtxt` 가 있어야 한다.  (없으면 해당 모델 dir은 무시된다.)

  `config.pbtxt` 파일에서 Python backend를 사용하도록 설정한다.

  ```
  backend:"python"
  ```

   이렇게 설정하면 model.py 파일이 Python backend의 진입점 역할을 하며, 이 파일 내에서 필요한 모든 초기화 작업(예: 모델 다운로드, 로드 등)을 처리할 수 있다.



##### with model file

model저장소 dir위치에 물리적인 model file을 위치시켜 모델을 직접 물리 파일로 load하는 방법

```shell
$ tritonserver --model-repository=<model-repository-path>
```

위와 같이 명령어 사용 시 아래와 같은 directory 구성이 이루어져야 한다.

```
path/
└── model-repository-path/                    			# model-repository 경로
    ├── model_name/                				# model name 이름 
        ├── config.pbtxt  								# 모델 설정 파일
        ├── [<output-labels-file> ...] 
        ├── configs/													# 모델 실행 시 추가적인 설정 파일
        	  └── [<custom-config-file> ...]
        ├── model version/              			# model version
        │  	├── [<model-definition-file> ...]
        ...		
        
```

- `config.pbtxt`: 모델에 대한 모델 구성파일로, 일부 모델의 경우 config.pbtxt가 필수이고 다른 모델의 경우 선택 사항이다.

  config.pbtxt 를 구성함에 따라 triton python client library를 사용할 때 그 구성에 따라 code를 적절하게 짜야한다.

- `configs` (dir): pbtxt 확장자 파일이 0개 이상

- `version` (dir): 모델 버전을 나타내는 숫자 dir (반드시 1개 이상 필요, 반드시 숫자)



**config.pbtxt**

```
name: "sample_model"                # 모델 이름
backend: "python"                   # 모델 백엔드
max_batch_size: 4                   # 최대 배치 크기 설정

# 입력 텐서 정의
input [
  {
    name: "TEXT"                    # 입력 텐서 이름
    data_type: TYPE_STRING          # 데이터 타입 (문자열)
    dims: [ -1 ]                    # 입력 데이터의 차원 (동적인 경우 -1)
  }
]

# 출력 텐서 정의
output [
  {
    name: "RESULT"                  # 출력 텐서 이름
    data_type: TYPE_STRING          # 데이터 타입 (문자열)
    dims: [ -1 ]                    # 출력 데이터의 차원 (동적인 경우 -1)
  }
]

# 인스턴스 그룹 (모델 복제본 개수 및 GPU 사용 설정)
instance_group [
  {
    count: 1                        # 인스턴스 수 설정 (동시에 처리할 모델 복제본)
    kind: KIND_CPU                  # 실행 장치 설정 (CPU 또는 GPU)
  }
]

# 모델 특정 파라미터
parameters {
  key: "infer_timeout"              # 추론 타임아웃 설정
  value: { string_value: "5000" }   # 타임아웃 시간 (밀리초 단위)
}

# 최적화 설정
optimization {
  input_pinned_memory: { enable: true }  # 고정된 입력 메모리 사용 설정
}
```



**명령어 사용 예시**

```
Local File System
$ tritonserver --model-repository=/path/to/model/repository ...

Google Cloud Storage
$ tritonserver --model-repository=gs://bucket/path/to/model/repository ...
```



**dir 구성 예시)**

- tensorRT

  ```
    <model-repository-path>/
      <model-name>/
        config.pbtxt
        1/
          model.plan
  ```

- ONNX

  ```
    <model-repository-path>/
      <model-name>/
        config.pbtxt
        1/
          model.onnx
  ```

  또는

  ```
    <model-repository-path>/
      <model-name>/
        config.pbtxt
        1/
          model.onnx/
             model.onnx
             <other model files>
  ```

- TorchScipt

  ```
    <model-repository-path>/
      <model-name>/
        config.pbtxt
        1/
          model.pt
  ```

  

#### --model-control-mode

model의 loading mode를 지정

- `none`: 서버 시작 시 모든 모델을 즉시 load

  - Triton이 로드할 수 없는 모델은 UNAVAILABLE로 표시되고 추론에 사용할 수 없다.
  - 서버가 실행되는 동안 모델 저장소에 대한 변경 사항은 무시된다.

- `poll`: 모델 저장소의 변경 사항을 주기적으로 확인하고 자동으로 적용

  `--repository-poll-secs` 옵션값에 0이 아 값으로 설정해야 정상적으로 활성화 됨

  - `--repository-poll-secs` 

    Triton이 모델 저장소 디렉터리를 주기적으로 확인하여 변경 사항(새로운 모델 추가, 모델 수정 또는 삭제)을 자동으로 감지하고 적용하도록 설정하는 주기(초)를 지정한다. (이 옵션은 `--model-control-mode=poll`일 때만 작동)

- `explicit`: API를 통해 명시적으로 모델을 load 또는 unload

  - load 요청

    ```shell
    curl -X POST "http://localhost:8000/v2/repository/models/{model_name}/load"
    ```

    - `8000`: HTTP 포트
    - {model_name}: load할 model의 이름.  config.pbtxt 파일에 지정된 모델 이름과 동일해야 한다.

  - unload 요청

    ```shell
    curl -X POST "http://localhost:8000/v2/repository/models/{model_name}/unload"
    ```

  - model 상태 확인

    ```shell
    curl -X GET "http://localhost:8000/v2/models/{model_name}"
    ```

  `--load-model` 옵션을 사용하면 triton 시작 시  model을 load 한 상태로 실행할 수 있다.

  - `--load-model`: Triton 서버가 시작될 때 특정 모델을 즉시 로드하도록 지정하는 option



#### --exit-on-error

이 옵션을 활성화하면 서버가 시작되거나 모델을 로드하는 과정에서 심각한 오류가 발생할 경우, 서버가 자동으로 중지된다

기본적으로 Triton은 오류가 발생해도 계속 실행되지만, --exit-on-error를 사용하면 오류 발생 시 즉시 중단되어 디버깅이나 문제 해결을 빠르게 수행할 수 있다.



#### API request

##### HTTP

- **`--allow-http`**: HTTP 요청 처리를 활성화하는 option

  `--http-port` (http 요청을 받기 위한 port명시 option)과 같이 쓰여야 한다.

##### gRPC

- **`--allow-grpc`** : grpc 요청 처리를 활성화하는 option 

  `--grpc-port` (grpc 요청을 받기 위한 port명시 option)과 같이 쓰여야 한다.

  - gRPC

    원격 프로시저 호출(Remote Procedure Call, RPC)을 위한 오픈소스 프레임워크로, Google에서 개발했다. 

    gRPC는 주로 마이크로서비스 간의 통신에서 성능을 높이고 데이터 전송을 최적화하기 위해 사용된다.

  

gRPC 예시

```python
import grpc
import numpy as np
from tritonclient.grpc import service_pb2, service_pb2_grpc

# Triton gRPC 서버 연결 설정
channel = grpc.insecure_channel('localhost:8001')
stub = service_pb2_grpc.GRPCInferenceServiceStub(channel)

# 모델 추론 요청
# 예시로, numpy 배열 데이터를 사용하여 모델에 요청을 보낼 수 있습니다.
request = service_pb2.ModelInferRequest()
request.model_name = 'my_model'
request.inputs[0].name = 'input_0'
request.inputs[0].data_type = service_pb2.DataType.TYPE_FP32
request.inputs[0].shape.extend([1, 3, 224, 224])

# 데이터를 모델의 input에 추가
request.inputs[0].contents.raw_contents = np.array(input_data, dtype=np.float32).tobytes()

# 요청 전송
response = stub.ModelInfer(request)
```



**prometheus**

-  **`--allow-metrics`**: prometheus 요청을 활성화하는 option

  `--metrics-port`: Prometheus 메트릭 서버가 사용할 포트를 설정한다. (default = 8002)

Prometheus의 prometheus.yml 설정 파일에 Triton 서버의 메트릭 엔드포인트를 추가하면 된다.

```yaml
scrape_configs:
  - job_name: 'triton'
    static_configs:
      - targets: ['localhost:8002']  # Triton 서버가 실행되는 호스트와 포트
```





## Triton python lib

### tritonclient 

#### httpclinet, grpcclinet

Triton Inference Server에 HTTP(gRPC)를 통해 요청을 보내기 위해 사용하는 Python 클라이언트 library

```python
import tritonclient.http as httpclinet
import tritonclient.grpc as grpcclinet
```



##### InferInput

모델 추론을 위해 클라이언트가 제공해야 하는 입력 데이터의 속성을 정의한다.

```python
input_object = httpclinet.InferInput(name = 'input_tensor_name', shape = [1, 3, 224, 224], datatype = "FP32")
```

```python
input_object = grpcclinet.InferInput(name = key, shape = shape, datatype = datatype)
```

- `name`: 입력 tensor의 이름 결정.  triton server에 load된 model의 input tensor name과 동일해야 한다.
  - input tensor name:  어떤 목적으로 입력되는 데이터인지 명시한 값
- `shape`: 입력 tensor의 shape결정
- `datatype`: 입력 tensor의 type결정

이러한 정보는 tritonserver 명령어 중 --model-repository  의 경로에 있는 model name(dir) 의 내부 파일 중 `config.pbtxt `에 정의되어 있어야 한다.

```
backend: "python"
max_batch_size: 0
input [
    {
        name: "TEXT"
        data_type: TYPE_STRING
        dims: [ -1 ]
    }
]
output [
    {
        name: "RESULT"
        data_type: TYPE_STRING
        dims: [ -1 ]
    }
]
```

위와 같다면 `name`은 'TEXT' 라는 값이,  `shape`은 자유롭게, `datatype`은  'BYTES' 값이 할당되어야 한다.



###### set_data_from_numpy

NumPy 형식의 데이터를 입력으로 넣기 위해 적절히 변환하는 method

```
input_list = list()
input_object = httpclinet.InferInput(name="input_name", shape=(1, 224, 224, 3), datatype="FP32")
input_list.append(input_object.set_data_from_numpy(np.asarray(data, dtype=object))
```

- `np.asarray`: 데이터를 numpy 형식으로 변환한다.

- `dtype=object`: 배열이 각각의 요소를 개별 객체로 저장한다. 

  문자열과 같은 객체를 포함하거나, 요소마다 길이가 다른 리스트와 같이 일반적인 NumPy 배열로 저장하기 어려운 데이터를 배열 내에 담을 수 있다.



###### with `config.pbtxt`

- `config.pbtxt`의  `data_type` 에 따른 httpclinet.InferInput 의 `datatype` 값 페어

  Triton data_type	-	grpcclient.InferInput의 datatype 값

  ```
  TYPE_BOOL				-		"BOOL"
  TYPE_UINT8			-		"UINT8"
  TYPE_UINT16			-		"UINT16"
  TYPE_UINT32			-		"UINT32"
  TYPE_UINT64			-		"UINT64"
  TYPE_INT8				-		"INT8"
  TYPE_INT16			-		"INT16"
  TYPE_INT32			-		"INT32"
  TYPE_INT64			-		"INT64"
  TYPE_FP16				-		"FP16"
  TYPE_FP32				-		"FP32"
  TYPE_FP64				-		"FP64"
  TYPE_STRING			-		"BYTES"
  ```

- batch size 가 4인 경우의 예시

  ```python
  import tritonclient.http as httpclient
  import numpy as np
  
  # Triton 서버에 연결
  url = "localhost:8000"  # Triton 서버 URL
  model_name = "your_model_name"  # 모델 이름
  model_version = "1"  # 모델 버전
  client = httpclient.InferenceServerClient(url=url)
  
  # 배치 입력 데이터
  texts = ["input text 1", "input text 2", "input text 3", "input text 4"]  # 4개의 텍스트 입력
  batch_size = len(texts)
  
  # InferInput 설정
  input_data = httpclient.InferInput(name="TEXT", shape=[batch_size], datatype="BYTES")
  input_data.set_data_from_numpy(np.array(texts, dtype=object))  # 문자열은 object dtype으로 변환
  
  # InferRequestedOutput 설정
  output_data = httpclient.InferRequestedOutput(name="RESULT")
  
  # 추론 요청
  response = client.infer(
      model_name=model_name,
      model_version=model_version,
      inputs=[input_data],
      outputs=[output_data]
  )
  
  # 결과 추출
  results = response.as_numpy("RESULT")
  print("Batch Inference Results:", results)
  ```

- input 이 2개 이상인 경우 예시

  ```
  backend: "python"
  max_batch_size: 0
  input [
      {
          name: "TEXT_1"
          data_type: TYPE_STRING
          dims: [ -1 ]
      },
      {
          name: "TEXT_2"
          data_type: TYPE_STRING
          dims: [ -1 ]
      },
      {
          name: "TEXT_3"
          data_type: TYPE_STRING
          dims: [ -1 ]
      }
  ]
  output [
      {
          name: "RESULT_1"
          data_type: TYPE_STRING
          dims: [ -1 ]
      },
      {
          name: "RESULT_2"
          data_type: TYPE_STRING
          dims: [ -1 ]
      }
  ]
  ```

  python code

  ```python
  import tritonclient.http as httpclient
  import numpy as np
  
  # Triton server URL
  url = "localhost:8000"
  model_name = "your_model_name"
  model_version = "1"
  
  # Create InferenceServerClient instance
  client = httpclient.InferenceServerClient(url=url, verbose=False)
  
  # Define input data
  data_1 = np.array(["sample text 1"], dtype=object)
  data_2 = np.array(["sample text 2"], dtype=object)
  data_3 = np.array(["sample text 3"], dtype=object)
  
  # Define InferInput for each input
  input_1 = httpclient.InferInput(name="TEXT_1", shape=data_1.shape, datatype="BYTES")
  input_2 = httpclient.InferInput(name="TEXT_2", shape=data_2.shape, datatype="BYTES")
  input_3 = httpclient.InferInput(name="TEXT_3", shape=data_3.shape, datatype="BYTES")
  
  # Set data for each input
  input_1.set_data_from_numpy(data_1)
  input_2.set_data_from_numpy(data_2)
  input_3.set_data_from_numpy(data_3)
  
  # Create output requests for expected output tensors
  output_1 = httpclient.InferRequestedOutput(name="RESULT_1")
  output_2 = httpclient.InferRequestedOutput(name="RESULT_2")
  
  # Send inference request
  response = client.infer(
      model_name=model_name,
      model_version=model_version,
      inputs=[input_1, input_2, input_3],
      outputs=[output_1, output_2]
  )
  
  # Access results for each requested output
  result_1 = response.as_numpy("RESULT_1")
  result_2 = response.as_numpy("RESULT_2")
  
  print("Result 1:", result_1)
  print("Result 2:", result_2)
  ```

만일 input에 없는 input tensor를 input으로 할당한다면 자연스럽게 무시된다.

만일 input에 있는 input tensor를 input으로 할당하지 않는다면 error가 발생한다.



##### InferRequestedOutput

추론 요청에서 클라이언트가 원하는 출력 텐서의 정보를 정의한다.

출력 텐서의 이름과 반환될 데이터 형식 등을 지정하는 데 사용된다.

```python
output_list = list()
output_list.append(httpclinet.InferRequestedOutput(name=output_name, binary_data=False))
```

```python
output_list = list()
output_list.append(grpcclinet.InferRequestedOutput(name=output_name, binary_data=False))
```

- `name`: 반환될 출력 텐서의 이름.  triton server에 load된 model의 output tensor name과 동일해야 한다.

- `binary_data`: True로 설정하면 출력이 이진 형식으로 반환되어 네트워크 전송을 최적화할 수있다. 

  기본값은 False로, 텍스트 형식으로 반환한다.

- `class_count`: 분류 모델에 적용되며, 상위 k개의 결과만 반환하고자 할 때 사용된다. 

  예를 들어, class_count=5로 설정하면 상위 5개의 분류 결과가 반환된다.



##### InferenceServerClient

Triton 서버와 상호작용하는 주요 클라이언트 객체

서버에 연결하고 추론을 수행하며 서버의 상태와 모델의 상태를 확인하는 데 사용된다.

```python
http_client = httpclinet.InferenceServerClient(url = requset_url, verbose = False)
grpc_client = grpcclinet.InferenceServerClient(url = requset_url, verbose = False)
```

- `verbose`: True로 설정 시 클라이언트가 요청과 응답에 대한 상세한 로그를 출력
- `ssl`: server가 HTTPS로 설정된 경우 True로 지정해 클라이언트가 SSL 연결을 사용하도록 설정
- connection_timeout, `network_timeout`: 서버와의 연결 대기 시간 및 네트워크 대기 시간을 설정하여 요청의 응답 시간을 조절할 수 있다.



###### is_model_ready

```python
http_client.is_model_ready(model_name=, model_version = None, timeout)
```

- model_name: 확인하려는 모델의 이름을 문자열로 입력. 이 이름은 Triton 서버에 로드된 모델의 이름과 일치해야 한다.
- model_version: 특정 버전의 모델을 확인할 때 사용한다. 기본값은 None이며, 이 경우 서버에 로드된 최신 버전이 사용된다.
- timeout: (선택적) 모델 준비 상태를 확인하는 데 대기하는 최대 시간을 지정한다. 기본값은 서버 설정에 따라 무제한일 수 있으며, 필요에 따라 조정할 수 있다.



###### start_stream, async_stream_infer

**gRPC 클라이언트**(즉, grpcclient)에서만 제공되는 기능으로, 스트리밍 방식으로 서버와 비동기적 상호작용을 지원한다.

```python
from functools import partial
import queue

class UserData:
    def __init__(self):
        self._completed_requests = queue.Queue()
  
def callback(user_data, result, error):
    if error:
        user_data._completed_requests.put(error)
    else:
        user_data._completed_requests.put(result)
        
...

  with grpc_client as triton_client:
      triton_client.start_stream(callback=partial(callback, user_data))
      request_id = "0"
      triton_client.async_stream_infer(
          model_name=model_name,
          inputs=placeholder_list,
          request_id=request_id,
          outputs=output_list
          )
      # while recv_count < expected_count:
      response = user_data._completed_requests.get()
```

- start_stream

  스트리밍 세션을 시작하여 서버와 지속적으로 연결된 상태에서 여러 요청을 보낼 수 있다.

  - callback: 서버에서 비동기적으로 전송된 추론 결과를 처리하는 함수로, 각 스트리밍 요청의 응답이 수신될 때마다 자동으로 호출된다.

    기본 형태

    ```python
    def callback(result, error):
        if error:
            print("Inference error:", error)
        else:
            print("Inference result:", result)
    ```

    allback을 통해 실시간으로 각 요청의 결과를 처리하거나 로깅할 수 있으며, 특히 대량의 데이터를 비동기 방식으로 처리할 때 유용하다.

- async_stream_infer

  비동기 방식으로 추론 요청을 스트리밍 세션에 보낸다. 이 메서드를 사용하여 서버와 실시간 데이터 스트림을 주고받을 수 있다.





###### infer

**HTTP 클라이언트**(즉, httpclient)에 기본 제공되는 기능으로, 동기적 방식으로 서버에 추론 요청을 보낸다.

```python
response = http_client.infer(
    model_name=model_name,
    model_version=model_version, 
    inputs=inputs_list,
    outputs=output_list
)
```

- `model_name`:  triton server에 load된 모델의 입력 이름과 일치해야 한다.
- `model_version`: triton server에 load된 모델 중 사용하고자 하는 model version을 명시한다.
- `inputs`: 각각의 객체가 `httpclinet.InferInput`의 객체로 `set_data_from_numpy`를 호출하여 데이터를 할당한 값의 list를 할당한다.
- `outputs`: 각각의 객체가 `httpclinet.InferRequestedOutput`의 반환 객체의 list를 할당한다.



**as_numpy**

 output에 대한 추론 결과를 numpy 배열로 반환한다.

```
result = response.as_numpy("output_name")
print(result)  # numpy 배열로 출력된 추론 결과 확인
```

- output_name: output tensor name



### triton_python_backend_utils

NVIDIA Triton Inference Server의 Python 백엔드에서 사용할 수 있는 유틸리티 모듈로, Python 스크립트에서 Triton 서버의 요청을 처리하고 응답을 생성하는 데 필요한 다양한 기능을 제공한다.

```python
import triton_python_backend_utils as pb_utils
```

#### get_input_tensor_by_name

특정 input tensor를 이름을 기준으로 가져오기 위한 함수. (아래 예시)

```python
class TritonPythonModel:

    def execute(self, requests):
        responses = []
        for request in requests:
            # 이름이 "INPUT"인 입력 텐서를 가져오기
            input_tensor = pb_utils.get_input_tensor_by_name(request, "INPUT")
            input_data = input_tensor.as_numpy()  # NumPy 배열로 변환

            # 예측 작업 수행
            output_data = input_data * 2  # 예시: 입력 데이터를 두 배로 반환

            # 출력 텐서 생성    output_data 를 출력으로 만들기 위해 tensor변환
            # name: 모델의 config.pbtxt 파일에 정의된 출력 이름과 일치해야 된다.
            # output_data: numpy 형태로 전달되어야 한다.
            output_tensor = pb_utils.Tensor("OUTPUT", output_data)		 
            responses.append(pb_utils.InferenceResponse([output_tensor]))		# list로 전달

        return responses
```



#### Tenser

모델의 출력 또는 입력으로 사용할 수 있는 tensor를 정의하는 클래스 (위 예시 참고)



#### InferenceResponse

모델 추론 응답을 생성하기 위한 클래스로, 하나 이상의 출력 텐서(pb_utils.Tensor)를 포함하여 추론의 최종 결과를 Triton 서버에 반환한다. (위 예시 참고)
