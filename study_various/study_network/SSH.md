# SSH

SSH란 Secure Shell Protocol, 즉 네트워크 프로토콜 중 하나로 컴퓨터와 컴퓨터가 인터넷과 같은 Public Network를 통해 서로 통신을 할 때 보안적으로 안전하게 통신을 하기 위해 사용하는 프로토콜.

주로 데이터 전송, 원격 제어에 사용



## start

### install

Ubuntu에서 openssh라는 패키지를 통해 SSH를 구동할 수 있다.

Ubuntu를 설치하면, openssh-client 만이 기본적으로 설치되어있음

```
$ dpkg -l | grep openssh
```

> openssh-client 확인

다른 컴퓨터에서 Ubuntu에 접속하려면 openssh-server 패키지도 설치해야 한다.

```
$ sudo apt-get install openssh-server
```

이후 방화벽 해제

```
$ sudo ufw allow ssh
```



### add ssh key

- 개인 key 쌍 추가

  ```
  $ ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
  ```

  - `-t rsa`: 키 유형을 RSA로 지정
  - `-b 4096`: 키의 비트 길이를 4096으로 설정(더 강력한 보안 제공).
  - `-C "your_email@example.com"`: 키에 대한 주석 추가(예: 소유자의 이메일 주소).

  ```
  Generating public/private rsa key pair.
  Enter file in which to save the key (/home/username/.ssh/id_rsa): 
  Enter passphrase (empty for no passphrase): 
  Enter same passphrase again: 
  Your identification has been saved in /home/username/.ssh/id_rsa
  Your public key has been saved in /home/username/.ssh/id_rsa.pub
  The key fingerprint is:
  SHA256:HS3y4/fFS0uyw6FsS1IrtftF09XYya0LvMFQQmUXi4A your_email@example.com
  The key's randomart image is:
  +---[RSA 4096]----+
  |         o+.+ o. |
  |        E  * o.++|
  |        . + o oo=|
  |         + *   .o|
  |        S +o= .o.|
  |         .o.o=.o.|
  |         oo+=.o+o|
  |          +=.+*.o|
  |          .ooooo |
  +----[SHA256]-----+
  ```

  전부 기본값으로 하면 `/home/username/.ssh`의 위치에 아래 2개의 파일이 생성된다.

  - `id_rsa` : private key
  -  `id_rsa.pub`: public key. gitlab과 같은 관리 프로세스와 연동할때 사용한다.
  - `known_hosts`: 이미 신뢰된 SSH 서버들의 공개 키들의 지문(fingerprints)을 저장





#### gitlab에 추가하기

`setting` > `SSH key` > `Key` 칸에  위에서 생성한 파일 `id_rsa.pub` 의 내용 추가

- 만일 `Fingerprint has already been taken`라는 문구가 뜬다면

  해당 공개키는 다른 gitlab에서 사용중이란 뜻이다.



### SSH agent

openssh package의 일부로 포함되어 있는 agent 프로그램. 

- SSH 키 관리를 담당하는 백그라운드 프로그램
- 개인 키를 안전하게 관리하고, 해당 키를 사용하여 SSH 세션을 위한 인증을 자동화

#### start

agent 시작 명령어

```
$ eval "$(ssh-agent -s)"
```



- 기본 키 추가 명령어

  사용자의 SSH 키를 SSH agent에 추가

  ```
  $ ssh-add
  ```

  ```
  Identity added: /home/username/.ssh/id_rsa (username@shopdb-B365M-DS3H)
  ```

  `/home/username/.ssh/id_rsa `라는 file(key)를 agent에 추가

- 특정 키 파일 추가 명령어

  ```
  $ ssh-add ~/.ssh/your_private_key
  ```



#### check ssh key

사용중인 ssh key가 있는지 확인. 

git에 어떤 ssh key로 연결되어있는지 확인하는 경우에도 사용할 수 있다.

```
$ ssh-add -l
```







