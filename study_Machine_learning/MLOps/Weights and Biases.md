# Weights and Biases

- 실험관리가 필요한 이유

  여러 실험을 하며 최적의 hyperparameter, 사용한 data의 종류 또는 model 등 학습에 유요한 영향을 주는 요소를 기록하며 관리한다.

  이를 위해 사용하는 실험관리 솔루션 툴이 바로 **Weights and Biases** 이다.

  > 개인적으로 사용하는 것은 무료이지만, 기업 단위는 별도의 가격 정책을 갖고 있다.
  >
  > https://wandb.ai/site



**install**

```
$ pip install wandb -qqq
```

```
$ wandb login
```

> loging 토큰을 발행하는 웹 주소를 알려준다. 
>
> 이후 이어서 출력되는  `Paste an API key from your profile and hit enter: ` 에 입력



간단한 연동 (python, keras, tensorflow등이 있다.)

```python
import torch
import torch.nn as nn

import wandb
wandb.init(project="project_name")

# log any metric from your training script
wandb.log({"acc" : accuracy, "val_acc": val_accuracy})
```

> 자세한 방법은 홈페지이제 있으며 colab환경에서 실습또한 할 수 있다.
>
> 반드시 해볼 것





