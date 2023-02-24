# SSH

SSH란 Secure Shell Protocol, 즉 네트워크 프로토콜 중 하나로 컴퓨터와 컴퓨터가 인터넷과 같은 Public Network를 통해 서로 통신을 할 때 보안적으로 안전하게 통신을 하기 위해 사용하는 프로토콜.

주로 데이터 전송, 원격 제어에 사용



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





### command

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

외부에서 filezilla, putty 다 되는데 vscode만 되지 않고

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
# Host 192.168.2119.100 found: line 3 type RSA
/User/username/.ssh/known_hosts updated.
original contents retained as /User/username/.ssh/known_hosts.old
```

이후 접속 되는것 확인
