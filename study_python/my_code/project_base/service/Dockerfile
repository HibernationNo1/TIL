FROM pytorch/pytorch:1.6.0-cuda10.1-cudnn7-devel

# To fix GPG key error when running apt-get update
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/machine-learning/repos/ubuntu1804/x86_64/7fa2af80.pub

# 기본 tool 설치
RUN apt-get update && apt-get install -y git wget vim sudo lsof\
    libgl1-mesa-glx libglib2.0-0
# 설치 과정에서 생성된 캐시 파일들을 정리해 디스크 공간을 절약
RUN apt-get clean
# 생성된 패키지 목록 파일들을 삭제하여 이미지의 크기 최소화                   
RUN rm -rf /var/lib/apt/lists/*

WORKDIR /workspace
COPY requirements.txt requirements.txt
RUN pip install --upgrade pip && pip install -r requirements.txt
RUN pip install mmcv-full==1.5.0 -f https://download.openmmlab.com/mmcv/dist/cu117/torch2.0.0/index.html
RUN pip install mmdet==2.23.0

# docker build . --no-cache -t ocr_api:0.3