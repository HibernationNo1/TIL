# OS

```python
import os
```



#### getcwd()

현재 작업하는 directory open

```python
tmp1 = os.getcwd()
print(tmp)	# D:\Project\tmp\.venv
```





#### path.join()

경로를 병합하여 새 경로 생성

경로를 생성할 뿐 실질적으로 directory는 만들지 않음

```python
tmp1 = os.getcwd()
# D:\Project\tmp\.venv

tmp2 = os.path.join(os.getcwd(), 'test_name1')
# 현 위치에서 'test_name1' 라는 directory 안의 경로 생성

tmp3 = os.path.join(tmp1, 'test_name2')
# D:\Project\tmp\.venv\test_name2
```





#### makedirs()

경로 위에 directory가 있으면 pass, 없으면 create한다.

```python
os.makedirs(tmp, exist_ok = True)
```

tmp object에 저장된 경로가 있으면 pass

없으면 directory를 만듦



#### chdir()

directory 변경

```python
os.chdir("C:\Tmp")
```



#### path.isdir()

찾고자 하는 경로(directory)가 있으면 Ture, 없으면 False return

```python
os.path.isdir('test_name1')
```



#### listdir()

경로 위 모든 directory list를 return한다.

```python
os.listdir(os.getcwd())
```



#### GPU ALLOW

GPU 를 과하지 않게 사용하기 위한 속성. 코드처음에 작성

```python
os.environ['TF_FORCE_GPU_ALLOW_GROWTH'] = 'true'
```

