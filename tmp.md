## project 1

- YOLO에 대한 설명

  yolo는 image를 grig cell로 나누어 각 cell안에서 object detection을 수행하는 model입니다.

- evaluation

  1. 첫 번째는 ground truth의 bbox중 예측한 bbox개수를 Recall의 계산방법에 따라 평가하고

  2. 두 번째는 1번이 100%일 때 precision계산방법에 따라 classification이 성공적으로 이루어진 경우의 비율입니다.

     이는 object의 좌표에 따라 x, y순으로 나열하여 일치한다면 success인 경우로 간주하여 계산합니다.

- YOLO의 장점과 단점

  장점 : 간단한 처리과정으로 속도가 매우 빠르고, Image 전체를 한 번에 바라보는 방식으로 class에 대한 맥락적 이해도가 높다.

  단점 : 상대적으로 다른 model군에 비해 낮은 정확도를 가지고 있다. (특히 작은 object에 대해 낮은 정확도를 가지고 있다.)

## project 2

- Mask RCNN에 대한 설명

  image에 작은 object부터 큰 object까지 존재한다고 상정한 후 각 pixel 단위로 anchor box를 만들어 object detection과 segmenstation을 수행하는 model입니다.

  - Mask RCNN의 가장 큰 특징 두 가지

    1. ROI Align입니다.

       bilinear interpolation을 사용해서 관심영역을 각 section값으로 계산하여 손실 특징값을 최소화 한 후 max pooling을 함으로써 해당 영역의 가장 큰 특징을 손실없이 잡아내는 방법입니다.

    2. Feature Pyramid Network입니다.

       pre trained model을 backbone으로 사용하여 각 stage에 따라 image의 특징을 크기순으로 잡아내어 size에 따라 anchor에 대응시킴으로써 기존 rcnn model군보다 더욱 가볍고 빠른 model을 만드는 핵심 역할이라고 생각합니다.

- Mask RCNN의 장점과 단점

  장점 : pixel단위로 instance의 존재 유무를 예측하기 때문에 segmentation이 가능하다. 

  단점 : YOLO와 같은 model군에 비해 model구성이 복잡하고 시간이 오래걸립니다.

- dataset 구현 과정에서 lung의 좌, 우 구분은 어떻게 했는지?

  image의 통일된 특징을 생각해보았습니다. 흉부 CT를 찍을 때 규정을 생각하여 각 lung의 좌표가 left 또는 right의 조건에 부합하는지 계산하여 구분하도록 했습니다.

- pre proseccing은 어떻게 적용했는지?

  1.  image의 scale에 normalization을 적용하고 0.6이하의 pixel값에는 normal distribution에 대응되는 값을 뺌으로써 lung과 뼈대의 contrast를 더욱 크게 만들었습니다.

     instance와 background의 경계가 모호한 image에 대해서 segmentation이 더욱 잘 이루어지는 결과를 얻을 수 있었습니다. (histogram equalization보다 더욱 좋은 결과를 얻음을 확인했습니다.)



# 예상 질문

- project를 하면서 어려웠던 부분과 해결한 방법

  version에 따른 개발 환경의 문제점에 가장 많이 부딫혔던 것 같습니다. 왠만한 문제는 stack overflow에 질문을 찾거나 올리면서 해결할 수 있었지만, 아직 리팩토링을 통해 model을 최신 version의 환경에서 구동하기 위해서 계속해서 문제에 직면하고 있습니다.

- 주로 오픈소스나 논문은 어디서 찾았는가?

  NIPS, CVPR, ICCV와 같이 top 컨퍼런스 중에서 관심분야의 키워드를 검색하거나 github에서 awesome키워드를 사용해 찾는 편입니다.



생육시스템