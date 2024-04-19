# proxy.conf

proxy관련 환경 설정 file.

이 설정은 NGINX가 백엔드 서버와 통신할 때의 동작을 조절할때 사용된다.

- 해당 파일은 `/etc/nginx/proxy.conf`의 경로에 위치한다.

- 해당 파일이 제대로 활성화 하기 위해선 `/etc/nginx/nginx.conf` 의 내용 중 http 섹션에 아래 내용이 추가되어야 한다.

  ```
  include    /etc/nginx/proxy.conf;	
  ```

  

  

 `proxy.conf` 파일의 예시 설정값.

```
proxy_redirect          off;
proxy_set_header        Host            $host;
proxy_set_header        X-Real-IP       $remote_addr;
proxy_set_header        X-Forwarded-For $proxy_add_x_forwarded_for;
client_max_body_size    10m;
client_body_buffer_size 128k;
proxy_connect_timeout   90;
proxy_send_timeout      90;
proxy_read_timeout      90;
proxy_buffers           32 4k;
```

- `proxy_redirect`

  backend 서버에서 오는 redirection URL을 변경할 것인지를 설정

  `off`로 설정하면, NGINX는 리다이렉션 URL을 변경하지 않는다.

- `proxy_set_header        Host            $host;`

  proxy 요청의 `Host` 헤더 값을 원래 client 요청의 host 이름으로 설정

- `proxy_set_header        X-Real-IP       $remote_addr;`

  proxy 요청에 `X-Real-IP` 헤더를 추가하고 이를 원래 client의 IP 주소로 설정합니다.

- `proxy_set_header        X-Forwarded-For $proxy_add_x_forwarded_for;`

  proxy 요청에 `X-Forwarded-For` 헤더를 추가하고 이를 원래 client의 IP 주소로 설정

  만약 여러 proxy를 거친 경우, 이 헤더는 여러 IP 주소를 포함할 수 있습니다.

- `client_max_body_size`

  client 요청의 본문 크기의 최대 허용 값을 설정

- `client_body_buffer_size`

  client 요청 본문을 버퍼링하는 데 사용되는 버퍼의 크기를 설정

- `proxy_buffers           32 4k;`

  응답 데이터를 버퍼링하는 데 사용되는 버퍼의 수와 크기를 설정

