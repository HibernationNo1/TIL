# install

사전에 torch, cudatoolkit이 install되어있어야 한다.



**mmdet** 설치할 때 mvcc도 한 번에 install



[document](https://github.com/open-mmlab/mmdetection)

MMDetection is an open source object detection toolbox based on PyTorch.

#### install

[document](https://github.com/open-mmlab/mmdetection/blob/master/docs/en/get_started.md)

OpenMMlab의 종속성을 자동으로 처리하기 위해 mim을 사용하여 설치한다.

**using mim**

```
$ pip install openmim
$ mim install mmdet
```

> `'cp949' codec can't decode byte 0xe2 in position 1179: illegal multibyte sequence` 와 같은 error가 나오면 install manually



**install manually**

1. install mmcv-full

   ```
   $ pip install mmcv-full -f https://download.openmmlab.com/mmcv/dist/{cu_version}/{torch_version}/index.html
   ```

   > if `cudatoolkit=10.2` and `pytorch==1.10.0` , 
   >
   > ```
   > $ pip install mmcv-full -f https://download.openmmlab.com/mmcv/dist/{cu102}/{torch1.10.0}/index.html
   > ```

2. install mmdet

   ```
   $ pip install mmdet
   ```

   