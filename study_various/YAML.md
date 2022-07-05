# YAML

데이터 직렬화에 쓰이는 format

> 데이터 직렬화 : service간에 data를 전송할 때 쓰이는 format으로 변환하는 작업
>
> XML, JSON역시 데이터 직렬화에 쓰이는 format이다.

`.yaml`, `.yml`



## 문법

key-value 문법

```yaml
apiVErsion : v1
Kind : pod
metadata : 
	name : example_1

# 주석
example : "string"

# - 를 사용하여 list를 명시
list_1 : 
	- ex_one : 1
	- ex_two : 2
# 또는 []
list_2 : ["1", "2", "3"]

# | 사용 
example_ : |
	Hello
	hiber
	nation
	# "Hello
	hiner
	nation"
	으로 인식됨. 빈 줄을 \n으로 처리

example_ : >
	Hello
	hiber
	nation
	# "Hello hiber natio"n 으로 인식됨. 빈 줄을 ' '으로 처리
	
# --- 를 통해 하나의 yaml에 여러개의 yaml을 작성 가능

---
apiVErsion : v2
Kind : pod
metadata : 
	name : example_2
```

