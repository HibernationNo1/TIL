# upstream.conf

load balancing 을 위한 upstream을 정의하는 configure  파일

특정 port로 들어온 요청을 다른 {주소}:{port}로 전달하는 역할을 한다.

- 해당 파일은 `/etc/nginx/sites-enabled/`의 경로에 위치한다.

- 해당 파일이 제대로 활성화 하기 위해선 `/etc/nginx/nginx.conf` 의 내용 중 http 섹션에 아래 내용이 추가되어야 한다.

  ```
  	include /etc/nginx/sites-enabled/upstream.conf;
  ```

  또는

  ```
  	include /etc/nginx/sites-enabled/*;
  ```

  

**예시**

```
# example_api 이라는 upstream을 위한 proxy server설정
upstream example_api {
	least_conn;     # load balancing method 
    # 각 서비스의 주소와 포트를 정의
    server 192.168.110.107:10003;         
    server 192.168.110.104:10003;
}


server {
    listen 10003; # 외부에서 접근할 때 사용할 포트 번호

    location / {
        # nginx에 들어온 요청을 upstream에서 정의한 example_api그룹에 정의된 서버들 중 하나로 전달하도록 설정
        proxy_pass http://example_api;    
        
        # 클라이언트가 요청한 원본 호스트명을 백엔드로 전달
        proxy_set_header Host $host;            

        # 클라이언트의 실제 IP 주소를 백엔드 애플리케이션에 전달    (`$remote_addr`: 클라이언트의 IP 주소)
        proxy_set_header X-Real-IP $remote_addr;        

        # 프록시 체인을 통과하며 변경된 클라이언트의 IP 주소를 전달.
        # 백엔드 애플리케이션은 요청이 거친 모든 프록시의 IP 주소를 알 수 있다.
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;        
        
        # 라이언트가 요청을 보낼 때 사용한 프로토콜(http 또는 https)을 백엔드 애플리케이션에 전달
        # 클라이언트가 사용한 프로토콜을 전부 https로 변경하려면 `proxy_set_header X-Forwarded-Proto https;` 를 지정
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
```

- nginx를 docker로 띄웠고, local device의 여러 docker에 대한 load balance 역할을 하고자 한다면 upstream을 아래와 같이 사용

  ```
  upstream example_api {
      # 각 서비스의 주소와 포트를 정의
      server {docker_name_1}:{service port};         
      server {docker_name_2}:{service port};         
  }
  ```

  - 이 때 nginx와 service docker의 docker network는 동일해야 한다.  
  - `service port`는 docker를 run할 때의 port forwarding한 port를 적는것이 아니라, service server의 자체 port를 적어햐 한다.

- load balancing method 

  1. **Round Robin (기본 설정)**:
     - 요청이 서버 그룹의 각 서버에 순차적으로 분배됩니다.
     - 특별한 설정을 하지 않으면 Nginx는 기본적으로 Round Robin 방식을 사용합니다.
  2. **Least Connections**:
     - 연결 수가 가장 적은 서버에 요청을 분배합니다.
     - `least_conn` 지시어를 사용하여 설정합니다.
     - 서버 간의 연결 처리 능력이 다를 때 유용하게 사용할 수 있습니다.
  3. **IP Hash**:
     - 클라이언트의 IP 주소를 해싱하여 요청을 특정 서버에 지속적으로 라우팅합니다.
     - `ip_hash` 지시어를 사용하여 설정합니다.
     - 세션 유지가 필요한 애플리케이션에 적합한 방식입니다.
  4. **Hash**:
     - 특정 키를 해싱하여 요청을 분배합니다.
     - `hash` 지시어와 함께 해시 키를 지정하여 사용합니다.
     - `hash $request_uri consistent;`와 같이 사용하여 요청 URI 기반으로 요청을 분배할 수 있습니다.
  5. **Random**:
     - 무작위로 서버에 요청을 분배합니다.
     - `random` 지시어를 사용하여 설정할 수 있으며, 선택적으로 두 가지 모드(`random two;`, `random two least_conn;`) 중 하나를 사용할 수 있습니다.
     - `random two;`는 무작위로 두 서버를 선택한 후, Round Robin 방식으로 요청을 분배합니다.
     - `random two least_conn;`는 무작위로 두 서버를 선택한 후, 연결 수가 가장 적은 서버에 요청을 분배합니다.

