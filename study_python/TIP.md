### sys.modules

실행되는 code의 path를 숨길 때 사용



tmp_1.py

```
exam_function = None
```



tmp_2.py 

```
class Exam(sys.modules[__name__].__class__):

	@property
	def exam_function(self):		# 속성 정의
		...

sys.modules['modules.tmp_1'].__class__ = Shared
```



tmp_3.py 

```
from path import tmp_1
tmp_1.exam_function
```

위 한 줄만 있어도 `Exam` class의 `exam_function`이 실행된다.