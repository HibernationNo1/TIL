# PIL

image작업을 위한 표준 절차를 제공하는 module

```
$ pip install pillow
```





## Image

```python
from PIL import Image
```



### open()

image를 load한다.

```python
img = Image.open(path)

print(type(img))  # <calss 'PILJpegImagePligin.JpegImageFile'>
```





### new()

새로운 image를 만든다.

```python
Image.new(mode, size, color = 0)
```

- `mode` : image의 mode

  > `RGB` :  (3x8-bit pixels, true color)
  >
  > `HSV` : (3x8-bit pixels, Hue, Saturation, Value color space)
  >
  > `L` : (8-bit pixels, black and white)

- `size` : 만들고자 하는 image



### <calss 'PIL'>

#### show()

` <calss 'PILJpegImagePligin.JpegImageFile'> ` type의 image를 보여준다.

```python
img.show()
```



#### meta data

- `img.filename` 
- `img.format` : file의 형식 
- `img.size` : image file의 size
- `img.mode` : image의 색상 모드 (RGB)
- `img.width` ,  `img.height`



#### resize()

```python
resize_img = img.resize(shape)
```

> resize할 때 resampling을 진행한다. 해당 option은 검색해보기.



#### paste()

PIL class인 `dst`을 `scr` 로 대체한다. 같은 size여야 가능

```python
dst.paste(scr)
```

- `dst`
- `scr`