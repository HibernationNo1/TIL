# argparse

```python
import argparse
```



## argparse.ArgumentParser()

define instance

```python
parser = argparse.ArgumentParser(description='descript argparse for what')
```



### add_argumen()

ArgumentParser에 program 인자에 대한 정보를 추가할때 사용한다. 이 정보는 저장되고, **parse_args()**가 호출될때 사용된다. (`args = parser.parse_args()`)

```python
parser.add_argumen("--exam")
```

- `"--exam"` : option 인수

  > `"-e" `와 같이 약자를 추가로 지정할수도 있다.
  >
  > `"--"` 가 붙지 않을 경우, option인수로 할당은 가능한데, `--` 가 붙은 인수들보다 우선수위가 된다. 

- `help =` : 해당 인수의 설명 (str)

- `type =` : 해당 인수의 type을 결정한다. `int` 를 할당하면, 해당 인수를 int형으로 받는다.

- `defualt = ` : 해당 옵션을 받지 않는 경우, default값을 할당한다.

- `action = ` : 여러가지 action을 지정할 수 있다.  `action`의 default는 `store`이다.

  > - `store` : 인자 바로 뒤의 값을 해당 인자에 할당한다.
  >
  >   ```
  >   parser.add_argumen("--exam") 일 경우
  >   $ python tmp.py --exam "exam" 
  >   이라는 명령어를 입력하면 args.exam에 "exam"이라는 str이 할당된다.
  >   ```
  >
  > - `store_const` : `add_argument()`에서 미리 지정되어 있는 `const=`에 해당하는 값이 저장된다. `const=`는 반드시 써 주어야 한다.
  >
  >   ```
  >   parser.add_argumen("--exam", action = store_const, const = "foo")
  >   ```
  >
  > - `store_true` : 해당 인자가 명령어에 포함될 경우 True를 할당. 아니면 False 
  >
  > - `store_false` : 해당 인자가 명령어에 포함될 경우 False을 할당. 아니면 True 
  >
  > - `append` : 값을 하나가 아닌 여러 개를 저장하고 싶을 때 쓴다. 인자를 여러 번 호출하면 같이 주는 값이 계속 append된다.
  >
  > - `count` : 인자를 적은 횟수만큼 값이 올라간다.
  >
  > - `help`: 도움말 메시지를 출력하게 하고 종료하여 코드는 실행시키지 않는다. `--help` 역할을 대신한다.

- `dest = ` : 적용 위치를 지정한다

  ```python
  parser.add_argument('--foo', action='append', dest='foo_list')
  ```

  `foo` 에 할당되는 값이 `foo_list`에 적용된다.

  ```python
  args.foo 
  # 대신
  args.foo_list
  ```

- `choices` : 값의 범위를 지정한다

  ```python
  parser.add_argument('--foo', choices=range(1, 5))
  # or
  parser.add_argument('--foo', choices=["1", "2", "3"])
  ```

- `metavar = ` : 해당 인자의 이름을 결정한다. (호출명과는 다름)

- `required = ` : 해당 인자의 생략 가능 여부를 결정한다. `required  = True` 인 경우, 해당 인자는 명령어 실행 시 반드시 포함되어야 한다.

- `nargs = ` 

  - `nargs = N`,  `N = int`값이 주어질 경우 : 해당 argument는 list가 되고, nargs값에 할당된 수  N만큼의 elements를 가질 수 있게 된다.

    ```python
    parser = argparse.ArgumentParser()
    parser.add_argument('--foo', nargs=2)	# 두 개의 인자 받음
    parser.add_argument('--bar', nargs=1)
    
    # python tmp.py --foo a, b --bar c
    args, unknown = parser.parse_known_args()
    print(args.foo)	# [a, b]  a, b 두 개의 인자를 받아 list에 할당
    print(args.bar) # [c]
    ```

    

  - `nargs = '*'` : 입력된 모든 argument를 list로 받는다.

    ```python
    parser = argparse.ArgumentParser()
    parser.add_argument('--foo', nargs="*")
    
    # python tmp.py --foo a, b, c
    args, unknown = parser.parse_known_args()
    print(args.foo)	# [a, b, c]  a, b, c 세 개의 인자를 받아 list에 할당
    ```

  - `nargs = '+'` : 입력된 모든 argument를 list로 받는다. (`'*'` 와 동일)



### parse_args()

받은 인자들을 객체로 사용할 수 있게 한다.

```python
args = parser.parse_args()
```





### parse_known_args()

`parse_args()` 와 유사하게 동작하지만, 여분의 인자가 있을 때 에러를 발생시키지 않는다.

```python
args, unknown = parser.parse_known_args()
```

> ```python
> parser = argparse.ArgumentParser()
> parser.add_argument('foo')
> parser.add_argument('bar')
> ```
>
> 위 처럼 인자가 두 개 일 때, 명령어로 세 개의 인자를 입력해도(여분의 인자가 있을 때) 에러를 발생시키지 않음





### add_mutually_exclusive_group()

argument를 group으로 나눠 관리하고자 할 때 사용한다. `parser`에 포함되는 하위 group을 만든다고 이해하면 된다.

```python
group_pars = parser.add_mutually_exclusive_group()
```

#### add_argument

`parser.add_argumen()` 와 동작이 동일하다.

```python
group_pars.add_argument('--exam')
```

단, `group_pars.add_argument()`을 두 개 이상 선언할 경우 그 중 한 개만 유효하게 사용할 수 있다.

```python
parser = argparse.ArgumentParser()
parser.add_argument('--baz')

group = parser.add_mutually_exclusive_group()
group.add_argument('--foo')
group.add_argument('--bar')
# python tmp.py --foo 1 --baz 2 		됨
# python tmp.py --bar 1 --baz 2 		됨
# python tmp.py --foo 0 --bar 1 --baz 2 	foo, bar 둘 다 입력이 있기 때문에 안됨
```

