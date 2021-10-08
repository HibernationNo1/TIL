# Docker_Deeplearning

### cuda환경 갖추기

Docker Compose v1.28.0 이상부터는 device 구조를 정의해서 GPU를 사용할 수 있게 한다.

```yaml
services: 
	cuda: 
		image: nvidia/cuda:10.2-base 
		command: nvidia-smi 
		runtime: nvidia


```











####  train, distribution

container image로 dataset만들고, model학습하고, 배포하기

1. **image로 dataset만들기**

   ```
   $ docker run -v /image_data:/input_image \
   			 -v /container_dataset:/dataset \
   		 	 -d --name create_dataset hibernation/create_dataset
   ```

   1. host의 `/image_data` 라는 directory에 있는 image를 container의 `/input_image` 로 공유한다.
   2. create_dataset 이라는 image안의 create_dataset.py라는 program이 실행되고,output으로 dataset이 만들어진다.
   3. 이 때 만들어지는 dataset은  container안의 `/container_dataset`라는 경로에 저장한다. 그리고 그 경로는 host의 `/dataset` 에도 공유된다.

2. **만들어진 dataset으로 model학습하기**

   ```
   $ docker run -v /dataset:/train_data  \
   			-v /trained_model:/model  \
   			-d hibernation/train_model
   ```

   1. host의 `/dataset`에서 dataset을 container의 `/train_data` 로 공유한다.
   2. model 이라는 image안의 train.py라는 program이 실행되어 model이 학습된다.
   3. 학습이 끝난 후 trained model은 container의 `/trained_model`로 저장된다. 그리고 그 경로는 host의 `/model ` 에도 공유된다.

3. **inference application container image만들기 (name: trained_model)**

   inference.py을 담은 image를 trained_model이라는 이름으로 build하기

   1. container image로 만들 directory생성 후 file옮기기

      ```
      $ mkdir trained_model		# 별도의 direcotry가 필요함
      $ mv requirements.txt \
      	 inference.py model.py utils.py visualization.py \
      	 model_0.h5 model_1.h5 model_2.h5 model_3.h5 \
      	 ./trained_model/
      ```

      > model_0 model_1 model_2 model_3 : 학습된 model

   2. create dockerfile as vim

      ```
      $ cd build
      $ vi dockerfile
      ```

      ```dockerfile
      FROM continuumio/miniconda3
      WORKDIR /code
      
      RUN conda create -n tensorflow2 python=3.7
      RUN conda activate tensorflow2
      
      # requirements
      COPY requirements.txt requirements.txt
      RUN pip install -r requirements.txt		
      
      # set path for inference
      RUN mkdir /code, /model, /result_inference, /input_data
      COPY inference.py model.py utils.py visualization.py /code
      COPY model_0.h5 model_1.h5 model_2.h5 model_3.h5 /model
      VOLUME ["/input_data", "/result_inference"]
      
      EXPOSE 5000
      
      CMD ["python", "inference.py"]
      ```

      ```
      $ cat dockerfile
      ```

   3. build하기

      ```
      $ docker build -t trained_model .
      ```

4. **screate docker-compose.yml** 

    ```yaml
    version : "3.9"
    
    
    services:
    	cuda:
    		image: nvidia/cuda:10.2-base
    		command: nvidia-smi
    		runtime: nvidia
    	
    	inference:
    	build: .
    ```

   

5. trained_model사용하기(배포된 image)

   ```
   $ docker run -v /input_data:/input_data  \
   			-v /result_inference:/result \
   			--name model_name \
   			-p 5000:5000 \
   			-d hibernation/trained_model
   ```

   1. host의 `/input_data` 안의 file을 container의 `/input_data`로 가져온다.

   2. trained_model이라는 image안의 inference.py라는 program이 실행되어 결과가 출력된다.

   3. 출력된 결과는 container안의 `/result_inference`에 저장된다. 그리고 그 경로는 host의

      `/result `에도 공유된다. 

