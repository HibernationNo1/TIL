# torch.autograd

`torch.autograd` 는 신경망 학습을 지원하는 PyTorch의 자동 미분 엔진이다.



**requires_grad**

torch.Tensor의 parameter중 하나인 requires_grad는 autograd에 모든 opration을 tracking해야 한다고 알려준다.

>  tf.gradientTape이라고 생각하면 됨

```python
a = torch.Tensor([2., 3.], requires_grad = True)
```





### Variable

>  2021.01.12 기준 1.7 version에서는 더 이상 사용되지 않음
>
> 현재는 모든  tensor가 자동적으로 Variable의 성질을 가지고 있기 때문



Variable은 각 tensor의 값을 볼 수 있는 `data`, 미분을 볼 수 있는 `grad`, backward를 통한 미분을 계산한 함수 정보인 `grad_fn` 총 3개의 함수를 사용할 수 있다.

**How to use**

1. Tensor를 감싼다.

   ```python
   import torch
   from torch.autograd import Variable
   
   x = Variable(torch.randint(2, 2), requires_gard = True)
   ```

2. 식을 전개한다.

   ```python
   out = x**3 + 8*x + 10
   ```

3. backgropagation을 진행한다.

   이 때 **backward**를 사용한다.

   ```python
   out.backward()
   ```

4. 초기 x의 grad에 대해 살펴보며 해당 변화량을 확인한다.

   **gard**

   ```python
   print(x.gard)
   ```

   

