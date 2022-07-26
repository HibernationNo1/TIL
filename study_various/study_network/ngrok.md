# ngrok

방화벽 넘어서 외부에서 로컬에 접속 가능하게 하는 터널 프로그램

외부에서도 `localhost:8080` 과 같은 local server에 접근할 수 있도록 임시 URL을 만들어준다.



#### install

[공식](https://dl.equinox.io/ngrok/ngrok/stable)

```
wget https://bin.equinox.io/c/4VmDzA7iaHb/ngrok-stable-linux-amd64.tgz
```

```
tar -xvzf ngrok-stable-linux-amd64.tgz
```

> 해당 명령어를 입력한 위치에 ngrok 폴더가 생김



### using

```
./ngrok http 8090
```

> 외부에서 local의 8090 port에 연결할 수 있는 URL을 만들어본다.

출력

```
ngrok by @inconshreveable                                                                                                                                           (Ctrl+C to quit)

Session Status                online
Session Expires               1 hour, 51 minutes
Version                       2.3.40
Region                        United States (us)
Web Interface                 http://127.0.0.1:4040
Forwarding                    http://eb45-1-214-32-67.ngrok.io -> http://localhost:8090
Forwarding                    https://eb45-1-214-32-67.ngrok.io -> http://localhost:8090

Connections                   ttl     opn     rt1     rt5     p50     p90
                              2       0       0.00    0.00    300.58  300.92

HTTP Requests
-------------

GET /favicon.ico               302 Found
GET /                          302 Found
GET /                          302 Found

```

- `Session Status` : session의 상태. online일 경우 정상

- `Session Expires` : 남은 session의 만료 시간

  > 만료 시간이 지나면 다시 `./ngrok http {port}`명령어 입력해야함
  >
  > 만료 시간 없이 사용하려면 계정 연동. 방법은 아래에

- `Region` : ngrok agent가 ternal을 hoting하기 위한 region

- `Web Interface` : ngrok dashboard를 제공하는 URL

- `Forwarding` : ngrok에서 제공하는 ternal URL로, 이를 통해 외부에서도 local 한경에 접근할 수 있다. (http, https제공)



#### account linking

ngrok은 예정을 연결하지 않고 사용할 경우 임시 URL에 연결 시 ERR_BGROK_6022를 만나게 된다. (wab app의 fronted server용도일 경우)



ngrok account는 **authtoken** 정보를 입력하여 연결할 수 있다.

1. [공식](https://dashboard.ngrok.com/login) 에서 회원가입 및 login

2. authoken확인

   좌측 탭 `Your Authtoken` 에서 `2CSyoOrkvZN0qowT8x72gKYb4qo_6uKpfheB2bC88e7isWSXd` 과 같은 정보 확인

3. ngrok에 link

   ```
   $ ./ngrok authtoken 2CSyoOrkvZN0qowT8x72gKYb4qo_6uKpfheB2bC88e7isWSXd
   ```

   > ```
   > Authtoken saved to configuration file: /home/user_name/.ngrok2/ngrok.yml
   > ```

4. `./ngrok http {port}`

   ```
   $ ./ngrok http 8090
   ```

   

