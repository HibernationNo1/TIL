# nginx



### install

#### with docker

nginx 의 docker hub를 보면 TAG에

`mainline-alpine3.18-perl`, `1.25.4-bookworm-perl`,  `stable-perl`, `mainline-bullseye-perl` 등등 여러가지 word로 구분되어 있다.

1. 기능성

   - **Mainline**: Nginx의 최신 기능과 개선 사항이 포함된 version
   - **Stable**: 보다 안정적인 사용을 목적으로 하는 version.   운영 환경에서 사용하기에 적합

2. 환경

   - **Alpine**: Alpine Linux를 기반으로 둔 image.

     Alpine Linux는 보안, 효율성, 그리고 단순성에 중점을 둔 경량 리눅스 배포판 (이미지 크기가 작아 컨테이너 환경에서 인기 좋음)

   - **Bookworm**: Debian의 다음 안정 버전의 코드명 (Bookworm은 개발 중인 version을 의미한다.)

   - **Bullseye**: Debian 11의 코드명.



- `docker-compose_nginx.yml`

  ```
  version: "3"
  services:
    nginx:
      image: 'nginx:stable-bullseye-perl'
      container_name: 'nginx'
      ports: 
        - '80:80'
      volumes:
      # default 먼저 mount해야 sites-enabled dir mount가 정상적으로 이루어짐
        - ./nginx/sites-enabled/default:/etc/nginx/sites-enabled/default     
        - ./nginx/sites-enabled:/etc/nginx/sites-enabled
        - ./nginx/conf.d:/etc/nginx/conf.d
        - ./nginx/nginx.conf:/etc/nginx/nginx.conf
        - ./nginx/log:/var/log/nginx    # nginx container 내부의 log파일을 mount
      networks:
        - mobitv  
  
  networks:
    mobitv:
      name: mobitv
      driver: bridge
        
  # docker-compose -f docker-compose_nginx.yml up -d
  ```



### conf

#### nginx.conf

- log의 형식에 대한 정의 

  ```
  http {
  	# log format정의
      log_format upstreamlog '$remote_addr - $remote_user [$time_local] '		
                             '"$request" $status $body_bytes_sent '
                             '"$http_referer" "$http_user_agent" '
                             'upstream_response_time $upstream_response_time '
                             'upstream_addr $upstream_addr';
  	
  	# access_log를 어떤 format으로 기록할지 결정
      access_log /var/log/nginx/access.log upstreamlog;
      
      ...
  }
  ```

  - ```
    '$remote_addr - $remote_user [$time_local] '		
    '"$request" $status $body_bytes_sent '
    '"$http_referer" "$http_user_agent" '
    ```

    기본 log format 형식

  - `upstream_response_time` : 응답까지 걸린 시간 기록

  - `upstream_addr`:  어느 ` address:port` 로 요청을 보냈는지 기록



#### upstream.conf

```
# example_api 이라는 upstream을 위한 proxy server설정
upstream example_api {
    # 각 서비스의 주소와 포트를 정의
    server 192.168.110.107:10003;         
    server 192.168.110.104:10003;
}


server {
    listen 10003; # 외부에서 접근할 때 사용할 포트 번호

    location / {
        # nginx에 들어온 요청을 upstream에서 정의한 human_detection 그룹에 정의된 서버들 중 하나로 전달하도록 설정
        proxy_pass http://human_detection;    
        
        # nginx가 받은 Host header값을 upstream으로 전달
        proxy_set_header Host $host;

        # client의 실제 IP 주소를 X-Real-IP hearser에 설정하여 upstream으로 전달
        proxy_set_header X-Real-IP $remote_addr;

        # proxy server를 통과하는 동안 client의 IP 주소를 포함하는 X-Forwarded-For header를 추가하거나 update
        proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;

        # 원본 요청이 사용한 protocol(http 또는 https)을 X-Forwarded-Proto header에 설정하여 upstream으로 전달
        # scheme: 요청이 사용한 protocol을 포함
        proxy_set_header X-Forwarded-Proto $scheme;
    }
}
```



`nginx -t`

`http://localhost:10003`

