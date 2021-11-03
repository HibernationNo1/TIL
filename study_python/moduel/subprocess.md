# subporcess

subporcess의 주요한 목적은, 현재 source code안에서 다른 프로세스를 실행하게 해주며 그 과정에서 데이터의 입출력을 제어하기 위함

인터프리터에서 source code를 작성하고 실해하면, 그 결과가 shell에 출력되는 것이 일반적인 코딩이다.

하지만 subpocess를 사용하면 script에서 실행된 입출력값을 간편하게 제어할 수 있다.



원래 이러한 기능은 system, os에서 담당하고 있었으나, python 3.x로 오면서 subporcess가 그 기능을 대신하게 되었다. 

또한 system, os는 보안상 심각한 결함을 발생시킬 수도 있으므로 subprocess를 쓰는 것이 더 안전하다.



subporcess module은 새로운 프로세스를 실행하도록 도와주고, 프로세스의 입출력 및 에러 결과에 대한 return code를 user가 직접 제어하게 해주는 module이다.



```python
import subporcess
```



### run

`os.system`과 같은 동작을 한다.

차이점 : 가상환경 activate가 가능

```python
subprocess.run('activate detectron2 && python inference_detectron2.py', shell=True)
```

- `activate detectron2` : detectron2라는 가상환경 실행
- `&&` : 이것을 기준으로 명령입력이 추가됨
- `python inference_detectron2.py` :  `inference_detectron2.py` 을 실행