## connection

1. copy ssh key to server

   ```
   $ ssh-copy-id -p 2323 username@IP
   ```

   - port `2323`으로 접속 (default `22`)

2. connection

   ```
   $ ssh username@IP -p 2323
   ```

   비밀번호 입력을 해야 한다면 ssh key에 의한 인증이 제대로 되지 않은 것이다.



- ssh key에 의한 인증이 제대로 안된 경우

  1. 원격 서버의 SSH 공개 키 파일 권한 확인

     ```
     $ chmod 700 ~/.ssh
     $ chmod 600 ~/.ssh/authorized_keys
     ```

  2. 원격 서버의 SSH 공개 키 확인

     `~/.ssh/authorized_keys`의 공개 키와 로컬의 `ssh-keygen -y -f /home/teno/.ssh/id_rsa`에 의한 출력이 같음을 확인

  3. home dir의 권한 확인

     ```
     $ cd ~
     $ cd ..
     $ cd ll		
     ```

     권한이 700이여야 한다.





## command

### start

**start ssh**

```
$ sudo service ssh start 
```



**stop ssh**

```
$ sudo service ssh stop
```



**restart ssh**

```
$ sudo service ssh restart
```



**check ssh port**

```
$ sudo netstat -antp
```

> 현재 network가 어떻게 열려있는지, 통신하고있는지 확인





### set port 

위치 : `/etc/ssh/ssh_config` 

해당 파일에서 port부분을 변경할 수 있다.

```
# vi /etc/ssh/ssh_config
```

```
...

#Port 22
#AddressFamily any
#ListenAddress 0.0.0.0
#ListenAddress ::

...
```

> ssh접근 port가 22인것을 확인. 이 부분을 변경하면 ssh의 접근 port를 변경할 수 있다.
>
> 변경 후 확인 방법
>
> ```
> $ sudo netstat -anp|grep LISTEN|grep sshd
> ```



### set allowed ip

1.  add allow ip

   ```
   # vi /etc/hosts.allow
   ```

   

   ```
   # /etc/hosts.allow: list of hosts that are allowed to access the system.
   #                   See the manual pages hosts_access(5) and hosts_options(5).
   #
   # Example:    ALL: LOCAL @some_netgroup
   #             ALL: .foobar.edu EXCEPT terminalserver.foobar.edu
   #
   # If you're going to protect the portmapper use the name "rpcbind" for the
   # daemon name. See rpcbind(8) and rpc.mountd(8) for further information.
   #
   
   sshd: 124.50.187.177		# `124.50.187.177` 라는 ip허용
   sshd: 211.36.				# `211.36.` 로 시작하는 ip허용
   ```

   

2. set denie ip

   ```
   # vi /etc/hosts.deny
   ```

   ```
   # /etc/hosts.deny: list of hosts that are _not_ allowed to access the system.
   #                  See the manual pages hosts_access(5) and hosts_options(5).
   #
   # Example:    ALL: some.host.name, .some.domain
   #             ALL EXCEPT in.fingerd: other.host.name, .other.domain
   #
   # If you're going to protect the portmapper use the name "rpcbind" for the
   # daemon name. See rpcbind(8) and rpc.mountd(8) for further information.
   #
   # The PARANOID wildcard matches any host whose name does not match its
   # address.
   #
   # You may wish to enable this to ensure any programs that don't
   # validate looked up hostnames still leave understandable logs. In past
   # versions of Debian this has been the default.
   # ALL: PARANOID
   
   sshd: ALL
   ```

   



## putty

원격 제어에 사용

1. 원격 접속하고자 하는 device의 IP확인

