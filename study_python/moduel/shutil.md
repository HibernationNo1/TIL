# shutil

고수준 파일 연산



#### copyfile()

가능한 가장 표율적인 방법으로 src인 file의 내용을 (meta data 없이) dst인 file에 copy후 dst를 return

src와 dst는 path에 대한 string이여야함

```python
dst = shutil.copyfile(src, dst)
```





#### copy()

src인 file을 file또는 directory인 dst에 copy

src와 dst는 path에 대한 string이여야함

```python
shutil.copy(src, dst)
```

