# Ubuntu 명령어

###  Shortcuts

단축키

#### terminal

- `Ctrl + Insert`: 복사하기
- `Shift + Insert`: 붙여넣기
- `Ctrl + l` : 화면 초기화 
- `Ctrl + d` : terminal 종료(session 종료)
- `Ctrl + c` : 하던 임무 종료



### 명령어

#### 기본 명령어

- **--help** : 어떠한 명령어에 대한 설명을 출력하는 명령어

  ```
  $ apt --help
  ```

  안되면

  ```
  help apt
  ```

  

- **apt** : 무언가를 intall할때 사용하는 명령어

  ```
  $ apt-get
  ```

  > 여기서 `-get` 대신 `-y` flag를 사용하면 install 과정에서 나오는 모든 물음에는 yes로 하겠다는 의미 

- **dpkg** 설치되어 있는 package 확인

  ```
  $ dpkg -l | grep package_name
  ```

  *option*

  - 설치되어 있는 package 개수 확인

    ```
    $ dpkg -l | wc -l
    ```

    

- **cal** : 달력

  ```
  $ cal
  ```

- **data** : 날짜

  ```
  $ data
  ```

- **clear** : terminal의화면 clear

  ```
  $ clear
  ```

- **ls** : 현재 위치에 존재하는 file과 directory 목록 보기

  ```
  $ ls
  ```

  하얀색으로 보이면 file, 파란색으로 보이면 directory

  *option*

  - **/etc** : 

    ```
    $ ls /etc
    ```

    file과 directory 목록을 여러 행으로 나눠서 보여줌

  - **-l** : 자세한 정보를 포함해서 보기

    ```
    $ ls -l
    또는 
    $ ll
    ```
    
    > **`$ ll`** 를 많이 씀
    
  - **-a** : 숨김속성이 적용 된 file이나 directory까지 보여줌

    ```
    $ ls -a
    ```

    

- **file** : file의 자세한 information을 보여줌

  ```
  $ file file_name
  ```

- **pwd** : 현재 내 위치를 보여줌

  ```
  $ pwd
  ```

- **cat** : file의 내용을 vim이 아닌, 그냥 읽기모드로 보기

  ```
  $ cat file_name
  ```

  *option*

  - **-n** : show with line number 

    ```
    $ cat -n file_name
    ```

    > 공백 line도 표시함

  - open multi file

    ```
    $ cat file_name1, file_name2
    ```
    
  - `>` 으로 바로 file을 만들 수 있다.

    ```
    cat > k.cpp
    ```

    > k라는 이름을 가진 c++확장자 file 생성 후 편집모드로 열기
    >
    > 만든 file은 `Ctrl + d` 로 저장 가능

- **nl** : file을 열어서 안의 내용을 line을 표시해주며 볼 수 있다.

  ```
  $ nl
  $ nl /etc
  ```

- **rm** : remove

  ```
  $ rm file_name
  ```

  *option*

  - **-f** : 강제 삭제

    ```
    $ rm -f file_name
    ```

  - **-r** :  file이 아닌, directory 삭제

    ```
    $ rm -r directory_name
    ```

    > directory안에 어떠한 file이 있다면, 같이 삭제할건지 여부를 물어본다.

  - **-rf** : file이건 directory이건 강제로 삭제 (안에 있는 것 까지)

    ```
    rm -rf dd/
    ```

    > dd라는 directory안의 모든 file 삭제

- **mkdir** : directory 만들기

  ```
  $ mkdir direc_name
  ```

  *option*

  - directory 만들고 바로 해당 directory로 이동

    ```
    $ mkdir direc_name && cd direc_name
    ```

  - 한 위치에 directory 한 번에 여러개 만들기

    ```
    $ mkdir d1, d2, d3
    ```

  - **-p** : 하위 directory까지 한번에 생성

    ```
    $ mkdir -p a1/a10/a100
    ```

    > 현재 위치에서 a1만들고 그 안에 a10을, 또 그 안에 a100을 생성

