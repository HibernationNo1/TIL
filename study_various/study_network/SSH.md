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





### ssh_config

위치 : `/etc/ssh/ssh_config` 

해당 파일에서 port부분을 변경할 수 있다.

```
$ sudo vi /etc/ssh/ssh_config
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

