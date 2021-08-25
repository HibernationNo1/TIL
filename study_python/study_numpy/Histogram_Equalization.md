# Histogram Equalization

히스토그램 균일화는 image의 명암 대비(Contrast)를 개선시키는 방법으로, Histogram이 gary scale 전체 구간에서 균일한 분포로 나타나도록 변경하는 명암비 향상 기법이다.

>  image의 pixel값을 0부터 255까지 균일하게 퍼트리는 계산을 의미한다.

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fm0Flr%2FbtqJP7HEfE3%2FRXPu8UJJMhWrOJkHQy5DGK%2Fimg.png)
$$
Histogram\ function:\ h(g) = N_g \\
nomalized\ Histogram\ function: \ p(g) = \frac{h(g)}{w*h}\\
누적\ 분포\ 함수(cdf) : \ cdf(g) = \sum_{0 =< j<g} p(i)
$$

$$
dst(x, y) = round(cdf(src(x, y))*L_{max})
$$


Histogram Equalization의 결과는 밝은 이미지나 어두운 이미지 어떤 것을 사용해도 동일한 결과를 도출한다.



CV2의 `cv2.equalizeHist(src, dst = None)`를 통해 계산이 가능하다.



**numpy구현**

```python
def preprocessing_HE(img_):
    hist, _ = np.histogram(img_.flatten(), 256,[0,256])		# histogram
    cdf = hist.cumsum()										# 누적합
    cdf_m = np.ma.masked_equal(cdf,0)						# 0인 element는 mask처리
    cdf_m = (cdf_m - cdf_m.min())*255/(cdf_m.max()-cdf_m.min()) # Histogram equalization
    cdf = np.ma.filled(cdf_m,0).astype('uint8')				# np.ma.masked_equal로 인해 mask처리된 element를 0으로 
    img_2 = cdf[img_]
    
    return img_2  
```

