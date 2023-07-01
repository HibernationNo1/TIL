# TorchServe

[github](https://github.com/pytorch/serve)

serving하고자 하는 model을 TorchServe에서 요구하는 방식으로 변환하고, 이를 기반으로 server를 실행하면 model과 user간의 API소통이 이루어지도록 하는 기술이다.

> runtime에서 모델을 manage하기 위한 다양한 기능의 API를 제공한다. 즉 torchserve를 실행시켜놓으면 모델 파라미터 외에 배포 관련 기본적인 설정은 실시간 api call을 통해 가능한 것이다.

TorchServe를 통해 model을 serving하기 위해서는 아래의 file들이 필요하다.

- `.mar` mar format의 file이다. 해당 file은 아래의 학습된 model, handler file 등을 포함하여 TorchServe에서 요구하는 방식으로 변환한 것이다.

  `.mar`을 만들기 위해 필요한 필수 file들

  - `model.pth` : 학습이 완료된 model file. 

    pytorch를 통해 학습되고 `torch.save`로 저장된 model file이다.

  - `handler.py` : torchserve가 구동되는 동안 API 통신에 의한 data를 받고 처리하는 code이다.

- `config.prosperties`

  torchserve가 구동되는 동안 사용될 port및 여러 설정들을 사용자가 결정할 수 있다.



**install**

1. java설치

   ```
   $ sudo apt-get update
   $ sudo apt-get install openjdk-11-jre
   ```

2. install

   ```
   $ pip install torchserve
   ```

   





## .mar

model을 TorchServe에서 요구하는 방식으로 변환한 file이다.



### handler.py

model을 serving하기 위해 TorchServe가 이해할 수 있는 형태로 정의하게 도와준다. `handler.py`가 정의되어 있어야 model을 동작시킬 수 있다.

`handler.py`는 data가 input으로 들어올 때 전처리, inference, 후처리에 대해 정의해놓은 파일이다.

기본 제공 [hendler](https://github.com/pytorch/serve/tree/master/ts/torch_handler)



handler 파일 내부에서 특정 class가 정의되어 있어야 한다.(class 이름에 대한 규정은 없다.)

```python
class CustomHandler():
    
    def __init__(self):
        pass

    def initialize(self, context):  
    	pass
    
    def postprocess(self, result, classes):
    	pass
    
    def inference(self, data, *args, **kwargs):
        pass
    
    def preprocess(self, data):
    	pass
    
        
    def handle(self, data, context):    
        
        return [response]
```

기본적으로 `__init__`, `initialize`, `preprocess`, `inference`, `postprocess`, `handle` 이라는 method가 정의되어 있어야 한다.



#### initialize

TorchServe가 실행될 때 처음으로 실행되는 method다.

- model을 load한다.
- model에 필요한 추가 resource를 load한다.
- 사용자 정의를 설정한다.

예시

```
    def initialize(self, context):        
        self.manifest, self.properties, self.cfg = self._get_properties(context, CONFIG_PATH)

        # set device resource
        if torch.cuda.is_available() and self.properties.gpu_id is not None:
            self.map_location = "cuda"
            device = self.map_location + ":" + str(self.properties.gpu_id)     
        else:
            self.map_location = "cpu"
            device = self.map_location
        if self.cfg.device != device:
            raise ValueError(f"Device setting are not same between config file and properties.\n"
                             f"       cfg.device: {self.cfg.device},     properties: {device}")
        self.device = self.cfg.device


    def _load_model(self, model_pth_path):
        """ Load the model from the given model path.
        """
        model_format = model_pth_path.split(".")[-1]
        if model_format != "pth":
            raise ValueError(f"The server only for .pth format model, but got {model_format}")

        model = build_detector(self.cfg, model_pth_path, device = self.device, logger = logger)
        model = build_dp(model = model, 
                         cfg = self.cfg,
                         device = self.device,
                         classes = model.CLASSES)
        
        return model
        
        
	def _get_properties(self, context, config_path):
        """ Load config data to build model and run inference.
        """
        manifest = Config(context.manifest)          # get data from MANIFEST.json in .mar file
        properties = Config(context.system_properties)      # get data from config.properties

        if not osp.isfile(config_path):
            raise RuntimeError("Missing the config.py file")
        cfg = Config.fromfile(config_path)
        return manifest, properties, cfg
        
```



**context**

매개변수인 context는 handler내에서 model과 관련된 설정과 metadata에 접근할 수 있도록 한다.

context는 TorchServe가 제공하는 것으로, initialize가 실행될 때 자동으로 전달된다.

- `context.manifest`: model의 metadata를 포함하는 dict로,`.mar`file의 `MANIFEST.json`으로부터 load된다.

  `.mar` file을 만들 때 `extra-file` 의 option에 `MANIFEST.json`를 가리키면 된다.

  > `MANIFEST.json`는 torch-model-archiver에 의해 자동으로 생성되며 아래와 같은 구조로 만들어진다.
  >
  > ```
  > {
  > "runtime": "python",
  > "model": {
  >  "modelName": "my_model",
  >  "serializedFile": "model.pth",
  >  "handler": "my_handler.py",
  >  "modelFile": "model.py",
  >  "exportVersion": "1.0"
  > },
  > "implementation_version": "1.0"
  > }
  > ```

- `context.system_properties`: system속성을 포함하는 dict로, TorchServe의 구성, runtime설정 및 환경 변수에 관한 정보를 제공한다.

  이러한 구성은 `config.properties`라는 file을 정의할 때 설정할 수 있다.

- `context.model_dir`: `.mar`이 추출된 dir의 경로를 나타낸다. 이를 통해 `model.pth`와 추가 resource를 load할 수 있다.

  > 보통은 system_properties를 통해 경로를 할당한다.
  >
  > ```python
  > properties = context.system_properties
  > model_dir = properties.get("model_dir")
  > ```

- `context.metrics`: model의 성능 metrics를 수집하는데 사용될 수 있는 metic객체를 제공한다.

 

#### handle

Client로부터 input data를 포함하고 있는 API를 수신했을 때 동작하며, model을 사용하여 inference를 수행하고 결과를 return한다.

- data를 model의 input으로 사용하기 위해 preprocessing을 진행한다.

- model를 통해 inference를 진행한다.

- inference result에 post-processing을 통해 최종 결과를 생성한다.

- 최종 결과를 return한다.

  **return type은 `list`이다.**

예시

```python
    def handle(self, data, context):               
        model = self.model
        if not next(model.parameters()).is_cuda:
            RuntimeError(f"modules must be is_cuda, but is not")
            
            
        start_time = time.time()
        
        metrics = context.metrics
                
        stop_time = time.time()
        metrics.add_time(
            "HandlerTime", round((stop_time - start_time) * 1000, 2), None, "ms"
        )
        
        data = self.preprocess(data)
        result = self.inference(data)
        board_info = self.postprocess(result, classes = model.CLASSES)

        if board_info is None:
            response = dict(response = 'None')
        else:
            response = dict(response = board_info)
        
    return [response]		# type: list


    def preprocess(self, data):
        body = data[0]['body']
        if request_key not in body.keys():
            RuntimeError(f"The body of request not match the input")
        data = body[request_key]
        image = base64.b64decode(data)     # <class 'bytes'>
        
        if not isinstance(image, (bytearray, bytes)):
            RuntimeError(f"The type of decoded data is not `bytearray` or `bytes`"
            f"              type(data): {type(image)}")
        
        pil_image = Image.open(io.BytesIO(image))
        numpy_image = np.array(pil_image)
        data = self.image_processing(numpy_image)
        
        data = collate([data], samples_per_gpu=1)

        data['img_metas'] = [img_metas.data[0] for img_metas in data['img_metas']]
        data['img'] = [img.data[0] for img in data['img']]
        
        data = parallel_scatter(data, [self.device])[0]
        
        return data
    
    
    
    def inference(self, data, *args, **kwargs):
        if 'img_metas' and 'img' not in data.keys():
            RuntimeError(f"The input data to model must have keys named 'img_meta' and 'img'"
            f"              data.keys() : {data.keys()}")
        with torch.no_grad():
            results = self.model(return_loss=False, rescal = False, **data)        # call model.forward
        result = results[0]    
        
        return result
    
    
    def postprocess(self, result, classes):
        bboxes, labels, _ = parse_inference_result(result)  # _: mask
        
        get_info_instance = Get_info(bboxes, labels, classes, score_thr = self.cfg.get('show_score_thr', 0.5))
        board_info = get_info_instance.get_board_info()
        if len(board_info) == 0: return None
        return board_info
    
    def inference(self, data, *args, **kwargs):
        if 'img_metas' and 'img' not in data.keys():
            RuntimeError(f"The input data to model must have keys named 'img_meta' and 'img'"
            f"              data.keys() : {data.keys()}")
        with torch.no_grad():
            results = self.model(return_loss=False, rescal = False, **data)        # call model.forward
        result = results[0]    
        
        return result
    
```





### archiver

TorchServe Model Archive(`.mar`)와 를 생성한다

**torch-model-archiver**는 PyTorch model을 TorchServe에서 serving하기 위해 Archive로 packaging하는 도구이다.

- install

  ```
  $ pip install torch-model-archiver
  ```

- 명령어

  아래의 dir map인 경우

  ```
  v1
  	extra
  		sub_module(dir)
  		config.py	
  		requirements.txt
  	handler.py
  	model.pth
  ```

  

  ```
  $ torch-model-archiver \
  	--model-name pipeline \
  	--version 0.1 \
  	--serialized-file pipeline.pth \
  	--extra-files extra \
  	--handler handler.py \
  	--runtime python 
  ```
  
  > `--model-name`에 할당한 이름에 `.mar`라는 format으로 file이 만들어진다.
  
  - `--model-name`: model의 이름을 지정. 지정된 이름은 추후 TorchServe에서 model을 참조할 때 사용된다.
  
  - `--version`: model의 version을 지정.  지정된 version은 추후 model 관리에 사용된다.
  
  - `--model-file`: model을 정의하는 python file의 path를 지정한다. 해당 file은 model이 정의된 class를 포함해야 한다.
  
    만일 model이 여러 file에 나뉘어 정의되어 있다면 해당 model을 하나의 module로 정의하여 dir에 보관하고 `--extra-files`에 해당 module을 포함하자.
  
    `--model-file`은 단일 file만 지정할 수 있다.
  
  - `--serialized-file`: 직렬화된 model file(일반적으로 `.pth` or `.pt` format)의 경로를 지정한다. 
  
  - `--extra-files`: 추가 file의 경로를 지정한다. config file이나 infomation 또는 보조 code file등을 포함할 수 있다. 
  
  - `--handler`: model serving handler를 지정한다. (`hendler.py`와 같은)
  
  - `--runtime`: runtime version을 지정한다. (`python` or `python3`)
  
  - `--export-path`: 생성된 model archive file(`.mar`)이 저장될 directory를 지정한다. 
  
    default는 `.` 이다.
  
    > `hendler.py`에서 import할 modul 및 python file을 포함한다.
  
  - `--force`: 해당 option을 사용하면 이미 존재하는 archive file이 있을 경우 덮어씌운다.
  
  - 그 외

    - `--requirements-file` : **kserve를 통해 배포**할 때 pod의 환경에 library를 install하는 경우 사용된다.
  
  

### config.properties

properties는 지정할 수 있는 사용자가 torchserve에 대한 설정을 결정한다.

```
inference_address=http://0.0.0.0:8085
management_address=http://0.0.0.0:8085
metrics_address=http://0.0.0.0:8082
grpc_inference_port=7070
grpc_management_port=7071
enable_metrics_api=true
metrics_format=prometheus
config_path=extra/config
gpu_id=0
model_store=/mnt/models/model-store	# torchserve구동 시 model file의 저장 위치 지정
install_py_dep_per_model=true		# requriements.txt를 설치하기 위해
model_snapshot={"name": "startup.cfg", "modelCount": 1, "models": {"my_model": {"1.0": {"defaultVersion": true, "marName": "my_model.mar", "minWorkers": 1, "maxWorkers": 3, "batchSize": 4, "maxBatchDelay": 100, "responseTimeout": 120}}}}
```

- `install_py_dep_per_model`: kserve에 의한 배포를 진행할 때 inference를 진행할 pod에 설치할 module을 적어놓은 requirements.txt를 전달한 경우 추가





### start

`.mar`file과 `config.properites`file을 사용하여 torchserve를 구동한다.

> Torchserve의 package는 `torchserve --start`명령이 실행되는 환경속에서 작동된다.
>
> ```
> nvgpu==0.9.0
> pynvml==11.4.1
> ```
>
> GTX3060기준, Nvidia driver version : `470.182.03` 일 때 pynvml의 최신 `11.5.0` version은 호환되지 않는다. 
>
> `11.4.1`은 2021년에, `11.5.0`는 2023년 release된 version임





1. torchserve 실행

   ```
   $ torchserve --start --model-store . --models pipeline=pipeline.mar --ts-config config.properties
   ```

   - `--model-store`: `.mar`형식의 file이 있는 path

   - `--models`: 사용하고자 하는 model지정

     `model_name = model.mar` 형식으로 사용

     `--models all`으로 사용시 `model-store`내부의 모든 model을 load하려고 시도한다.

   - `--ts-config`: TorchServe의 설정을 지정하는 file의 경로 지정

3. post

   ```
   $ curl -X POST http://localhost:8085/predictions/model_name -T input.json
   ```

   - `port`: config.prosperties에서 설정한 inference port를 지정
   - `model_name`: Torchserve를 통해 배포한 model의 이름 지정
   - `-T input.json`: post를 통해 보낼 input file을 지정

   - `input.json`: example 을 download

     ```
     $ curl https://raw.githubusercontent.com/kserve/kserve/c5f8984d3151769698664c33f94412b55a12d210/docs/samples/v1beta1/torchserve/v1/imgconv/input.json -o input.json
     ```

   > image를 json으로 만드는 [code](https://github.com/kserve/kserve/tree/master/docs/samples/v1beta1/torchserve/v1/imgconv)
   >
   > request를 보낼 때 file 또는 body의 내용이 6MB를 넘기면 요청이 거부된다.
   >
   > **image를 json으로 변환 후 request를 보내는 python code**
   >
   > ```python
   > import base64
   > import json
   > import argparse
   > import os, os.path as osp
   > import cv2
   > import requests
   > 
   > URL = "http://localhost:8085/predictions/pipeline"
   > ACCEPT_MB = 5
   > class Kserve():
   >  URL = "http://127.0.0.1:8081/v1/models/pipeline:predict"
   >  headers = dict(Host = 'pipeline-test08.pipeline.svc.cluster.local')
   > 
   > 
   > # python request.py file_name.jpg --kserve
   > def parser_args():
   >  parser = argparse.ArgumentParser()
   >  parser.add_argument("filename", help="converts image to bytes array",
   >                      type=str)
   >  parser.add_argument("--kserve", help="converts image to bytes array",
   >                      action='store_true')
   > 
   >  args = parser.parse_args()
   >  return args
   > 
   > def resize_image(file_name, scale):    
   >  file_path = osp.join(os.getcwd(), file_name)
   >  if not osp.isfile(file_path):
   >      raise OSError(f"The file does not exist! \n file path: {file_path}")
   > 
   >  org_img = cv2.imread(file_path)
   >  h, w, c = org_img.shape
   > 
   >  re_h, re_w = int(h*scale), int(w*scale)
   >  re_img = cv2.resize(org_img, (re_w, re_h))
   > 
   >  print(f"Resizing from [{h}, {w}, {c}] to [{re_h}, {re_w}, {c}]")
   > 
   >  return re_img
   > 
   > 
   > def send_request_get_response(request, kserve = False):    
   >  if kserve:
   >      requests.post(Kserve.URL, json=request, headers=Kserve.headers)
   >      print(f"Send request to {Kserve.URL}")
   >  else:
   >      response = requests.post(URL, json=request)
   >      print(f"Send request to {URL}")
   > 
   >  # show response
   >  if not response.text == '':
   >      license_info = response.json()['response']
   >      if license_info is None or license_info == 'None': 
   >          print(f"License plate detection failed.")
   >          exit()
   >      print(f"License plate information")
   >      for key, value in response.json()['response'][0].items():
   >          if key in ['width', 'height', 'board_center_p']: continue
   >          print(f"	{key}: {value}")
   >  else:
   >      print("Request has been denied.")
   > 
   > 
   > def endecode_image(image_bytes):
   >  image_64_encode = base64.b64encode(image_bytes)        # encode image to base64
   >  bytes_array = image_64_encode.decode('utf-8')    # decode base64 to UTF-8 string
   >  request = {"data": bytes_array}
   >  return request
   > 
   > def get_size_reque_mbytes(request):
   >  # check size of request
   >  json_string = json.dumps(request)
   >  json_bytes = json_string.encode('utf-8')
   >  size_in_bytes = len(json_bytes)
   >  size_in_mbytes = size_in_bytes/(1024*1024)
   >  return size_in_mbytes
   > 
   > if __name__ == '__main__':
   >  args = parser_args()
   > 
   >  file_path = osp.join(os.getcwd(), args.filename)
   >  if not osp.isfile(file_path):
   >      raise RuntimeError(f"File dose not exist: {file_path}")
   > 
   >  image_file = open(file_path, 'rb')          # open binary file in read mode
   >  image_bytes = image_file.read()             # <class 'bytes'>
   > 
   >  request = endecode_image(image_bytes)
   >  size_mbytes = get_size_reque_mbytes(request)
   >  if size_mbytes > ACCEPT_MB:
   >      image_np = resize_image(args.filename, 6/size_mbytes*1)       # load image and resizing
   >      _, buffer = cv2.imencode(".jpg", image_np)          # compression in memory
   >      image_bytes = buffer.tobytes()                      # convert to `bytes`
   >      request = endecode_image(image_bytes)
   >      size_mbytes_re = get_size_reque_mbytes(request)
   >      if size_mbytes_re > ACCEPT_MB:
   >          raise RuntimeError(f"The size of the request payload too large.\n"
   >              f"              Size of the request payload: {size_mbytes_re:.3f} MB")
   > 
   >  send_request_get_response(request, args.kserve)
   > ```
   >

4. stop torchserve

   ```
   torchserve --stop
   ```

   

