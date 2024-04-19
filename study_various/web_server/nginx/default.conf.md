# default.conf

- Nginx 웹 서버의 기본 설정을 담고 있는 구성 파일

- 해당 파일은 `/etc/nginx/conf.d/default.conf` 에 위치한다.

- `upstream.conf` 와 동일한 문법으로 작성이 가능하다.

  `upstream.conf` 과 같은 역할로 사용할 수 있지만, 보통은 Nginx가 웹 요청을 수신하고 처리하는 방법에 대한 초기 설정을 제공하는데 사용된다.

- 해당 파일이 제대로 활성화 하기 위해선 `/etc/nginx/nginx.conf` 의 내용 중 http 섹션에 아래 내용이 추가되어야 한다.

  ```
  	include /etc/nginx/conf.d/default.conf;
  ```

  또는

  ```
  	include /etc/nginx/conf.d/*;
  ```

  

**예시**

```
server {
    # 80 port로 들어오는 요청을 localhost로 전송
    listen       80;
    listen  [::]:80;
    server_name  localhost;

    location / {
        root   /usr/share/nginx/html;
        index  index.html index.htm;
    }

    error_page   500 502 503 504  /50x.html;
    location = /50x.html {
        root   /usr/share/nginx/html;
    }
}

server {
    # http://mypublicdomain.com:10004 으로 들어오는 요청을 http://localhost:10003 으로 전송
    listen       10004;
    listen  [::]:10004;
    server_name  mypublicdomain.com;

    location / {
        proxy_pass http://localhost:10003;  # 내부 IP 주소와 포트

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

        root   /usr/share/nginx/html;
        index  index.html index.htm;
    }

    error_page   500 502 503 504  /50x.html;
    location = /50x.html {
        root   /usr/share/nginx/html;
    }
}
```

