# OS

```python
import os
```





#### system()

argument로 받은 string을 linux 명령어로 수행한다.

```python
os.system("cd")
```



>  tmp.py라는 file이 아래와 같을 때
>
> ```python
> import os
> 
> print("무한루프")
> 
> os.system('python tmp.py')
> ```
>
> 무한루프가 돌아간다.
>
> 이를 이용해 다른 python file을 실행할 수 있다.



#### getcwd()

현재 작업하는 directory open

```python
tmp1 = os.getcwd()
print(tmp)	# D:\Project\tmp\.venv
```

> terminal command $ cd 를 사용해서 작업하는 위치 변경



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



#### os.listdir()

전달받은 path의 위치에 존재하는 모든 file과 directory를 list로 반환

```python
file_list = os.listdir(os.getcwd) 
# 현재 위치의 모든 file과 directory를 list로 return
```





#### os.walk()

전달받은 path의 하위에 존재하는 모든  file과 directory를 list로 반환

```python
(root, dirs, files) = os.walk(root_dir)
```

`root` : path의 list

`dirs` : [root[0]에 위치한 directory들의 list,  root[1]에 위치한 directory들의 list, ...]

`files` : [root[0]에 위치한 file들의 list,  root[1]에 위치한 file들의 list, ...]





#### os.environ

운영 체제에 등록되어 있는 모든 완경 변수에 접근이 가능

ex) 환경 변수 `HOME` 에 저장되어 있는 값에 접근

```python
print(os.environ['HOME'])
```





##### GPU ALLOW

GPU 를 과하지 않게 사용하기 위한 속성. 코드처음에 작성 (tensorflow사용시)

```python
os.environ['TF_FORCE_GPU_ALLOW_GROWTH'] = 'true'
```





#### name

on.name의 return은 운영체제에 따라서 다르다

`nt` : windows

`posix` : linux

```python
if os.name == 'nt':
    print("windows")
elif os.name == 'posix':
    print("linux")
```





#### rename()

```python
old_file_path = os.path.join(file_path, old_file_name)
new_file_path = os.path.join(file_path, new_file_path)

os.rename(old_file_path, new_file_path)
```

> file path 는 같아야 하며, file name만 다른 경우
