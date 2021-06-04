# GrabCut

GrabCut: 영역 분할 algorithm 중 하나로, image의 pixel을 (자료구조의)grahp의 정점으로 간주하고, pixel들을 background와 object의 group으로 나누는 최적의 컷을 찾는 방식

> 누끼 따는 algorithm
>
> 단, input image가 배경과 전경의 분할이 쉬운 image여야 효과가 좋음 (그래서 잘 사용 안됨)

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQlQK4E5pggznF_G-1Jup4vpl2LNlNNAwEk9iePchGbWFo-UojVWNRkH1fMMpjs1JTI3L0&usqp=CAU)

GrabCut에는 두 가지 동작 방식이 있다.

- 사각형 지정 자동 분할
- 사용자가 지정한 전경, 배경 정보를 활용하여 영상 분할



#### cv2.grabCut()

```python
mask, bgdModel, fgdModel = cv2.grabCut(img, mask, rect, bgdModel, fgdModel, iterCount, mode = None)
```

- `img` : input image (8bit 3 chennal)

- `mask` : 입, 출력 mask image

  > 출력 시 위 개의 값으로 구성됨.
  >
  > {`'0' : cv2.GC_BGD`, `'1': cv2.GC_FGD`, `'2' : v2.GC_PR_BGD`, `'3' : cv2.GC_PR_FGD`}
  >
  > `cv2.GC_BGD` : background
  >
  > `cv2.GC_FGD: foreground
  >
  > `cv2.GC_PR_BGD : probabiliy background (불분명하지만 background 일 수도 있는 것)
  >
  > `cv2.GC_PR_FGD : probabiliy foreground
  >
  > 위 네 개의 값으로 구성됨.
  >
  > 초기화 : mode = `cv2.GC_INIT_WITH_RECT`

- `rect` : ROI 영역

  > `cv2.GC_INIT_WITH_RECT` 모드에서만 사용됨

- `bgdModel` : 임시 background model metrix. 같은 영상 처리 시에는 변경 금지

  > None으로 줘도 내부에서 만들어 사용. 단, updata를 하며  iteration을 돌릴 시에는 줘야함
  >
  > initial :`bgdModel np.zeros((1, 65), np.float64)`

- `fgdModel` :  임시 foreground model metrix. 같은 영상 처리 시에는 변경 금지

  > None으로 줘도 내부에서 만들어 사용. 단, updata를 하며  iteration을 돌릴 시에는 줘야함
  >
  > initial :`fgdModel np.zeros((1, 65), np.float64)`

- `iterCount` : 결과 생성을 위한 반복 횟수

- `mode` :

  > 보통 `cv2.GC_INIT_WITH_RECT` 으로 초기화 하고, `cv2.GC_INIT_WITH_MASK` mode로 업데이트



**예제1 **

bgdModel, fgdModel = None

초점이 확실히 나눠진, 간단한 object 누끼 따기

```python
src = cv2.imread('image.jpg')

if src is None:
    print('Image load failed!')
    exe.exit()

rc = cv2.selectROI(src) # 마우스로 사각형을 지정해서 초기 분할

mask = np.zeros(src.shapep[:2], np.uint8)

cv2.grabCut(src, mask, rc, None, None, 5, cv2.GC_INIT_WITH_RECT)
# 5번 수행

mask2 = np,where((mask == 0) or (mask == 2), 0, 1).astype('uint8')
# 확실하게 background 이거나 background일 가능성이 있는 pixel은 0으로, 아닌것은 1로

dst = src * mask2[:, :, np.newaxis]
# 목표 object만 누끼를 따고, background는 0의 값을 가진 image

cv2.imshow('dst', dst)
cv2.waitKey()
cv2.destroyAllWindows()
```





**예제2**

bgdModel, fgdModel을 통해 계속 updata해가며 누끼 따기

mouse event를 통해 누끼를 따고싶은 영역을 지정 후 누끼 따기

```python
src = cv2.imread('image.jpg')

if src is None:
    print('Image load failed!')
    exe.exit()
    
# 사각형 지정을 통한 초기 분할
mask = np.zeros(src.shapep[:2], np.uint8)
bgdModel = np.zeros((1, 65), np.float64)
fgdModel = np.zeros((1, 65), np.float64)

rc = cv2.selectROI(src)
    
cv2.grabCut(src, mask, rc, bgdModel, fgdModel, 1, cv2.GC_INIT_WITH_RECT)    

# 초기 grabCut 출력
cv2.imshow('dst', dst)

def on_mouse(event, x, y, flags, param):
    if event == cv2.EVENT_LBUTTONDOWN: # 마우스 왼쪽 버튼 클릭
        cv2.circle(dst, (x, y), 3, (255, 0, 0), -1)
        cv2.circle(mask, (x, y), 3, cv2.GC_FGD, -1)
        cv2.imshow('dst', dst)
    elif event == cv2.EVENT_RBUTTONDOWN: # 마우스 오른쪽 버튼 클릭
        cv2.circle(dst, (x, y), 3, (0, 0, 255), -1)
        cv2.circle(mask, (x, y), 3, cv2.GC_BGD, -1)
        cv2.imshow('dst', dst)
    elif event == cv2.EVENT_MOUSEMOVE:
        if flags & cv2.EVENT_FLAG_LBUTTON: # 마우스 왼쪽 버튼 눌린상태로 마우스 moving
        	cv2.circle(dst, (x, y), 3, (0, 0, 255), -1)
        	cv2.circle(mask, (x, y), 3, cv2.GC_FGD, -1)
        	cv2.imshow('dst', dst)
        if flags & cv2.EVENT_FLAG_RBUTTON: # 마우스 오른쪽 버튼 눌린상태로 마우스 moving
        	cv2.circle(dst, (x, y), 3, (0, 0, 255), -1)
        	cv2.circle(mask, (x, y), 3, cv2.GC_BGD, -1)
        	cv2.imshow('dst', dst)
            
cv2.setMouseCallback('dst', on_mouse)

# 마우스 이벤트로 얻은 정보를 통해 cv2.GC_INIT_WITH_MASK 모드로 segmentation 진행
# Enter를 누르면 cv2.GC_INIT_WITH_MASK 모드로 grabCut을 업데이트
while True:
    key = cv2.waitKey()
    if key == 13: # Enter
        cv2.grabCut(src, mask, rc, fgdModel, 1, cv2.GC_INIT_WITH_MASK)
        mask2 = np,where((mask == 0) or (mask == 2), 0, 1).astype('uint8')
        dst = src * mask2[:, :, np.newaxis]
        cv2.imshow('dst', dst)
        
    elif key == 27 : #ESC
        break
        
cv2.destroyAllWindows()
```



