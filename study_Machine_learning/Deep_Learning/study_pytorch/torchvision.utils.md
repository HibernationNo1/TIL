# torchvision.utils

### utils.make_grid

mini-batch마다 할당된 images를 grid형대로 모아 배치해서 하나의 image로 만든다.

```python
from torchvision.utils import make_grid
```

image에 대한 training 중간중간의 결과를 확인할 때 사용한다.



```python
img = make_grid(tensor, nrow, padding, normalize, range, scale_each, pad_value)
```

- `tensor` : 4-D mini-batch Tensor of shape(B, C, H, W) or a list of images all of the same size

- `nrow` : images를 display할 window의 column부분  

- `padding` : image에 0의 값을 가진 pixel을 몇 겹으로 둘러칠지 결정

  > `pad_value` : padding의 default = 0이 아닌, 다른 값(0~1)을 주고자 할 때 사용

- `normalize` : True로 하면 image에 대해서 normalization을 진행한다.



**e.g.**

```python
import matplotlib.pyplot as plt
from torchvision.utils import make_grid

plt.imshow(make_grid(img, normalize = True))
plt.show()
```





### utils.save_image

```python
from torchvision.utils import save_image
```

mini-batch마다 할당된 images를 grid형대로 모아 배치해서 하나의 image로 만든 후 저장한다.

```python
save_image(tensor, fp, normalize)
```

- `tensor` : 4-D mini-batch Tensor of shape(B, C, H, W) or a list of images all of the same size
- `fp` : 저장하고자 하는 path
- `normalize`