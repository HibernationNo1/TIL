# YOLO

- YOLO의 기본 컨셉

  image를 **S*S Grid Cell** 로 나누고, 각 cell 별로 **B** 개의 **Bounding Box**를 predict

  

> object detection tesk 에 의해 만들어진 Bounding Box 하나당 mapping되는 5가지 vector
>
> - x, y : grid cell 내의 object 중앙 x, y좌표 (normalization된 0~1 사이의 값)
> - width, height : 전체 image 대비 width, height 값 (normalization된 0~1 사이의 값)
> - confidence : image 내에 object가 있을 것이라고 확신하는 정도



### 동작 과정

1. **YOLO Model에 image Input**

   YOLO Model의 최종 output 개수
   $$
   output: S \times S \times(5*B + C)
   $$

   > **5** :  x, y coordinate, width, height, confidence 
   >
   > **B** : number of Bounding Box
   >
   > **C** : number of Class

   S = 7, B = 2, C = 20 일 경우 YOLO Model의 최종 output은 7 * 7 * 30

   

2. **class specific confidence score**

   YOLO는 output image의 grid cell 마다 각 class에 대한 probability를 각 bounding box의 confidence와 곱한 vector를 연산한다.



3. **non-*maximum* suppression**

   class specific confidence score 로 인해 나온 다수의 bounding box 중 가장 대표성을 띄는 bounding box만 표현한다.

   non-*maximum* suppression 동작 과정

   1. confidence 가 0.6 이하인 bounding box를 제거한다
   2. class별로 confidence가 가장 높은 bounding box가 앞으로 오도록 전체 bounding box를 내림차순 정렬한다.
   3. 가장 confidence가 높은 bounding box와 나머지 bounding bax를 비교해서 2개의 bounding box의 IoU 가 0.5보다 크다면 confidence가 가장 높은 bounding box를 제거한다
   4. 제거되지 않는 bounding box 중에서 confidence가 가장 높은 bounding box와 나머지 bounding box간에 3번 과정을 반복한다.
   5. 3~ 4번 과정을 전체 bounding box에 대해서 진행한다.
   6. 2~5번 과정을 전체 class에 대해서 진행한다.

   > 3~4번 과정이 non-*maximum* suppression algorithm이다





> **exmple : S = 7, B = 2, C = 20 일 경우**
>
> ![](https://curt-park.github.io/images/yolo/DeepSystems-NetworkArchitecture.JPG)
>
> | input image | 448 × 448 × 3      |                         |
> | ----------- | ------------------ | ----------------------- |
> | layer 1     |                    | GoogLeNet               |
> |             | **14 × 14 × 1024** |                         |
> | layer 2     |                    | Convolution, Maxpooling |
> |             | **14 × 14 × 1024** |                         |
> | layer 3     |                    | Convolution, Maxpooling |
> |             | **14 × 14 × 1024** |                         |
> | layer 4     |                    | Convolution, Maxpooling |
> |             | **7 × 7 × 1024**   |                         |
> | layer 5     |                    | Convolution, Maxpooling |
> |             | **7 × 7 × 1024**   |                         |
> | layer 6     |                    | Flatten                 |
> |             | **50,176 × 1**     |                         |
> | layer 7     |                    | Dense                   |
> |             | **4096 × 1**       |                         |
> | layer 8     |                    | Dense                   |
> |             | **1470 × 1**       |                         |
> | layer 9     |                    | Reshape                 |
> | **output**  | **7 × 7 × 30**     |                         |
>
> 
>
> **output**
>
> 7 × 7 × 30에서, 각 grid cell에 대하여 
>
> - 30차원 vector의 앞 5개 :  1개의 Bounding Box를 표현
> - 그 다음 5개: 두 번째 Bounding Box를 표현
> - 그 다음 20개 : 각 class에 대한 softmax regression confidence 
>
> 
>
> **class scores for bounding box**
>
> grid = (7, 7) 이고 bounding box  = 2, class = 20 이므로
>
> (20개의 class에 대한 probability) * (bounding box의 confidence) =  20 × 1 의 vector가 7 × 7 × 2 개 
>
>  즉, 98개의 bounding box가 나오게 된다.
>
> 
>
> **non-*maximum* suppression**

