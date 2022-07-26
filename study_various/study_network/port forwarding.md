# port forwarding

일반적인 port number 범위

TCP/UDP 통신에서는 포트 번호를 이용해서 컴퓨터 안의 어떤 프로그램에게 데이터를 전달할지를 식별한다. 포트 번호는 0부터 65535까지의 16비트 범위의 숫자로 되어 있다.

- 0 ~ 1023 : 잘 알려진 Well-Known Port 라고 부르며, 웹 서버나 메일 서버 등의 일반적인 프로그램들이 사용

  | 프로토콜              | 명령어  | 포트 번호  |
  | :-------------------- | :------ | :--------- |
  | Echo                  | echo    | 7          |
  | Daytime               | daytime | 13         |
  | File Transfer         | ftp     | 21/20      |
  | Secure Shell          | ssh     | 22         |
  | Telnet Terminal       | telnet  | 23         |
  | Simple Mail Transfer  | smtp    | 25         |
  | Domain Name Service   | domain  | 53         |
  | Trivial File Transfer | tftp    | 69         |
  | Finger                | finger  | 79         |
  | HyperText transfer    | http    | 80/84/8000 |
  | NetNews               | nntp    | 119        |

- 1024 ~ 49151 : Registered Port 라고 부르며, 잘 알려져 있는 프로그램들이 아닌 다른 용도의 프로그램들이 사용

- 49152 ~ 65535 : 동적 포트(Dynamic Port)로 서버가 클라이언트를 식별할 때 사용



공유기 외부에서 공유기 내부의 컴퓨터에 접속하기 위해서는 공유기의 몇번 port에 접속한 저보를 공유기 내의 몇 IP의 몇 번 port로 연결해줄 것인지 공유기에 설정해야 한다. 이 것이 port forwarding이다.



공유기 관리 페이지 https://192.168.0.1/

ID, PW입력 후



- 기본 설정 



-  고급 설정 >  NAT라우터 관리 > 포트포워드 관리

  규칙 이름 :  자유롭게

  내부 IP주소 : 연결하고자 하는 device IP주소

  외부 포트 : 외부에서 접근하고자 하는 port

  내부 포트 : 외부에서 접근한 port에 내부 특정 device의 port를 연결한다.





### Ubuntu

1. port상태 확인

   ```
   # netstat -tnlp -a
   ```

   ```
   Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name    
   tcp        0      0 0.0.0.0:22              0.0.0.0:*               LISTEN      -                   ...
   tcp        0    400 192.168.56.101:22       192.168.56.1:49319      ESTABLISHED -
   ```

   >`-a` : 모든소켓 표시
   >
   >- State 
   >
   >  `LISTEN` : 열려 있음(사용 가능) 
   >
   >  - `0.0.0.0:22` : 22번 port가 열려 있음
   >
   >  `ESTABLISHED` :누군가 접속중
   >
   >  ```
   >  tcp        0    400 192.168.56.101:22       192.168.56.1:49319      ESTABLISHED -
   >  ```
   >
   >  내 IP가 `192.168.56.101` 이고, 이곳의 22번 port로 `192.168.56.1`가 접속중임
   >
   >- `TIME_WAIT` : 접속 후 사용이 종료되었으나 지정된 시간만큼 다른 명령이나 신호를 기다리는 중
   >
   >- `FIN_WAIT 1` : port가 닫혀있으며 연결이 종료되기를 기다리는 중
   >
   >- `FIN_WAIT 2` : 연결이 완전히 닫힌 상태
   >
   >- `SYN_SENT` : 원격지에서 port를 열려고 시도하는 중 
   >
   >- `UNKNOWN` : 현재 port의 상태를 알 수 없음

2. 열고자 하는 port확인 (5900port확인)

   ```
   # netstat -nap | grep 5900
   ```

   > 아무것도 안뜨면 해당 port는 사용 안하는 중

3. 특정 port열기

   외부에서 접속할 수 있도록 port OPEN (사용 안하는 port에만 적용) 

   `INPUT`

   ```
   # iptables -I INPUT 1 -p tcp --dport 5900 -j ACCEPT
   ```

   `OUTPUT`

   ```
   # iptables -I INPUT 1 -p udp --dport 5900 -j ACCEPT
   ```

4. port가 열렸는지 확인

   ```
   # iptables -nL
   ```

   ```
   Chain INPUT (policy ACCEPT)
   target     prot opt source               destination
   ACCEPT     tcp  --  0.0.0.0/0            0.0.0.0/0            tcp dpt:5900
   
   ```

   > 5900번 열려있음 확인

5. port forwarding

   

   

