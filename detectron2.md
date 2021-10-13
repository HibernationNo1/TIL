# detectron2



download Cuda 10.1





create virtual envirment

```
$ conda create -n detectron2 python==3.7
```

```
$ conda activate detectron2
```



install pytorch

```
conda install pytorch torchvision torchaudio cudatoolkit=11.1 -c pytorch -c conda-forge
```

> 컴퓨터에 맞는 cudatoolkit=10.1 인지 확인



```
pip install cython
```



install pycoco

```
pip install "git+https://github.com/philferriere/cocoapi.git#egg=pycocotools&subdirectory=pythonAPI"
```





install detectron 2

```
mkdir detectron2
cd detectron2
```

```
git clone https://github.com/augmentedstartups/detectron2
```

> ```
> git clone https://github.com/facebookresearch/detectron2.git
> ```



install VC_redist.x64  (web site)

detectoron2 폴더 안에서 실행



```
pip install -e .
```

> detectoron2 폴더 안에서



``` 
pip install opencv-python
```



```
pip install fvcore==0.1.1.post20200716
```





```
python tests/test_windows_install.py
```

> image하나 떠야함
>
> image주소 바꾸려면 
>
> `res = requests.get("https://live.staticflickr.com/700/33224654191_fdaee2e3f1_c_d.jpg")`





local의 detectron2를  [colab](https://colab.research.google.com/drive/16jcaJoc6bCFAQ96jDe2HwtXj7BMD_-m5)이랑 연결

```
$ jupyter notebook
```



