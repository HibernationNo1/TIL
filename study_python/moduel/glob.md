# glob

파일들의 list를 뽑을 때 사용하는 moduel이다.



```python
import glob
```

- `glob('path')`

  ```python
  import glob
  import os 
  import cv2
  
  glob.glob('*.*') # 현재 directory의 모든 file을 list화
  
  path_model = os.path.join(os.getcwd() , 'models')
  for path_ in sorted(glob.glob (path_base_input + '\*.png')):
      img = cv2.imread(path_)  
  ```

  

