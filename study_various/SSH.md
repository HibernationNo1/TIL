# SSH

SSH란 Secure Shell Protocol, 즉 네트워크 프로토콜 중 하나로 컴퓨터와 컴퓨터가 인터넷과 같은 Public Network를 통해 서로 통신을 할 때 보안적으로 안전하게 통신을 하기 위해 사용하는 프로토콜.

주로 데이터 전송, 원격 제어에 사용



### install

Ubuntu 기준

```
$ apt install ssh
```

또는 

```
$ apt install openssh-server
```

> 설치 안되면 
>
> 방화벽 해제해보기
>
> ```
> root@ ~~~ :~# systemctl stop ufw
> ```



ssh가 잘 설치되었는지 확인

```
$ systemctl status ssh
```

초록색 글자의  `active(running)`이 보인다면 접속 가능



ssh 시작

```
root@ ~~~ :~# systemctl start ssh
```





### putty로 ssh 시작

1. login(target OS가 실행되고 있어야함)

   window 10에서 putty 실행 후 

   > 경우 1
   >
   > VirtualBox로 network의 포트 포워딩을 통해 특정 Virtual machine의 host port에 105라는 번호를 할당했다면.
   >
   > putty의 Host Name : `127.0.0.1`, 		port : `105`
   >
   > 경우 2
   >
   > Virtual machine의 포트 포워딩을 
   >
   > host port : ` 22` 		guest port : `22` 으로 설정했다면 
   >
   >  putty의 Host Name : `127.0.0.1`, 		port : `22`

   위 예시 입력 후 확인, accept 클릭

   `login as:` 가 뜨면 성공

   ```
   login as: hibernation
   password : winter4958
   ```

   > 아이디 비번 입력해서 접속

2. VirtualBox와 양방향 setting

   VirtualBox에서 장치 - 클립보드 공유 - 양방향 으로 setting

   VirtualBox에서 장치 - 드래그 앤 드롭 - 양방향 으로 setting

이제 window10에서 putty를 통해 ssh로 ubuntu에서 작업이 가능하다.