- **rmdir** : directory  삭제

  ```
  $ rmdir direc_name
  ```

  > directory 안에 어떠한 file이 있다면 mr 불가능
  >
  > 보통 rmdir보단 **rm -r** 을 더 많이 사용함
  >
  > 

  

  ```
  $ rm -rf dd/
  $ mrdir dd
  ```

  > rm -rf으로 내부 file과 directory 삭제 후 사용

  *option*

  - **-p** : 하위 directory까지 한번에 삭제

    ```
    $ mrdir -p a1/a10/a100
    ```

- **touch** : file을 생성

  ```
  $ touch tmp
  ```

  > tmp라는 이름의 file 생성

- **vi** : vim으로 file열기

  ```
  $ vi file_name
  ```

- **cp** : 사용자가 지정한 위치의 file을 복사하는 명령어

  ```
  $ cp /tmp/foo/bar .
  ```

  > tmp안의 foo 안에 있는 bar라는 file을 같은 이름으로 현재 위치에 복사

  ```
  $ cp /tmp/foo/bar baz
  ```

  > tmp안의 foo 안에 있는 bar라는 file을 baz라는 이름으로 현재 위치에 복사
  >
  > 만약 baz라는 이름을 가진 file이 이미 있었다면, 덮어씌우고, 
  >
  > baz라는 이름을 가진 directory가 있다면 해당 directory안에 복사

  *option*

  - **-r** : file이 아닌, directory를 복사할때 사용

    ```
    $ cp -r /tmp/foo .
    ```

  -  **-i** : 복사하려는 file과 같은 이름을 가진 file이 이미 존재한다면 덮어씌울지를 물어보는 옵션

    ```
    $ cp -i /tmp/foo/bar baz
    ```

    > 항상 `-i`를 붙여쓰는 것을 습관화 하자

- `wget URL` : URL을 다운로드 (img 같은 것)

- **du** : 설정한 위치에 존재하는 firectory와 file용량 확인

  ```
  $ du . 				$ du ~
  ```

  > 현재 위치에서 용량 확인, user directory의 용량 확인
  >
  > 속해 있는 개별 file에 대해서 용량을 보여준다.

  - **-sh** : 전체 용량을 합산해서 보여준다.

    ```
    $ du -sh ~
    ```

- **df** : 설정한 위치에 존재 파티션의 사용비율 및 용량을 보여준다.

  ```
  $ df
  ```

  - **-h** : 보기 쉽게 보여줌

    ```
    $ df -h
    ```

    

  





##### 기호 명령어

- **>** : file1을 file2의 내용으로 덮어써서 저장

  ```
  $ file_name2 > file_name1
  ```

  > ```
  > $ cal > file_name
  > ```
  >
  > 달력을 file_name이란 파일 이름으로 저장

- **>>** : file1을 file2의 내용 뒤에 붙여서 저장

  ```
  $ file_name1 >> file_name2
  ```

- **&&** : 여러 명령어를 한 줄에 입력해서 실행

  ```
  $ mkdir tmp && cd tmp
  ```

  > tmp directory를 만들고 tmp로 이동

- **|** : 



##### variable

###### 환경 변수 `env`

환경 변수는 다른 명령어와 구분하기 위해 대체적으로 대문자를 사용

환경(전역) 변수의 list를 출력

```
$ env | ln
```

> 전역변수를 index를 보여주며 출력



- 변수를 출력할 때는 `echo` 에 `$`를 붙여서 출력해야 한다.

  ```
  echo $PWD
  ```

  > PWD라는 환경변수 호출



###### 지역 변수 `set`

지역 변수의 list를 출력

```
$ set | ln
```

> 여러 function도 포함되어 있는 것을 볼 수 있다.



**option**

- -o : 지역 변수 중 on - off 설정이 가능한 option들을 출력

  ```
  $ set -o
  ```

  그 중 noclobber 옵션을 off에서 on으로 바꿔보자.

  > noclobber option은 어떤 file1을 file2에 덮어씌울 때 안에 어떠한 내용이 있다면 덮어씌우기가 안되도록 하는 함수

  ```
  $ set -o noclobber 
  ```

  > noclobber 을 on으로 켠다

  ```
  $ set +o noclobber 
  ```

  > noclobber 을 off로 끈다



