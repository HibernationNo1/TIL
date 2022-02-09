# tqdm

python 작업 중 프로그래이 내가 의도한 방향으로 진행되는 중인지 확인하는데 사용하는 moduel

```python
from tqdm import tqdm
```



##### Iterable-based

어느 iterable이든 tqdm으로 감싸면, iter이 증가함에 따라 진행률을 출력한다.

```python
import time

tmp_list = [i for i in range(100)]

for count in tqmd(tmp_list, desc = "test"):
    time.sleep(0.25)
```



- `tqmd(iter, desc = str)`
  - `iter` : iterable instance
  - `desc` : 진행률을 나타내는 바 앞에 표시할 text
  - 

