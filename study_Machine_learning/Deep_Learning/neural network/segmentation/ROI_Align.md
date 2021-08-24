# ROI Align

ROI pooling의 Quantization Problem을 해결하기 위해 고안된 방법으로, bilinear interpolation을 사용해서 ROI영역을 각 section으로 나눔으로써 손실 특징값을 최소화한다.



### calculate process

1. feature map에서의 ROI영역을 k × k section으로 나눈다.
2. 각 section을 다시 k × k으로 나누는 point의 x, y좌표를 계산한다.
3. 각 point에 대한 feature value를 bilinear interpolation방법으로 계산한다.
4. 계산된 각 point의 max값을 해당 section의 output으로 결정한다. 



#### 각 section의 point의 좌표 계산 방법

> 좌측 하단을 기준으로 (0, 0)이며 오른쪽이 x좌표 증가방향, 위쪽이 y좌표 증가방향이다.

ROI영역을 k × t의 section으로 나눈다고 가정하고 (i, j)번째 section의 (n, m)번째 point의 좌표 계산  ( ROI의 top left 좌표 = [x_box, y_box], 	width = w, 	height = h )
$$
P\_coord\_x_{(i, j, n, m)} = x_{box} + \frac{w}{k}(i-1) + \frac{w}{k^2}n \\
P\_coord\_y_{(i, j, n, m)} = y_{box} - \frac{h}{t}(j-1) - \frac{h}{t^2}m
$$

> 예시::
>
> feature map이 16×16이며, ROI영역을 3 × 3의 section으로 나누고 
>
> ROI의 top left 좌표 = [9.25, 10], 	w = 6.25, 	h = 4.53 일 때
>
> (1, 1) section의 (1, 1)번째 point의 x, y좌표 = [9.94, 9.5]
> $$
> P\_coord\_x_{(1, 1, 1, 1)} = 9.25 + \frac{6.25}{3}(1-1) + \frac{6.25}{9} = 9.94 \\
> P\_coord\_y_{(1, 1, 1, 1)} = 10 - \frac{4.53}{3}(1-1) - \frac{4.53}{9} = 9.5
> $$
> (1, 1) section의 (2, 2)번째 point의 x, y좌표 = [10.63, 8.99]
> $$
> P\_coord\_x_{(1, 1, 2, 2)} = 9.25 + \frac{6.25}{3}(1-1) + \frac{6.25}{9}*2 = 10.63 \\
> P\_coord\_y_{(1, 1, 2, 2)} = 10 - \frac{4.53}{3}(1-1) - \frac{4.53}{9}*2 = 8.99
> $$
> (2, 3) section의 (2, 2)번째 point의 x, y좌표 = [12.69, 5.97]
> $$
> P\_coord\_x_{(1, 1, 1, 1)} =  9.25 + \frac{6.25}{3}(2-1) + \frac{6.25}{9} 2 = 12.69\\
> P\_coord\_y_{(1, 1, 1, 1)} = 10 - \frac{4.53}{3}(3-1) - \frac{4.53}{9}2 = 5.97
> $$

