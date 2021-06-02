# Morphology

Morphology 연산이란? : image를 형태학적인 측면에서 다루는 기법으로, 다양한 영상 처리 시스템에서 pre-processing 또는 post-processing 형태로 널리 사용된다.



동작: Structuring element가 kernel이 되어 window slicing을 하며 특정 조건이 만족하면 특정 연산을 하는 동작이다.

> CNN의 convolution과는 살짝 비슷하다.



**Structuring element**(구조 요소)

모폴로지 연산의 결과를 결정하는 kernel, mask, window를 의미한다. 

Structuring element이 특정 조건을 만족할 경우 연산을 적용하는 Structuring element 내부의 pixel을 **고정점**이라고 한다.



Morphology 연산에는 침식(erosion), 팽창(dilation) 두 가지가 있다.



### erosion

object의 외각을 깎아내는 연산으로, object의 크기는 감소하고, background는 확대된다.

Structuring element가 object 영역 내부에 완전이 포함될 경우 고정점 pixel을 0으로 설정하는 계산 방법

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcTNY3qN-ILYigKFUDMD7vETF8ayRQ8gMdFZFQ&usqp=CAU)

주로 image에 작은 크기의 object를 지우는데 사용된다. (배경 위의 사람 지우듯)



#### cv2.erode()

```python
dst = cv2.erode(src, kernel, dst = None, anchor = None, iterations = None,
         borderType = None, borderValue = None)
```

`src` : input image (gray scale)

`kernel` : Structuring element 

> - `cv2.getStructuringElement()` 에 의해 생성 가능.
>
> None으로 지정하면 3×3 kernel을 사용 (보통 걍 None을 사용)

`dst` : output image

> input image와 같은 size, type

`anchor` : 고정점 위치

> default =  (-1, -1) :  Structuring element의 중앙을 고정점으로 사용

`iterations` :  반복 횟수

> default =  1

`borderType` : 가장자리 pixel 확장 방식

> default `cv2.BORDER_CONSTANT`

`borderValue` : None





### dilation

object의 외각을 팽창시키는 연산으로, object의 크기는 확대되고, background는 감소한다.

구조 요소와 object 영역이 한 pixel이라도 만날 경우 고정점 pixel을 255로 설정하는 계산 방법

![](https://thezeroalpha.github.io/physcomp-notes/Morphological%20operations.resources/screenshot_1.png)

주로 object 안에 존재하는 작은 배경을 지우는데 사용된다. (얼굴 위의 잡티를 지우거나 끊어진 줄을 지어줄 때)





#### cv2.dilate()

```python
dst = cv2.dilate(src, kernel, dst = None, anchor = None, iterations = None,
         borderType = None, borderValue = None)
```

각 parameter의미는 `erode()`와 같다





##### cv2.getStructuringElement()

Structuring element의 모양을 임의로 결정하거나 만들어서 사용할때 사용

```python
retval = cv2.getStructuringElement(shape, ksize, anchor = None)
```

`shape` : Structuring element 모양을 나타내는 flag

> `cv2.MORPH_RECT` : 사각형 모양
>
> `cv2.MORPH_CROSS` : 십자가 모양
>
> `cv2.MORPH_ELLIPSE` : 사각형에 내접하는 타원

`ksize` : Structuring element size

> (width, height) type: tuple

`anchor`  : Structuring element으로 `cv2.MORPH_CROSS` 을 사용할 때 고정점 좌표

> (-1, -1) 을 지정하면 Structuring element의 중앙을 고정점으로 사용

`retval` : 0과 1로 구성된 cv2.CV_8UC1 타입의 metrix (ndarray)

> 1의 위치가 Structuring element모양을 결정





#### ex

```python
src = cv2.imread("image.png", cv2.IMEAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    sys.exit()
    
se1 = cv2.getStructuringElement(cv2.MORPH_RECT, (5, 3))
dst1 = cv2.erode(src, se1)

dst2 = cv2.dilate(src, None)

se2 = cv2.getStructuringElement(cv2.MORPH_RECT, (1, 7)) # | 모양의 kernel
dst3 = cv2.dilate(src, se2) # 위 아래로만 팽창

cv2.imshow('src', src)
cv2.imshow('dst1', dst1) 
cv2.imshow('dst2', dst2) 
cv2.imshow('dst3', dst3) 

cv2.waitKey()
cv2.destroyAllWindows()
```





### opening

opening ==  Erosion  ->  Dilation

연산 효과 : 작은 돌기나 object가 사라지고, 얇은 연결선이 끊어짐

(주로 noise를 제거하는 용도로 사용)



### closing

closing ==  Dilation  ->  Erosion

연산 효과 : 작은 홈, 작은 홀이 사라지고, 얇은 연결선이 두꺼워짐

![](https://www.researchgate.net/profile/Budi-Setiyono-2/publication/317312246/figure/fig5/AS:503607678205952@1497080835957/Closing-Operation-in-Image-Morphology.png)



### gradient

gradient ==  (Dilation - Erosion)





#### cv2.morphologyEx()

dilation, erosion 뿐 아니라 opening, closing 까지도 지원하는 method

```python
dst = cv2.morphologyEx(src, op, kernel, dst = None, anchor = None, 
                 iterations = None, borderType = None, borderValue = None)
```

`src` : input image (gray scale)

`op` : morphology 연산 flag

>`cv2.MORPH_ERODE` : erosion
>
>`cv2.MORPH_DELATE` : dilate
>
>`cv2.MORPH_OPEN` : opening
>
>`cv2.MORPH_CLOSE` : closing
>
>`cv2.MORPH_GRANDIENT` : gradient

`kernel` : Structuring element

`dst` : output image



```python
src = cv2.imread("image.png", cv2.IMEAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    sys.exit()
    
# 지역 이진화
C = 5
bsize = 33
dst1 = cv2.adaptiveThreshold(src, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
                               CV2.THRESH_BINARY, bsize, C)


cnt1, _ = cv2.connectedComponents(dst1)
# connectedComponents : image 안의 object(흰색 덩어리들)의 개수를 return

dst2 = cv2.morphologyEx(dst1, cv2.MORPH_OPEN, None)
# opening 수행

cnt2, _ = cv2.connectedComponents(dst2)

cv2.imshow('src', src)
cv2.imshow('dst1', dst1) 
cv2.imshow('dst2', dst2) 
print(cnt1, cnt2)  # opening 수행 전 후 작은 object의 개수가 줄어든걸 알 수 있다.

cv2.waitKey()
cv2.destroyAllWindows()
```

