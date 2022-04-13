# EDSR

구현 code : https://github.com/Saafke/EDSR_Tensorflow



image를 upsampling할때 사용

openCV에서 관련 method를 제공하고 있다.

```
$ pip install opencv-contrib-python
```





```python
import cv2
from cv2 import dnn_superres
sr = dnn_superres.DnnSuperResImpl_create()

path = "EDSR_x2.pb"		# 해당 model은 구현 code github의 model/ 에 있다.
sr.readModel(path)
sr.setModel('edsr', 3)

img = cv2.imread(file_path)
img7 = sr.upsample(img)

cv2.imshow(f"width : {img7.shape[1]}, height : {img7.shape[0]}, mean : {np.mean(img7)}", img7)
while True:
    if cv2.waitKey() == 27:
        break
cv2.destroyAllWindows()
```

> EDSR_x2.pb 해상도(size)를 2배 키워준다.
>
> EDSR_x3.pb 
>
> EDSR_x4.pb 