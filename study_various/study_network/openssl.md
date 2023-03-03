# openssl



기본적으로 linux에는 openssl이 설치되어 있다.

version check

```
$ openssl version
OpenSSL 1.1.1k  25 Mar 2021
```

> 설치 안되어 있다면 아래 명령어
>
> ```
> $ sudo apt install openssl
> ```



### SSL 인증서 및 키 확인

 기본적으로 미리 설정된 자체 SSL 인증서 및 키를 확인

```
$ sudo apt-get update
```



```
$ sudo openssl x509 -noout -text -in /etc/ssl/certs/ssl-cert-snakeoil.pem
$ sudo openssl rsa -noout -text -in /etc/ssl/private/ssl-cert-snakeoil.key
```

- `/etc/ssl/certs/ssl-cert-snakeoil.pem`: 기본 SSL 인증서 파일의 경로
- `/etc/ssl/private/ssl-cert-snakeoil.key`: 기본 SSL 키 파일의 경로



### 인증서 생성

1. 인증서 생성 명령어

   

   ```
   $ openssl req -newkey rsa:2048 \
               -x509 \
               -sha256 \
               -days 3650 \
               -nodes \
               -out hibernation_.crt \
               -keyout hibernation_.key
   ```

   - `newkey rsa:2048`: 새 인증서 요청 및 4096비트 RSA 키를 생성한다.

     기본은 2048bit이며, 4096bit도 사용할 수 있다.

   - `x509`:  X.509 CSR(인증서 서명 요청)을 사용

   - `sha256`:  265비트 SHA(Secure Hash Algorithm)를 사용

   - `days 3650` : 인증서 유효기간 설정(일 단위, 기본값 30일)

     3650: 10년

   - `nodes`: 암호사용을 해제. 해당옵션이 없으면 아파치 재시작할 때마다 비밀번호 입력 필요

   - `out`: 새로 만든 인증서를 쓸 파일 이름을 지정(파일 이름 지정)

     format: `.crt`

     > 위 명령어를 입력한 위치에 개인 키 생성됨

   - `keyout`: 새로 만든 개인 키를 쓸 파일 이름을 지정(파일 이름 지정)

     format: `.key`

2. 위 명령 입력 후 필요한 요청자의 정보 기입이 진행된다.

   1. `Country Name (2 letter code) [AU]` 국가 코드 

      한국: KO

   2. `State or Province Name (full name) [Some-State]` 도시명

      서울: seoul

   3. `Locality Name (eg, city) []` 구/군

      동작구: Dongjak-gu

      강남구: Gangnam-gu

   4. `Organization Name (eg, company) [Internet Widgits Pty Ltd]` 회사명

      개인용 인증서인 경우 개인의 이름이나 개인용 이메일 도메인 등을 입력

   5. `Organizational Unit Name (eg, section) []` 부서명

      속한 부서가 없다면 "-" 또는 "N/A" 등의 텍스트를 입력

   6. `Common Name (e.g. server FQDN or YOUR name) []` :  도메인 이름 혹은 서버IP

      개인용 인증서의 경우 인증서 발급을 요청하는 개인의 이름 또는 개인용 이메일 주소를 입력

   7. `Email Address []` 이메일 주소

3. 보안을 위해 권한 조정

   ```
   $ ll
   -rw-rw-r-- 1 hibernation hibernation 1489  3월  2 10:24 hibernation_.crt
   -rw------- 1 hibernation hibernation 1704  3월  2 10:09 hibernation_.key
   ```

   ```
   $ chmod 600 hibernation_.key
   $ chmod 600 hibernation_.crt
   ```

   ```
   $ ll
   -rw------- 1 hibernation hibernation 1489  3월  2 10:24 hibernation_.crt
   -rw------- 1 hibernation hibernation 1704  3월  2 10:09 hibernation_.key
   ```

   







```
클라이언트에서 사용하는 SSL 버전 확인 및 업데이트
```

