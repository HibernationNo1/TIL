# Faster R-CNN

Image segmentation을 수행하는 network로, End-to-End로 학습이 진행된다.

Fast RCNN의 구조에서 Selective Search을 통해 ROI을 구하던 Region proposals 과정을

Region Proposal Network(RPN)을 통해 ROI을 구하도록 그 방법을 바꾸었다.

- **Fast RCNN**

  ​            ┌           CNN        	 	┐

  image │					   		     ├  RoI pooling ─ Fully connected

  ​            └  Selective Search 	┘

  ​                          1단                                 2단                    3단

  

- **Faster R-CNN**

  image ─ CNN 		       	┐

  ​                   │		  	    	├  RoI pooling ─ Fully connected

  ​                   └       RPN   	┘

  ​                 1단      1.5단                2단                    3단



**동작 과정**

![](https://bloglunit.files.wordpress.com/2018/08/ec8aa4ed81aceba6b0ec83b7-2018-08-13-ec98a4ed9b84-2-30-31.png?w=633&h=200)

1. Image를 VGG기반의 CNN에 통과시겨 Feature map을 얻는다.

2. Feature map을 Region Proposal Network(RPN)의 input으로 사용하여 Region Proposals 과정을 수행한다.

   > RPN : feature map을 보고 어느 위치에 object가 있을법한지 추론하는 network

3. RPN의 output에 대해서 RoI pooling을 수행한다.

4. ROI pooling의 output인 feature map을 fully connected layer input으로 넣는다.

5. 1. FC layer의 output에 대해서 regression을 진행한다.
   2. FC layer의 output에 대해서 softmax를 진행한다.





## Training

Faster R-CNN은 RPN이 제대로 ROI를 계산해야 뒷 단의 network가 학습이 되기때문에 

이를 위해 4단계에 걸쳐서 model을 번갈아서 학습시키는 Alternation Training 기법을 취한다.

1. **Anchor box를 생성한다.**

   Anchor generation layer를 통해 Anchor를 생성한다.

2. **ImageNet pretrained 모델(ZF 또는 VGG)을 불러온 다음, RPN을 학습시킨다.  (`M1`)**

   1. Anchor target layer를 통해 1번 단계에서 생성된 Anchor를 sampling한다.
   2. sampling된 Anchor로 RPN을 학습한다. (pre-trained VGG도 학습된다.)

3. **2번 단계에서 학습시킨 RPN에서 initial ROI를 뽑는다. (`P1`)**

   1. RPN을 통해 class score, bounding box regressor를 반환한다.
      1. feature map을 PRN의 Intermediate Layer input으로 받는다.
      2. Intermediate Layer의 output을 Classification Layer, Regression Layer의 input으로 입받는다.
      3. Classification Layer을 통해 class score를, Regression Layer를 통해 bounding box regressor를 반환한다.

   2. 1번 단계에서 생성한 anchor와 class score, bounding box regressor를 통해 region proposals를 추출한다.
      1. Anchor에 bounding box regressor를 적용하여 Anchor가 객체의 위치를 더 잘 detection하도록 조정한다.
      2. Anchor에 class score을 적용하여 class score기준으로 내림차순 정렬한다.
      3. Non maximum suppression을 적용하여 class score 상위 N개의 Anchor를 추출한다.
      4. NMS의 결과는 메모리 상에서 구멍이 뚫린 형태가 되기 때문에, 이를 위해 ROI를 연속된 형태로 모아준다. (ROI 계산 완료)

4. **`M1`과 `P1`을 사용해서 Fast R-CNN을 학습시킨다. (`T1`)**

   1. Proposal target layer을 통해 `P1`을 sampling한다.
   2. `M1`과 sampling된 ROI로 Fast R-CNN을 학습한다.(pre-trained VGG도 학습된다.)

5. **4번 단계에서 학습시킨 `T1`를 가져와서 RPN을 학습시킨다. (`M2`)**

   > 단, 이때 원본 image를 학습하는 CNN은(1단에 위치한 CNN)학습에 참여하지 않도록 pix시킨다.
   >
   > 세부 학습 과정은 2번 단계와 동일하다.

6. **5단계에서 학습된 `M2`에서 ROI를 뽑는다. (`P2`)**

   > 세부 과정은 3번 단계와 동일하다.

7.  **`M2`와 `P2`를 사용해서 Fast R-CNN을 학습시킨다. (`T2`)**

   > 세부 과정은 4번 단계와 동일하다.

8. **7번 단계에서 탄생한 `T2`가 학습이 완료된 Faster R-CNN이다.**

   (`T2`를 통해 `M3`를 학습시키는, 4~6단계를 반복할 수 있다. 하지만 논문에서는 이 이상 반복을 해 보아도 학습 결과에는 크게 변화가 없었다고 한다.)



![](https://github.com/HibernationNo1/TIL/blob/master/image/Fast_R-CNN.jpg?raw=true)



- Proposal target layer

  ROI중에서 Fast R-CNN 모델을 학습시키기 위한 유용한 ROI을 선택하는 layer

  1. 전체 ROI중에 IOU가 0.5이상인 경우 Positive ROI, 0.1~0.5인 경우 Negative ROI이다.



- Anchor target layer

  Anchor중에서 RPN이 학습하는데 사용할 수 있는 Anchor를 선택하는 layer

  1. 생성한 Anchor box중에서 원본 image의 경계를 벗어나지 않는것들만 선택한다.

  2. 선택한 Anchor box중에서 IOU가 0.7이상인 것은 Positive Anchor, IOU가 0.3이하인 것은 Negative Anchor로 선정한다. 

     > Positive Anchor는 object를 의미하고 Negative Anchor는 background를 의미한다.
     >
     > 그 사이의 iou값을 가진 Anchor는 버린다. 

  3. Anchor samples을 할 때 positive samples과 negative samples의 비율을 1:1로 한다





#### Results

|                                           | R-CNN      | Fast R-CNN | Faster R-CNN    |
| ----------------------------------------- | ---------- | ---------- | --------------- |
| Test time per image<br />(with proposals) | 50 seconds | 2 seconds  | **0.2 seconds** |
| speedup                                   | 1×         | 25×        | **250×**        |
| mAP(VOC 2007)                             | 66.0       | 66.9       | **69.9**        |









