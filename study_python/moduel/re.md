# re



### match

패턴과 문자열이 일치하는 부분을 group 으로 묶어서 반환

```python
import re

model_path = "path/20210901T1644/mask_rcnn_lung_0001.h5"
regex = r".*[/\\]+(\d{4})(\d{2})(\d{2})T(\d{2})(\d{2})[/\\]mask\_rcnn\_[\w-]+(\d{4})\.h5"

m = re.match(regex, model_path)
print(m.group(1)) # 2021
print(m.group(2)) # 09
print(m.group(3)) # 01
print(m.group(4)) # 16
print(m.group(5)) # 44
```



### fullmatch

패턴과 문자열이 완벽하게 일치하면 매칭 결과를 return

일치하지 않으면 None 반환

```python
matchObj = re.fullmatch('a', 'a')
print(matchObj)		
# <_sre.SRE_Match object; span=(0, 1), match='a'>

print(re.fullmatch('a', 'aba'))
# None
```



