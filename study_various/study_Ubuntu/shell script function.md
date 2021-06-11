# shell script function



alias란?





지역 변수를 및 함수를 계정에 설정하는 방법

```
vi .bash_profile
```

```
vi .bashrc
```



함수 선언하는 방법



설정을 적용하고 나서, 다시 login을 해야 적용한 설정이 반영된다.

> 단, source 명령어를 사용하면 logout하지 않아도 설정을 반영할 수 있다.

- `source` : file을 읽어서 실행하는 명령어 (`.` 라고 해도 됨)

  ```
  source .bash_profile   # 또는
  . .bash_profile
  ```

  위 명령어를 실행하면 logout하지 않아도 설정을 반영할 수 있다.