**`name() { }`** 지역 변수(함수)를 만드는 명령어

- 함수 생성

  ```
  tmp() { echo " 이것은 함수입니다. " ;}
  ```

  > `{` 이후에 띄어쓰기 필수 

- 호출

  ```
  tmp
  ```

이렇게 만들어진 함수는 session이 종료되면(logout이나 다른 command에선) 사라진다. 지역변수이기 때문에.

하지만 특정 file에 저장을 해 놓으면 login할 때마다 사용이 가능하다.





#### root 권한 명령어

- **sudo -i** : root로 전환

  ```
  $ sudo -i
  또는 
  $ su -
  ```

- root 에서 logout

  단축키 `Ctrl + d`

- **passwd** root에서 passward 바꾸기

  ```
  # passwd
  ```

  

##### user 

- **useradd** 사용자 추가 명령어

  ```
  # useradd -m -b /home -s /bin/bash new_user_name
  ```

  > home directory의 사용자, 사용하는 shell : bin/bash

  - **passwd new_user_name** : 새로 만든 사용자의 비밀번호 설정

    ```
    # passwd new_user_name
    ```

    passwd file을 열어봐서 어떤 사용자들이 있는지 확인해보자

    ```
    $ nl /etc/passwd
    ```

  새롭게 만들어진 사용자는 sudo그룹의 권한이 없기 때문에 root로 로그인 할 수 없다.

  - **usermod -aG sudo new_user_name** : 사용자에게 sudo 그룹의 권한을 주는 명령어

    ```
    # usermod -aG sudo new_user_name
    ```

- **userdel** : user를 삭제하는 명령어

  ```
  # userdel tmp
  ```

  > tmp라는 user계정 삭제

- **whoami** : 현재 terminal로 login한 user가 누구인지 출력 (**logname**)

  ```
  $ whoami
  ```

  ```
  $ logname
  ```

- **who** : 현재 로그인 되어있는 모든 user를 출력

  ```
  $ who
  ```

  >  출력된 정보 중 pts/1는 terminal 번호이다. 

- **tty** : 현재 내 terminal 경로와 번호를 출력

  ```
  $ tty
  ```

  - root권한 상태에서 **echo** 명령어를 통해 사용자에게 메세지를 보낼 수 있다. 

    ```
    # echo "안녕?" > /dev/pts/0
    ```

    > 0번 terminal의 user에게 메세지 보냄

- **w** : user들이 뭘 하고 있는지 볼 수 있는 명령어

  ```
  $ w
  ```





##### group

- **groupadd** : 새 그룹을 만드는 명령어

  ```
  # groupadd 
  ```

  group file을 열어봐서 어떤 사용자들이 있는지 확인해보자

  ```
  $ nl /etc/group
  ```

- **groups** : 현재 terminal로 login한 user가 소속된 group의 이름을 출력

  ```
  $ groups
  ```

- **chown** : file 또는 directory의 소유 user를 바꾸는 명령어

  ```
  # chown user_name derectory1
  ```

  > derectory1 라는 폴더의 소유주를 user_name이라는 user로 바꿈

- **chgrp** : file 또는 directory의 소유 group을 바꾸는 명령어

  ```
  # chgrp group_name derectory1
  ```

  > derectory1 라는 폴더의 소유 그룹을 group_name이라는 그룹으로 바꿈

  - chown 을 사용해서 소유주와 그룹을 동시에 바꿀 수 있다

    ```
    # chown user_name:group_name derectory1
    ```

    > derectory1 라는 폴더의 소유주를 user_name으로, 소유 그룹을 group_name으로 바꿈
    >
    > `$ ll` 명령어로 확인 가능





#### Compile명령어

- **gcc** : c++ 확장자의 file을 compile하는 명령어

  ```
  $ gcc tmp.cpp
  ```

  > tmp라는 c++확장자 file을 compile

  compile이 성공적으로 되면 tmp라는 이름의 실행파일이 만들어진다.

  ```
  $ tmp
  ```

  > 실행

