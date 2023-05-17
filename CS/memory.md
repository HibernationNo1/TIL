# memory

용어

- logical address(논리적 주소)

  process가 memory에 적재되기 위한 독자적인 주소들.

  process마다 독립적으로 할당되는 주소들이며, 0번지부터 시작된다.

  code, heap과 같은 memory의 특정 공간에 대한 주소를 process별로 0번지부터 차례로 이름을 붙여준다(별명처럼).

  > 하지만 실제 memory상에서는 process와 상관 없는 주소에 위치하게 된다. 그냥 어디 있는지 확인하기 쉽게 process의 단위로 정리한 주소들.

- physical address(물리적 주소)

  process가 실제로 memory에 적재되는 위치를 나타내는 주소

- address binding(주소 바인딩)

  CPU가 기계어 명령을 수행하기 위해 process의 logical address가 실제 physical address의 어느 위치에 mapping되는지 확인하는 과정



## 관리

### paging

process의 memory공간을 동일한 크기의 page단위로 나누어 physical address의 서로 다른 위치에 page들을 저장하는 memory관리 기법.

1. 실제 Ram memory인 physical memory를 page와 같은 크기의 frame으로 미리 나누어둔다.

2. process의 memory를 page단위로 나눈다.

3. process의 memory를 page단위로 Ram memory에 적재한다.

   ram memory도, process의 논리적 memory도 page단위로 미리 분할해 뒀기 때문에 memory할당이 빠르게 이루어진다.

   이 때 page table를 만들게 된다.

   - page table

     address binding을 위해 process의 각 page의 logical address들과 Ram memory의 physical address들을 서로 대응해서 저장해 놓는다.

     주소 변환이 빠르게 이루어질 수 있도록 하기 위해.

     page table의 column은 **logicl address의 번지**, **physical memory의 주소**가 있다.

     ![](https://images.velog.io/images/jieuni/post/4c3139a6-7c2e-4e96-8c19-7122abd5d0c0/image.png)



**paging기법시 발생할 수 있는 문제**

- memory gragmentation(memory 내부 단편화)

  process주소 공간의 크기가 page크기의 배수라는 보장이 없기 때문에, process의 주소 공간 중 가장 마지막에 위치한 page에서는 결국 어느정도 남는 공간(아무 data도 없는 공간)이 발생하게 된다. 

  process주소 공간에서 이러한 낭비되는 memory가 있는 것을 memory gragmentation이라고 한다.





### segmentation

process가 할당받은 memory공간을 논리적 의미 단위(segment)로 나누어, 연속되지 않는 물리 메모리 공간에 할당될 수 있도록 하는 memory관리 기법

process의 memory는 code, data, heap stack등의 기능 단위로 segment를 정의하는데, 이런 것 처럼 기능 단위로 나누어 관리하는 것이다.

segmentation또한 address binding을 위한 segment table을 갖는다.

- 기능 또는 의미적 단위로 영역을 나누었기 때문에 나눈 영역의 크기가 일정하지 않다.
- segment table의 column은 **logical memory의 번지**, **physical memory의 주소**, **physical memory에서 실제 할당받을 크기의 제한(limit)**이 있다.



**segmentation기법에서 발생할 수 있는 문제**

- memory fragmentation(memory 외부 단편화)

  커다란 크기의 segment가 할당되었다가 제거되고 그 자리에 더욱 작은 segment가 할당되면, 기존의 segment에 비해 남는 공간이 생기게 된다. 

  이 처럼 서로 다른 크기의 segment들이 physical memory에 적재되고 제거되는 일이 반복되면 Ram memory공간에서 낭비되는 memory가 생기는데, 이를 memory fragmentation이라고 한다.



### paged segmentation

segmentation을 기본으로 하되, 각각의 segmentation을 다시 동일 크기의 page로 나누어 physical memory에 할당하는 memory관리 기법이다.

- 외부 단편화 문제를 해결할 수 있다.
- 동시에 segment단위로 process간의 공유나 process내의 접근 권한 보호가 이루어지도록 해서 paging기법의 단점을 해결한다.





### virtual memory

process전체가 memory에 적재되지 않더라도 실행이 가능하도록 하는 기법

사용자의 program이 physical memory보다 커져도 실행이 가능하다.

- 운영체제는 virtual memory기법을 통해 program의 losical memory주소 영역에서 필요한 부분만 logical memory에 적재하고, 직접적으로 필요하지 않는 memory공간은 swap영역에 저장하게 된다.

  ![](https://www.tutorialspoint.com/operating_system/images/virtual_memory.jpg)

#### demand paging

요구 페이징

당장 사용될 주소 공간을 page단위로 memory에 적재하는 방법

- 특정 page에 대해 cpu의 요청이 들어온 후에 해당 page를 메모리에 적재한다.

- 당장 실행에 필요한 page만을 메모리에 적재하기 때문에 memory사용량이 감소하고 입출력 overhead도 감소한다.



- invaild bit

  virtual memory(process의 memory)상에는 존재하지만, 당장은 사용하지 않기 떄문에 swap sapce에 존재하는 memory영역



**page fault**

CPU가 invaild bit(무표 비트)로 표시된 page를 사용하기 위해 access하는 상황을 의미한다.

CPU가 invaild page에 접근하면 주소 변환을 담당하는 하드웨어인 MMU가 page fault trap을 발생시키게 된다.

1. CPU가 page N을 참조한다.

2. page table에서 page N이 invaild상태임을 확인한다.

3. MMU에서 page fualt trap이 발생한다

   - page fualt trap

     swap영역에 있는 page N에 대한 memory영역을 physical memory에 적재하는 동작.

4. 디스크에서 page N을 빈 frame에 적재하고 page table을 update한다. (invaild -> vaild)



**replacement algorithm**(페이지 교체)

page fualt trap이 발생하면 요청된 page를 디스크의 swap영역에서 pysical memory로 가져와야 한다. 

이 때 physical memory에 공간이 부족한 경우, 기존에 physical memory에 있던 page를 swap영역으로 옮겨 memory공간을 확보하는 것을 replacement algorithm라고 한다.

- replacement algorithm은 최대한 page fault가 적게 일어나도록 도와줘야 한다.

  때문에 앞으로 참조될 가능성이 적은(사용되지 않을) page를 선택해서 교체하는 것이 성능을 향상시키는 방법이다.

- algorithm 종류는 여러가지가 있다.

  - FIFO(first in first out)

    가장 오래된 page를 교체

  - 최적 page 예측

    앞으로 사용되지 않을 page를 예측

  - LRU(least recently used)

    가장 오랫동안 사용되지 않는 page