![](https://github.com/HibernationNo1/TIL/blob/master/image/P_1.jpg?raw=true)



#### bilinear interpolation를 사용한 각 section의 point에서의 feature value 계산방법 

> 좌측 하단을 기준으로 (0, 0)이며 오른쪽이 x좌표 증가방향, 위쪽이 y좌표 증가방향이다.

1. point의 좌표를 계산한다.

2. point의 인접 4개 cell의 좌표를 계산한다. 

3. point에서의 feature value를 bilinear interpolation의 방법으로 계산한다.
   $$
   P \approx \frac{y - y_1}{y_2 - y_1} \left( \frac{x_2 - x}{x_2 - x_1}Q_{11} + \frac{x - x_1}{x_2 - x_1}Q_{21} \right) + 
   \frac{y_2 - y}{y_2 - y_1} \left( \frac{x_2 - x}{x_2 - x_1}Q_{12} + \frac{x - x_1}{x_2 - x_1}Q_{22} \right)
   $$

   > 예시 :: 
   >
   > point 좌표가 [9.94, 9.5]일때 
   >
   > x_1 = 9.5, x_2 = 10.5, y_1 = 8.5, y_2 = 9.5
   > $$
   > P \approx \frac{9.5 - 8.5}{9.5 - 8.5} \left( \frac{10.5 - 9.94}{10.5 - 9.5}0.1 + \frac{9.94 - 9.5}{10.5 - 9.5}0.2 \right) \\ + 
   > \frac{9.5 - 9.5}{9.5 - 8.5} \left( \frac{10.5 - 9.94}{10.5 - 9.5}1 + \frac{9.94 - 9.5}{10.5 - 9.5}0.7 \right)\\
   > = 0.144
   > $$



- 인접 4개의 cell 좌표 계산방법

  point의 x좌표가 정수값 `n` + 실수값 `f`일 때

  - `f`가 0.5보다 클 때 인접한 cell의 x좌표 : (n + 0.5, n + 1 + 0.5)
  - `f`가 0.5보다 작거나 같을때의 인접한 cell의 x좌표 : (n - 0.5, n + 1 - 0.5)

  y좌표도 동일하게 계산한다.

  

  > 예시 :: 
  >
  > point 좌표가 [12.69, 5.97]일때 인접 cell의 좌표
  >
  > (12.5, 5.5), (13.5, 6.5), (12.5, 5.5), (13.5, 6.5)
  >
  > x_1 = 12.5, x_2 = 13.5, y_1 = 5.5, y_2 = 6.5

  

##### **예시**

512×512 size의 image에서 

ROI의 size :145×200, top lest 좌표 : (396, 320), bottom right 좌표 : (496, 175)가 주어졌고,

backbone network에 의한 feature map의 size가 16×16이라고 할 때

sub-sampling ratio = 512/16 = 32임으로

feature map에서의 ROI size는 145/32, 200/32  ==  4.53×6.25 가, top left 좌표 : (9.25, 10), bottom right 좌표 : (15.5, 5.47) 임을 알 수 있다.



![](https://miro.medium.com/max/700/0*JArsNcfm3TyRj1Q8.png)

그리고 ROI pooling의 output shape이 3×3이라고 하면, 각 section의 h, w는 1.51, 2.08이게 된다.

여기서 각 section을 다시 3×3으로 나누는 point를 지정하는데,

그 point의 좌표는 아래 계산으로 구할 수 있다.

- (1, 1) section의 (1, 1)번째 point의 x, y좌표 = [9.94, 9.5]
  $$
  P\_coord\_x_{(1, 1, 2, 2)} = 9.25 + \frac{6.25}{3}(1-1) + \frac{6.25}{9}*1 = 9.94 \\
  P\_coord\_y_{(1, 1, 2, 2)} = 10 - \frac{4.53}{3}(1-1) - \frac{4.53}{9}*1 = 9.5
  $$

- (1, 1) section의 (2, 1)번째 point의 x, y좌표 = [10.63, 9.5]
  $$
  P\_coord\_x_{(1, 1, 2, 2)} = 9.25 + \frac{6.25}{3}(1-1) + \frac{6.25}{9}*2 = 10.63 \\
  P\_coord\_y_{(1, 1, 2, 2)} = 10 - \frac{4.53}{3}(1-1) - \frac{4.53}{9}*1 = 9.5
  $$

- (1, 1) section의 (1, 2)번째 point의 x, y좌표 = [9.94, 8.99]
  $$
  P\_coord\_x_{(1, 1, 2, 2)} = 9.25 + \frac{6.25}{3}(1-1) + \frac{6.25}{9}*1 = 9.94 \\
  P\_coord\_y_{(1, 1, 2, 2)} = 10 - \frac{4.53}{3}(1-1) - \frac{4.53}{9}*2 = 8.99
  $$

- (1, 1) section의 (2, 2)번째 point의 x, y좌표 = [10.63, 8.99]
  $$
  P\_coord\_x_{(1, 1, 2, 2)} = 9.25 + \frac{6.25}{3}(1-1) + \frac{6.25}{9}*2 = 10.63 \\
  P\_coord\_y_{(1, 1, 2, 2)} = 10 - \frac{4.53}{3}(1-1) - \frac{4.53}{9}*2 = 8.99
  $$
  

![](https://github.com/HibernationNo1/TIL/blob/master/image/P_1.jpg?raw=true)

그리고 각 좌표에서의 인접 cell의 x, y좌표와 feature value를 구하면 아래와 같다.

- [9.94, 9.5]의 인접 cell의 x, y좌표

  x_1 = 9.5, x_2 = 10.5, y_1 = 8.5, y_2 = 9.5
  $$
  P \approx \frac{9.5 - 8.5}{9.5 - 8.5} \left( \frac{10.5 - 9.94}{10.5 - 9.5}0.1 + \frac{9.94 - 9.5}{10.5 - 9.5}0.2 \right) \\ + 
  \frac{9.5 - 9.5}{9.5 - 8.5} \left( \frac{10.5 - 9.94}{10.5 - 9.5}1 + \frac{9.94 - 9.5}{10.5 - 9.5}0.7 \right)\\
  = 0.144
  $$
  P = 0.14

- [10.63, 9.5]의 인접 cell의  x, y좌표

  x_1 = 10.5, x_2 = 11.5, y_1 = 8.5, y_2 = 9.5

  P = 0.21

- [9.94, 8.99]의 인접 cell의  x, y좌표

  x_1 = 9.5, x_2 = 10.5, y_1 = 8.5, y_2 = 9.5

  P = 0.51

- [10.63, 8.99]의 인접 cell의  x, y좌표

  x_1 = 10.5, x_2 = 11.5, y_1 = 8.5, y_2 = 9.5
  P = 0.43

1, 1 section에 속한 P에 대하여 max값을 output으로 삼으면 0.51이 된다.

 ![](https://miro.medium.com/max/700/0*h4cpIjHPjRx2dMRc.png)

