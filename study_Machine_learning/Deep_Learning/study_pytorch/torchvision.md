# torchvision

deep learning에서 자주 사용되는 dataset과 model structure 및 image convert 기술을 포함한 module

```python
import torchvision
```



### datasets

#### MNIST

mnist를 load한다.

```python
train_data = datasets.MNIST(root = './data', train = True, download = True,
                            transform = transforms.ToTensor())
```



#### ImageFolder

```python
from torchvision.datasets import ImageFolder
```

개인 images를 load한 후 pytorch dataset 객체로 변환하는 method

```python
train_dataset = ImageFolder(root, transform)
```

- `root` : `.jpg,.jpeg,.png,.ppm,.bmp,.pgm,.tif,.tiff,.webp` 와 같은 images가 모여있는 dir의 path (dataset의 최상위 dir)

  >  root  = `./dataset` 
  >
  > 일 때 dir map은 아래와 같다
  >
  > ```
  > dataset ┬ dir_0   ┬   1.jpg
  > 		│         ├   2.jpg
  > 		├ dir_1   ...
  > 		│         └   N.jpg
  > 		...
  > 		│
  > 		└ dir_N
  > ```
  >
  > 이 때 dir_0부터 dir_N은 각각 한 개의 class를 의미한다. (dog, cat 등등...)
  >
  > 그렇기 때문에 한 개의 image에 한 개의 class를 담은 dataset만 가져오는게 가능하다.
  >
  >  한 개의 image에 다수의 class를 담은 image를 사용하려면 `from torch.utils.data import Dataset` 를 사용하자.
  
- `transform` : augmentation방법을 지정

  > torchvision.transforms를 통해 정의한 augmentation방법 list를 가져온다.

> e.g.
>
> ```python
> data_transforms = {
>     'train' : transforms.Compose([
>         transforms.Resize([1024, 1024]),
>         transforms.RandomHorizontalFlip(),
>         transforms.RandomVerticalFlip(),
>         transforms.RandomCrop(1024),
>         transforms.ToTensor(),
>         transforms.Normalize([R_m, G_m, B_m],[R_s, G_s, B_s])
>     ]),
>     'val' : transforms.Compose([
>         transforms.Resize([1024, 1024]),
>         transforms.RandomCrop(1024),
>         transforms.ToTensor(),
>         transforms.Normalize([R_m, G_m, B_m],[R_s, G_s, B_s])
>     ])
> }
> 
> image_datasets = {x: ImageFolder(root = os.path.join(data_dir, x),
>                              	transform = data_transforms[x]) for x in ['train', 'val']}
> ```

> 만일 dataset(images)의 size가 일관되어있지 않다면 (어떤건 [1024, 1024], 어떤건 [512, 512]) 반드시 `transforms.Resize()` 를 통해 images의 size를 통일해주어야 `DataLoader`를 통해 가져올때 에러가 발생하지 않는다.

이후 `from torch.utils.data import DataLoader` 를 통해 image를 하나씩 가지고오는 작업을 해야 한다.



### models

pre trained model을 load한다.

```python
from torchvision import models
```



> **e.g.**  resnet가져오기
>
> ```python
> resnet = model.resnet50(pretrained = True)
> ```
>
> - `pretrained` : pretrained옵션을 True로 설정하면 미리 학습된 model의 parameter값을 그대로 가져온다.
>
> ```python
> num_ftr = resnet.if.in_feature
> resnet.fc = nn.Linear(num_ftr, 10)
> ```
>
> - data의 class개수가 10개라면, model의 마지막 layer의 output channel 수는 10개여야 한다. 이를 위해서 model의 마지막 Full conneted layer대신 output channel수가 10개인 layer로 대체한다.
>
> **in_feature** : 해당 layer의 입력 채널 수를 의미한다.
>
> ```python
> optimizer_tf = optim.Adam(filter(Lambda p : p.requires_grad, 
>                                 resnet.parameters()), lr = 0.001)
> 
> ```
>
> - `requires_grad = True`로 설정된 layer의 parameter에만 최적화 적용





### transforms

data를 조작하고 학습에 적합하게 만드는 class

```python
import torchvision.transforms as transforms
```



#### ToTensor

image를 tensor로 변경하는 preprocessing을 진행한다.

```python
transforms.ToTensor()
```





#### Resize

image를 1024×1024로 resizing

```python
transforms.Resize([1024, 1024])
```



#### RandomHorizontalFlip

image를 무작위로 좌우 반전

```python
transforms.RandomHorizontalFlip(p = 0.5)
```

- `p` : 반전되는 image의 비율 결정 (default = 0.5) 



#### RandomVerticalFlip

image를 무작위로 상하 반전

```python
transforms.RandomVerticalFlip(p = 0.5)
```

`p` : 반전되는 image의 비율 결정 (default = 0.5) 



#### RandomCrop

image의 일부를 random하게 잘라내서 특정 size로 변경한다.

```python
transforms.RandomCrop(1024)
```

> image의 일부를 random하게 잘라내서 1024 size로 변경한다.



#### Normalize

image가 Tensor형태로 전환된 이후에 nomalization을 시행한다.

```python
transforms.Normalize([R_m, G_m, B_m],[R_s, G_s, B_s] )
```

`[R_m, G_m, B_m]` : [red channel의 mean, green channel의 mean, blue channel의 mean]

`[R_s, G_s, B_s] ` :  [red channel의 std, green channel의 std, blue channel의 std]



#### Compose

transform의 method를 여러개 호출해야 하는 경우, 하나로 묶어주는 method

```python
torchvision_transform = transforms.Compose([ 
   transforms.ToTensor(), 
   transforms.Normalize((0.5, 0.5, 0.5), (0.5, 0.5, 0.5)) 
])
```





