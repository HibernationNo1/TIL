# Permission

**directory위치**

가장 최상위 directory가 있고, 그 아래 home directory와 여러가지가 있다.

home dicrectory에는 root directory와 user들의 각 계정의 directory가 있다.

![](https://t1.daumcdn.net/cfile/tistory/223BDE4855351B370F)

>  home과 같은 계층에는 **etc**와 **root** directory도 존재한다.
>
>  우리가 알아야 할 최상위(/) 계층의 바로 아래 directory : **bin**, **root**, **etc**, **home**, **use**, **tmp**
>
>  user가 root(관리자) 외에도 jene, zed가 있다고 가정

- **root** : 관리자 directory

  > root directory라고 하면 최 상위 directory인 `/`를 의미하고, root 사용자라고 하면 관리자를 의미한다. 그리고 그 관리자의 directory는 `/` 아래 있는 root directory이다.
  >
  > 관리자를 제외한 일반 user는 자신의 directory에서만 작업을 할 수 있는 권한이 있다. 하지만 관리자는 모든 user의 directory에서 무엇이든 할 수 있는 권한이 있다.
  >

- **home** : users를 담고 있다.

  - jene

    ```
    $ cd home/jene/winter2		==  $ cd ~/winter2
    ```

    jene라는 user directory위치에 있는 winter2라는 directory로 이동

  - zed

    ```
    $ cd home/zed/winter3		== $ cd ~/winter3
    ```

    zed라는 user directory위치에 있는 winter3라는 directory로 이동

- **etc** : 모든 사용자들이 사용하는 소프트웨어 또는 그 외의 설정값이 저장된 file이 모여있다.

  > etc및의 file은 root권한으로만 수정이 가능하다.

- **bin** : execute file을 모여있다.





- **~** : '틸드'라고 하며 현재 접속한 계정의 home directory 를 의미한다. (개인 계정)

  > hibernation 으로 접속 한 상태에서

  ```
  $ cd ~
  $ pwd
  ```

  ```
  /home/hibernation
  ```

  

- file 이름 앞에 `.` 가 있으면 해당 file은 숨김속성이 적용된 file임



### 권한

- `r` : read 읽기권한 (4)
- `w` : write 쓰기권한 (2)
- `x` : execute 실행권한 (1)

```
$ ll
```

> `$ ll` : 명령어로 알 수 있는 file 또는 directory의 information

```
drwx------  5 root root 4096   	# tmp1
drwxr-xr-x 20 root root 4096   	# tmp2
-rw-r--r--  1 root root 3106	# tmp3
```

> `$ ll` 으로 위 정보를 출력했다고 가정하고, 위 정보를 구분해서 나누면

```
d rwx --- ---  5 root root 4096  
d rwx r-x r-x 20 root root 4096  
- rw- r-- r--  1 root root 3106
```

> - 첫 번째 글자 
>
>   `d` : directory
>
>   `-` : file
>
> - 두 번째 단어 : file 또는 directory의 소유주가 가진 권한
>
> - 세 번째 단어 : file 또는 directory의 소유 group이 가진 권한
>
> - 네 번째 단어 : file 또는 directory의 others가 가진 권한
>
> - 여섯 번째 단어 : file 또는 directory의 소유주 이름
>
> - 일곱 번째 단어 : file 또는 directory의 소유group 이름
>
> - 여덟 번째 숫자 : file 또는 directory의 크기

각 권한이 가진 숫자를 더해보면 아래와 같다

```
d rwx --- ---  5 root root 4096   	# tmp1  
   7   0   0						(4 + 2 + 1), (0), (0)
d rwx r-x r-x 20 root root 4096   	# tmp2  
   7   5   5						(4 + 2 + 1), (4 + 1), (4 + 1)
- rw- r-- r--  1 root root 3106   	# tmp3
   6   4   4						(4 + 2), (4), (4)
```



#### chmod

**chmod** 를 이용해 이 권한을 바꿀 수 있다.

> 기호 모드에 오류가 나면 `,` 다음에 공백을 넣어볼것 

```
# chmod 777 tmp1 # 각 권한을 모두 rwx로 추가
# chmod +w tmp2  # 각 권한에 w권한만 모두 추가
# chmod 123 tmp3

# chmod u=r,g=x,o=r tmp1  # user는 r, group은 x, others는 r의 권한만 있도록
# chmod u=rwx,g=rx,o=rw tmp2 
# chmod u=-r,g =+wx,o=-r tmp3
```

위 명령어로 인해 아래처럼 information이 바뀐다.

```
d rwx rwx rwx  5 root root 4096   	# tmp1 
d rwx rwx rwx 20 root root 4096   	# tmp2  
- --x -w- -wx  1 root root 3106   	# tmp3

d r-- --x r--  5 root root 4096   	# tmp1 
d rwx r-x rw- 20 root root 4096   	# tmp2  
- -w- rwx ---  1 root root 3106   	# tmp3
```

각 권한에 대해서 설정을 함으로써, 특정 user 또는 group만 접근하고, 실행할 수 있는 file또는 directory를 만들고 관리할 수 있다.



#### umask

**umask** : user가 directory 또는 file을 만들 때 각 객체에 적용되는 권한을 결정하는 값을 가지고 있다.

```
$ umask
```

> 0022을 출력했다면, 
>
> 이 사용자의 directory는 처음 만들어질 때 777-022 = 755의 권한을 가지고 있다.
>
> 이 사용자의 file은 처음 만들어질 때, directory의 권한에서 실행 권한(x)이 제외된 권한을 가지고 있다.
>
> ```
> $ umask -S
> ```
>
> 0022를 기호모드로 출력 `u=rwx, g=rx, o=rx` 가 출력될거임

이 umask값을 바꿀 수 있다.

```
$ umask 000
```

> umask값을 000으로 바꿈

이 uamsk값을 기호 모드로 표현해서 수정하면 더욱 이해하기 쉽다.

```
$ umask u=rwx,g=rx,o=rx
```

> 0022출력. 처음 directory의 권한이 `u=rwx,g=rx,o=rx` 로 주어질 것이라는 의미

