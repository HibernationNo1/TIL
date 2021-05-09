# AlexNet

![](https://i.imgur.com/CwIvlUW.png)

 AlexNet using two GPU

![](https://seongkyun.github.io/assets/post_img/study/2019-01-25-num_of_parameters/fig2.png)

Color scale input

위 그림에서 input image의 shape = (224, 224) 이지만 논문상 오류이므로 227을 사용해야 된다고 한다.

- **when through layer == 1** 

  shape of weight(tensor) == shape of channel

  > output channel = 48
  >
  > GPU 2개 사용하기 때문에 *2

  $$
  (H_f, W_f, D_{in}, D_{out})\\
  w.shape = (11, 11, 3, 48*2)
  $$


  shape of bais
  $$
  b.shape = (48*2 )
  $$
  

  shape of output image
  $$
  W_1 = H_1 = \left[ \frac{H_{n-1} + 2p - k}{s}  \right] + 1 = \left[ \frac{227 + 0 - 11}{4} \right] + 1 \\= 55
  \\
  $$

  $$
  img.shape = (55, 55, 48 * 2)
  $$

  



- **when through layer == 2** 

  shape of image

  pooling이 곧 filter이기 때문에 p == k

  
  $$
  W_2 = H_2 = \left[ \frac{55 + 5 - 5}{1} \right] + 1 \\= 27
  $$

  $$
  img.shape = (27, 27, 48 * 2)
  $$

  

