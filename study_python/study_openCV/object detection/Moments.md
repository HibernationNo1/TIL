# Moments

moments : image의 형태를 표현하는 일련의 실수값

모양 정보를 포함한 feature vector를 추출하는 방법이라고 생각해도 좋음

특정 함수 집합과의 correlation 형태로 계산한다.
$$
m_{pq} = \sum^{N-1}_{y=0}\sum^{M-1}_{x=0} x^p  y^q * f(x, y)\\
x^p  y^q : 사전에\ 정의된\ 함수
$$

> 위 식으로 추출된 실수를 moments라고 한다.
>
> x^p * y^q 에 어떠한 함수를 사용하는지에 따라서 moments의 종류가 바뀐다.



- Hu의 7개 불변 moments

  3차 이하의 정규화된 중심 moments를 조합하여 만든 7개의 moments값을 의미한다.

  image의 크기가 변하거나 회전, 이동, 대칭이 되어도 변하지 않는 moments다.



#### cv2.matchShapes()

모양을 비교하는 method.

Hu의 7개 불변 moments를 계산해서 object의 모양을 비교 후 distance값을 return한다.

> object가 찌그러지거나 블러처리 된 것 처럼 임의의 변형이 있으면 잘 동작하지 않음

두 object의 모양이 비슷하면 작은 값을 return한다.

```python
retval =  cv2.matchShapes(contour1, contour2, method, parameter)
```

- `retval` : 두 contours 또는 gray scale image 사이의 distance

- `contour1` : 첫 번째 외곽선 coordinate 또는 gray scale image

- `contour2` : 두 번째 외곽선 coordinate 또는 gray scale image

- `method` : 비교 방법

  > `cv2.CONTOURS_MATCH_I1`
  >
  > `cv2.CONTOURS_MATCH_I2`
  >
  > `cv2.CONTOURS_MATCH_I3` : 가장 추천되는 방법
  >
  > ![](https://blog.kakaocdn.net/dn/kxLAG/btqKSfLxpI8/F2ww9ifxlNqu4sDlE1Pv41/img.png)

- `parameter` : 사용되지 않음. 0 지정

