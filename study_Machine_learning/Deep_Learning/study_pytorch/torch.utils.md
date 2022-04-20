# torch.utils

```py
import torch
import torch.utils
```



### utils.data

```python
import torch.utils.data
```



#### DataLoader

ImageFolder로부터 생성된 instance를 argument로 받아 load하는 기능을 가지고 있다.

```python
from torch.utils.data import DataLoader

data_loader_train = DataLoader(dataset = train_data, batch_size = batch_size, shuffle = True)
```

- dataset : mini batch로 구성할 input dataset

- batch_size : batch size를 통해 mini batch를 구성할 수 있다.

- shuffle : dataset의 순서를 random으로 섞어서 배치를 구성할지 여부를 결정

  > `True` or `False`

> ```python
> train_features, train_labels = next(iter(data_loader_train))
> print(f"train_features: {train_features.size()}")  # torch.Size([batch_size, channel, height, width])
> print(f"label : {train_labels.size()}")		# torch.Size([32])
> ```

- `torch.utils.data.DataLoader` 의 return값에 `next(iter())`  를 적용하면 [`data`, `labels`]를 return하며, `data`는 mini batch로 구성된 input data

  `labels`은 mini batch로 구성된 label이다.





#### Dataset

Dataset을 상속받아 subclassing으로 custom dataset class를 만든다.

```python
from torch.utils.data import Dataset

class CustomImageDataset(Dataset):
    def __init__(self, config, transform=None):     
        """
        transform (callable, optional): Optional transform to be applied
                on a sample.
        """
        self.root_dir = config.DATA.DATA_PATH
        self.json_file = os.path.join(os.path.join(os.getcwd(), self.root_dir), config.DATA.DATASET)

        with open(self.json_file) as f:
            self.metadata = json.load(f)

        self.transform = transform
    
    def __getitem__(self, idx):                     
        """
            idx : index of image list
        """
        
        if torch.is_tensor(idx):
            idx = idx.tolist()	# tensor인 idx를 list의 entry로 변경
        
        image_metadata = self.metadata["metadatas"][idx]
        
        record = {}
        image_info = image_metadata["image_info"]
        image_name = image_info["file_name"]             # 2_20200825_093215.jpg
        image_path = os.path.join(self.root_dir, image_name)     # training에 사용할 image의 path    
        image = cv2.imread(image_path)

        record["image_path"] = image_path                  
        record["height"] = image_info["height"]
        record["width"] = image_info["width"]
        
        objs = []

        for _, instance_info in enumerate(image_metadata["instance_info"]):

            x_min, y_min, x_val, y_val = instance_info["bbox"]      # x_max = x_min + x_val (same y)
            obj = {
                "bbox":  [x_min, y_min, x_min + x_val, y_min + y_val],
                "segmentation": instance_info["segmentation"],
                "incstance_id": instance_info["category_id"],
                }
            objs.append(obj)
        record["annotations"] = objs


        if self.transform:
            image = self.transform(image)	# image에 transform적용

        return image, record
    
    def __len__(self):                              
        return len(self.metadata["metadatas"])
```

- `def __init__()` : 데이터 셋을 가져와서 전처리를 해준다.

- `def __getitem__()` : 데이터 셋에서 한 개의 데이터를 가져오는 함수를 정의 (여기서 image는 tensor를 return해야함)

- `def __len__()` : 데이터 셋의 전체 길이를 반환

위 세 개의 함수는 반드시 정의되어있어야 한다.

> 위 처럼 `from torch.utils.data import Dataset`를 상속받아 `CustomImageDataset`를 생성하면 아래처럼 다룰 수 있다.
>
> ```python
> from torchvision import datasets, transforms
> 
> img_size = [720, 1280]
> torchvision_transform = transforms.Compose([			# transforms 생성 
>                              transforms.ToTensor()
>                             ,transforms.Resize(img_size)]) 
> 
> from data import custom_dataset
> train_dataset = custom_dataset.CustomImageDataset(config, transform=torchvision_transform)
> ```





#### DistributedSampler()

분산처리(train or validation or test)를 위해 사용됨

> `torch.nn.parallel.DistributedDataParallel`과 함께 사용

```python
sampler_train = torch.utils.data.DistributedSampler(
            dataset_train, num_replicas=num_tasks, rank=global_rank, shuffle=True
        )
```

