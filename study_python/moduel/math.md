# math

```python
import math
```



#### floor()

```python
res = math.floor(x)
```

x보다 작거나 같은 가장 큰 정수인 x의 바닥값(floor를 반환) 

x의 내림수





#### isqrt()

```python
res = math.isqrt(n)
```

음이 아닌 정수 n의 정수 제곱근을 return



#### modf()

```python
res_i, res_f = math.modf(x)
```

x의 소수와 정부 부분을 return.  두 결과 모두 x의 부호를 가지며 float임





#### exp()

```python
res = math.exp(x)
```

e의 x거듭제곱을 return





#### expm1()

```python
res = math.expm1(x)
```

e의 x거듭제곱에서 1을 뺀 값

`exp(x)-1` 보다 더욱 정확함





#### log()

```python
res = math.log(x, base)
```

base없이 인자가 제공되면 x의 자연로그(밑 = e) 를 return

base와 함께 인자가 제공되면 밑 = base인 x의 log를 return



#### log2()

```python
res = math.log2(x)
```

밑이 2인 x의 log를 return



#### log10()

```python
res = math.log10(x)
```

밑이 10인 x의 log를 return





#### sin(), cos() tan()

```python
res = math.sin(x)
res = math.cos(x)
res = math.tan(x)
```





#### hypot()

```python
coordinates = [x, y]
res = math.hypot(coordinates)
```

원점부터 유클리드 distance를 return





#### degrees(), radians()

```python
res = math.degress(x) # x를 radian에서 degree로 변경
res = math.radians(x) # x를 degree에서 radian로 변경
```





#### e, pi

```python
res = math.pi
res = math.e
```