2. IP통신 확인

   ```
   $ ping 192.168.56.101
   
   Ping 192.168.56.101 32바이트 데이터 사용:
   192.168.56.101의 응답: 바이트=32 시간<1ms TTL=64
   192.168.56.101의 응답: 바이트=32 시간<1ms TTL=64
   192.168.56.101의 응답: 바이트=32 시간<1ms TTL=64
   192.168.56.101의 응답: 바이트=32 시간<1ms TTL=64
   
   192.168.56.101에 대한 Ping 통계:
       패킷: 보냄 = 4, 받음 = 4, 손실 = 0 (0% 손실),
   왕복 시간(밀리초):
       최소 = 0ms, 최대 = 0ms, 평균 = 0ms
   ```

3. 접속

   `username@IP` :port 입력

   





## Filezilla

데이터 전송에 사용

- 호스트 : `sftp://192.168.0.208`

- 사용자면 : ainsoft

- PW : 

- Port :

  입력 후 빠른연결 사용





## vscode

extension에서 `remote-ssh` 검색해서 설치

`ssh username@IP` 로 접속



**error**  

- 외부에서 filezilla, putty 다 되는데 vscode만 되지 않고

  bash에서 `ssh username@IP` 명령어 입력 시 아래 error가 뜨는 경우

  ```
  ECDSA host ket for 192.168.219.100 has changed and you have requsted strict checking.
  Host key verification failed.
  ```

  `192.168.219.100`이라는 ip로 기존에 접속한 적이 있는 서버와 RAS 공유키를 교환한 상태에서, `192.168.219.100`이라는 서버가 바뀐 경우 발생한다.

  아래 명령어로 초기화 진행

  ```
  $ ssh-keygen -R 192.168.219.100
  ```

  ```
  username$ ssh-keygen -R 192.168.219.100
  # Host 192.168.219.100 found: line 3 type RSA
  /User/username/.ssh/known_hosts updated.
  original contents retained as /User/username/.ssh/known_hosts.old
  ```

  이후 접속 되는것 확인





- 프로세스에서 없는 파이프에 쓰려고 했습니다.

  ```
  [15:23:31.588] > ssh: connect to host 192.168.219.100 port 22: Connection refused
  > 프로세스에서 없는 파이프에 쓰려고 했습니다.
  [15:23:32.777] "install" terminal command done
  [15:23:32.778] Install terminal quit with output: 프로세스에서 없는 파이프에 쓰려고 했습니다.
  [15:23:32.778] Received install output: 프로세스에서 없는 파이프에 쓰려고 했습니다.
  [15:23:32.778] Failed to parse remote port from server output
  [15:23:32.780] Resolver error: Error: 
  	at m.Create (c:\Users\마이노\.vscode\extensions\ms-vscode-remote.remote-ssh-0.102.0\out\extension.js:1:584145)
  	at t.handleInstallOutput (c:\Users\마이노\.vscode\extensions\ms-vscode-remote.remote-ssh-0.102.0\out\extension.js:1:582705)
  	at t.tryInstall (c:\Users\마이노\.vscode\extensions\ms-vscode-remote.remote-ssh-0.102.0\out\extension.js:1:681881)
  	at async c:\Users\마이노\.vscode\extensions\ms-vscode-remote.remote-ssh-0.102.0\out\extension.js:1:644110
  	at async t.withShowDetailsEvent (c:\Users\마이노\.vscode\extensions\ms-vscode-remote.remote-ssh-0.102.0\out\extension.js:1:647428)
  	at async t.resolve (c:\Users\마이노\.vscode\extensions\ms-vscode-remote.remote-ssh-0.102.0\out\extension.js:1:645160)
  	at async c:\Users\마이노\.vscode\extensions\ms-vscode-remote.remote-ssh-0.102.0\out\extension.js:1:720916
  [15:23:32.787] ------
  ```

  경우의 수

  - client와 sever가 같은 공유기로 묶여있는 경우

    같은 내부 IP가 할당되었는지 확인

    > 192.168.219.100 으로 client와 server가 같은 IP를 사용하고 있는 경우 발생한다.
    >
    > 공유기를 통해 DHCP IP 고정할당을 설정해야 함 

  



