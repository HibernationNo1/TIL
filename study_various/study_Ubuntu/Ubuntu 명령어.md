# Ubuntu 명령어



###  Shortcuts

단축키

#### terminal

- `Ctrl + Insert`: 복사하기
- `Shift + Insert`: 붙여넣기
- `Ctrl + l` : 화면 초기화 
- `Ctrl + d` : terminal 종료
- `Ctrl + c` : 하던 임무 종료



### 기본 명령어

- **apt** : 무언가를 intall할때 사용하는 code

  ```
  $ apt-get
  ```

  > 여기서 `-get` 대신 `-y` flag를 사용하면 install 과정에서 나오는 모든 물음에는 yes로 하겠다는 의미 

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
    # ls /etc
    ```

    file과 directory 목록을 여러 행으로 나눠서 보여줌

  - **-l** : 자세한 정보를 포함해서 보기

    ```
    # ls -l
    또는 
    # ll
    ```

- **pwd** : 현재 내 위치를 보여줌

  ```
  $ pwd
  ```

- **cat** : file의 내용을 읽기 전용으로 보기

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
    $ rm -f directory_name
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

- **mrdir** : directory  삭제

  ```
  $ mrdir direc_name
  ```

  > directory 안에 어떠한 file이 있다면 mr 불가능
  >
  > 보통 mrdir보단 **rm -r** 을 더 많이 사용함

  rm -rf으로 내부 file과 directory 삭제 후 사용

  ```
  $ rm -rf dd/
  $ mrdir dd
  ```

  *option*

  - **-p** : 하위 directory까지 한번에 삭제

    ```
    $ mrdir -p a1/a10/a100
    ```

- **vi** : vim으로 file열기

  ```
  $ vi file_name
  ```

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





### root 권한 명령어

- **sudo -i** : root로 전환

  ```
  $ sudo -i
  또는 
  $ su -
  ```

- root 에서 logout

  단축키 `Ctrl + d`



