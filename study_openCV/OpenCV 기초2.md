# OpenCV 기초2



- image에서 pixel값 가져오기

  ```python
  img = cv2.imread('cat.bmp')
  
  x = 20
  y = 10
  pix = img[x, y]
  print(pix)  # x, y좌표의 픽셀 BGR scale을 알 수 있다.
  
  # imp를 만약 GRAYSCALE로 받았다면 해당 좌표의 garyscale값을 알 수 있다.
  ```

  index 접근 방법을 이용해서 해당 pixel의 값을 바꿀 수도 있다

  ```python
  img[x, y] = (0, 0, 255)
  img[x:, y:] =  (0, 255, 255)
  ```

  

