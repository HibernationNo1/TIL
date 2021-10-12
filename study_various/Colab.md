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



##### runtime 유지하기

```
function ClickConnect(){
console.log("Working"); 
document.querySelector("colab-toolbar-button").click() 
}setInterval(ClickConnect, 1800000)
```

> 위 코드는 30분마다 colab-toolbar-button을 클릭하는 코드이다. 30분 마다 Text 섹션이 추가된다. 만약에 이 방법을 사용해도 런타임 연결이 종료되는 경우 setInterval 함수의 두 번째 파라미터의 값을 더 작은 값(단위는 millisecond)으로 설정해보자.





##### local runtime연결

1. install ['jupyter notebook'](https://jupyter.org/install)

2. 확장 program install 

   ```
   $ pip install jupyter_http_over_ws
   $ jupyter serverextension enable --py jupyter_http_over_ws
   ```

   > 만약 삭제하고싶을 때
   >
   > ```
   > $ jupyter serverextension disable --py jupyter_http_over_ws
   > $ pip uninstall jupyter_http_over_ws
   > ```
   >
   > 

3. server시작 및 인증

   ```
   $ jupyter notebook \
     --NotebookApp.allow_origin='https://colab.research.google.com' \
     --port=8888 \
     --NotebookApp.port_retries=0
   ```

   > server가 시작되면 초기 backend URL과 함께 메시지가 인쇄. 
   >
   > 다음 단계에서 입력해야 하므로 이 URL을 다른 위치에 저장

4. local runtime연결

   1. Colaboratory에서 '연결' 버튼을 클릭하고 '로컬 런타임에 연결...'을 선택
   2. 이전 단계의 초기 backend URL 입력
   3. 연결

   ```
   ```

   
