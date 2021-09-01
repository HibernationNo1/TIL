# re



### re.match

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



