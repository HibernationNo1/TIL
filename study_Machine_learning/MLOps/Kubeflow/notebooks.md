

# Notebooks

`New Noteboock` : 해당 namespace에 대한 Notebook server생성

python code, termina등 사용 가능



**name**

>  이전에 만든 notebook의 volume이 남아있다면 해당 name은 중복 불가



### Docker Image

image는 기본적으로 kubeflow에서 제공하는 것을 사용할 수 있지만, 해당 image는 sudo명령어가 인식되지 않기 때문에 몇 가지 layer를 추가한 custom image를 만들어 사용하는 것이 좋다.



#### custom image

- kubeflow기본 제공 image를 base로 하는 dockerfile생성

  1. [공식](https://gallery.ecr.aws/j1r0q0g6/notebooks/notebook-servers/jupyter-pytorch-cuda-full)페이지에서 base image를 결정한다.

  2. sudo를 사용할 수 있게 하기 위한 root권한 설정하는 command는 base image가 무엇인지에 따라 다르다.

     TODO: 특정 예시 image를 시험삼아 만들고 notebook에 pull을 성공하여 root권한 설정이 가능한 notebook서버를 얻자.

  

  - error
    - pip3 install pycocotools가 불가능하다.(방법 못찾음)

  

- 독립적인 image를 base로 하는 dockerfile생성

  1. custom image를 만들기 위해서는 반드시 아래 명령어가 docker image에 포함되어야 한다.

     reference: [here](https://v0-6.kubeflow.org/docs/notebooks/custom-notebook/)

     ```
     ENV NB_PREFIX /
     
     CMD ["sh","-c", "jupyter notebook --notebook-dir=/home/jovyan --ip=0.0.0.0 --no-browser --allow-root --port=8888 --NotebookApp.token='' --NotebookApp.password='' --NotebookApp.allow_origin='*' --NotebookApp.base_url=${NB_PREFIX}"]
     ```

  2. 위 명령어만 추가한다고 해서 kubwflow의 notebook에 image가 정상적으로 pull되진 않는다.

     사용하고자 하는 base image에 따라 몇 가지 설정 command가 추가되어야 한다.



### Volume

#### Workspace Volume

persistance volume을 생성. (작업 내역을 보존하고싶다면 반드시 할당)

- mount되는 directory의 위치는 `/opt/local-path-provisioner/volume_name`이다.
- Attach existing volume을 통해 기존에 만들어둔 persistance volume중 Access Mode가 `ReaWriteMany`인 volume을 선택하면 여러 인원이 data를 공유할 수 있다.



#### Data Volumes

그 외 volume을 생성. 





**Configurations**

특정한 민감 정보를 kubernetes에 secret하게 하고자 할 때 해당 정보를 notebook에서 가져와 사용할 수 있도록 한다.





**Affinity / Tolerations**

어떤 Node는 GPU 가 있고, 어떤 Node는 memory가 빵빵하고.. 등 각 Node당 특징이 있다. 이런 경우 해당 notebook server를 특정 node에 scheduling하고자 할 때 사용한다.