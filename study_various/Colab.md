# Colab

[Colab](https://colab.research.google.com/notebooks/)



shell 명령어

code에서 `!` 쓰고나서 사용

```
! 명령어
```



##### Using GPU

상단 tap - Edit - Notebook settings 누르고 GPU설정

> 연결 안되어있으면 tensorflow돌릴때
>
> `GPU device notfound` 뜸



##### File Download, Upload

좌측 tap - file부분 클릭



File Save on github

##### github와 연동

**Save file on github**

상단 tap - github에 사본 저장

>  `.ipynb` 로 저장됨



**load file from github to colab**

연동하고자 하는 github repository 주소가 `https://github.com/HibernationNo1/Segmented_Lung-assignment/blob/master/Lung_Segmentation.ipynb` 일 때

text에서

```
https://colab.research.google.com/github/HibernationNo1/Segmented_Lung-assignment/blob/master/Lung_Segmentation.ipynb
```



##### Google Drive와 연동

code에서

```python
from google.colab import drive
drive.mount('/content/gdrive')
```



##### python

version이 3.7.11이고, 3.8.8로 바꿀 떄

```shell
!wget https://www.python.org/ftp/python/3.8.8/Python-3.8.8.tgz
!tar xvfz Python-3.8.8.tgz
!Python-3.8.8/configure
!make
!sudo make install
```



