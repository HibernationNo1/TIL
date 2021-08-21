# Image Segmentation

object detection방법으로, bounding box로 표현되는것이 아닌, 특정 pixel이 target class에 속하는지 아닌지를 분류한다.

사전 훈련된 detection network와 사전 훈련된 classification network를 하나로 이어서 end-to-end 방식으로 학습한다.



Object detection 방식

### 2-Stage Detector

object의 위치를 찾는 문제(localization)와 분류(classification)문제를 순차적으로 해결한다.

**image** >> [**Region proposals**] >> [**Feature Extractor** >> **Calssification**, **Regression**]

- Region proposals : object가 존재할법한 위치 제안(object가 존재할법한 위치를 찾아 나열하는 과정)



#### R-CNN

![](https://lilianweng.github.io/lil-log/assets/images/RCNN.png)

1. CPU상에서 Input image에 대해 Selective Search를 진행한다. (Region proposals)

2. Selective Search통해 얻은 위치 정보를 각각 CNN의 input으로 사용해 feature vector를 추출한다.

3. 1. 각각의 feature vector에 대해서 SVM(Support Vector Machine)를 사용해 classification을 진행한다.

   2. 각각의 feature vector에 대해서 Regressorsion을 진행한다.



- 단점 

  Selective-search 등을 이용하여 찾아낸 RP마다 CNN을 적용해야 해서 속도가 느리다.

  > Selective-search * CNN 의 연산을 수행

  SVM과 regression model까지 학습이 진행되다 보니 더 많은 비용이 소모된다.



#### Fast R-CNN

![](https://i.ytimg.com/vi/kcPAGIgBGRs/maxresdefault.jpg)

R-CNN의 단점을 보안해서 보다 더 빠른 결과를 제공하는 모델이다.

1. 1. CPU상에서 Input image에 대해 Selective Search를 진행한다. (Region proposals)

   2. input image에 CNN을 적용한다.

2. CNN의 output인 feature map에서 Selective Search로 얻어진 ROI영역을 위치시킨 후 해당 영역에 대해서만 max pooling을 적용한다. (ROI pooling)

3. ROI pooling의 output인 feature map을 fully connected layer input으로 넣는다.

4. 1. FC layer의 output에 대해서 regression을 진행한다.
   2. FC layer의 output에 대해서 softmax를 진행한다.



- 개선점 

  모든 RP(Region proposals)에 대해 각각 convolution 연산을 하지 않고, 입력 이미지에 한번만 CNN을 적용하고 RoI pooling으로 Feature Extractor를 진행한다.

  > (Selective-search + ROI) + 1의 연산을 수행

  

#### Faster R-CNN

![](https://user-images.githubusercontent.com/46951365/91658450-22d47680-eb03-11ea-9524-24311d6c43c4.png)

1. Image를 CNN에 통과시겨 Feature map을 얻는다.

2. Feature map을 Region Proposal Network(RPN)의 input으로 사용하여 Region Proposals 과정을 수행한다.

   > RPN : feature map을 보고 어느 위치에 object가 있을법한지 추론하는 network

3. RPN의 output에 대해서 RoI pooling을 수행한다.

4. ROI pooling의 output인 feature map을 fully connected layer input으로 넣는다.

5. 1. FC layer의 output에 대해서 regression을 진행한다.
   2. FC layer의 output에 대해서 softmax를 진행한다.



- 장점 : RPN을 통해 전체 framework를 End-to-End로 학습한다.
- 단점 : 여전히 많은 component로 구성되며, Region Classification단계에서 각 feature vector는 개별적으로 FC layer로 Forward된다.



### 1-Stage Detector

object의 위치를 찾는 문제(localization)와 분류(classification)문제를 한 번에 해결한다.

**image** >> [**Feature Extractor** >> **Calssification**, **Regression**]







