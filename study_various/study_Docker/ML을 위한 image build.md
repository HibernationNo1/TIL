ML을 위한 image build



#### inference image

```
ls 	┬ detectron2 (dir) 
	│
	├ models_2021_11_11.pth
	│
	├ requirements.txt 	   
	│
	├ inference.py
	│
	├ utils.py
	│
	└ config.py		
	
	- inference_result_image (dir)	◆
```

- `detectron2 (dir)` : import `detectron2`을 위한 package

- `models_2021_11_11.pth` : pre-trained model

- `requirements.txt` : 해당 repository를 실행하기 위한 module 및 package에 관한 정보

  > `requirements.txt` 는 반드시 명시해야 할 목록만 간단하게 명시한다.

- `inference.py` : `models_2021_11_11.pth`의 weight를 load한 후, `test_images (dir)` 의 images에 대해 inference를 진행한다.

- `utils.py` : `inference.py`에서 사용되는 여러 utility function이 define되어 있다.

- `config.py` : `inference.py`에서 사용되는 여러 configuration이 class로 define되어 있다.

- `inference_result_image (dir)	◆` : `inference.py`로 인해 생성되는 dir



1. **create dockerfile**

   ```
   $ vi dockerfile
   ```

   > 위 명령어는 `inference.py` 가 있는 위치에서 실행한다.

   

   ```yaml
   FROM python:3.7-buster	# train.py가 실행되기 위한 execution environment
   						# 3.7version이며, base형태인 buster를 가져왔다.
   
   WORKDIR /usr/src/app		# copy할 source들의 위치를 정의
   
   RUN apt-get update						# apt-get -y install libgl1-mesa-glx를 위해 필요함
   RUN apt-get -y install libgl1-mesa-glx  # import cv2를 하기 위해 필요함
   RUN pip install --upgrade pip
   
   
   COPY requirements.txt ./
   RUN pip install -r requirements.txt
   
   COPY ./ ./		# 현재 위치의 모든 파일을 copy한다.
   
   
   CMD ["python", "inference.py"]		# cmd에서 python train.py 라는 명령어가 실행됨
   ```

   

2. **build**

   ```
   $ docker build -t hibernation/segmentation_inference:0.0.1 ./
   ```

   > - `.` 반드시 표기해야함
   >
   >   현재 location의 directory에 위치한다는 뜻
   >   
   > - 



3. **run**

   1. initial running일 때

      ```
      $ docker run hibernation/segmentation_inference:0.0.1
      ```

   2. initial running이 아닐 때

      ```
      $ docker run -v $(pwd):/usr/src/app hibernation/segmentation_inference
      ```

      > windows에서는` $(pwd):/usr/src/app` 대신 `%cd%:/usr/src/app`
      >
      > 명령어를 입력하는 위치의 file을 mount한다.(source code의 변경점이 있다면 바로 반영됨)



- ```
  $ docker exec -it hibernation/segmentation_inference:0.0.1 sh
  ```

  





