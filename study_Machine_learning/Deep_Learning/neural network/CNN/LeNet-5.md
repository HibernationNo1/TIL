# LeNet - 5

LeNet - 5 Architecture

![](https://debuggercafe.com/wp-content/uploads/2019/06/LeNet-5.png)

![](https://debuggercafe.com/wp-content/uploads/2019/07/Layers-in-LeNet.png)

Gray scale input

---

LeNet - 5에서 사용하는 pooling filter는 Average Pooling임





- **when through layer == 1** 

  shape of weight(tensor) == shape of channel
  $$
  (H_f, W_f, D_{in}, D_{out})\\
  w.shape = (5, 5, 1, 6)
  $$
  

  shape of bais
  $$
  b.shape = (6, )
  $$
  즉, number of parameters = (5 * 5 * 1 * 6) + 6= 150

  

  그리고 shape of output image는 아래와 같다
  $$
  W_1 = H_1 = \left[ \frac{H_{n-1} + 2p - k}{s}  \right] + 1 = \left[ \frac{32 + 0 - 5}{1} \right] + 1 \\= 28
  \\
  $$

  $$
  img.shape = (28, 28, 6)
  $$

  



- **when through layer == 2** 

  shape of image
  $$
  W_2 = H_2 = \left[ \frac{28 + 0 - 2}{2} \right] + 1 \\= 14
  $$
  channel 수는 변함이 없기 때문에 D_in == 6
  $$
  img.shape = (14, 14, 6)
  $$
  
- **when through layer == 3** 

  shape of weight(tensor) == shape of channel

  feature map을 16개 만들거기 때문에 D_out == 16
  $$
  w.shape = (5, 5, 6, 16)
  $$
  

  shape of bais
  $$
  b.shape = (16, )
  $$
  즉, number of parameters = (5 * 5 * 6 * 16) + 16= 2416

  

  

  shape of image
  $$
  W_3 = H_3 = \left[ \frac{14 + 0 - 5}{1} \right] + 1 \\= 10
  $$

  $$
  img.shape = (10, 10, 16)
  $$

  

  

- **when through layer == 4** 

  shape of image
  $$
  W_4 = H_4 = \left[ \frac{10 + 0 - 2}{2} \right] + 1 \\= 5
  $$

- **when through layer == 5** 

  shape of weight(tensor) == shape of channel

  output의 channel이 120개임
  $$
  w.shape = (5, 5, 16, 120)
  $$
  

  shape of bias
  $$
  b.shape = (120, )
  $$
  

  즉, number of parameter = (5 * 5 * 16 * 120) + 120= 48120

  

  shape of output
  $$
  W_4 = H_4 = \left[ \frac{5 + 0 - 5}{1} \right] + 1 \\= 1
  $$

  $$
  img.shape = (1, 1,120)
  $$

  

  Apply Flatten 

  shape of data
  $$
  data.shape = (120, )
  $$



- **when through layer == 6** 

  neural 하나당 weight 120개, bias 1개 이고, Fully connected의 size = 84이므로

  number of parameters = (120 + 1) * 84 = 10164

  

  shape of data = (84, )



- **when through output layer** 

  number of parameters = (84 + 1) * 10 = 850

  shape of data = (10, )

  각각의 data는 10가지의 class를 나누고 각각의 probabiliy를 나타낸다.



**capacity**

이 network가 가진 전체 capacity =  150 + 2416 + 48120 + 10164 + 850

