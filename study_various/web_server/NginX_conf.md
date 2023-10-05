# Using NginX 



#### install

Ubunru20.04

1. nginx의 공식 Ubuntu repository 주소 추가
   ```
   $ deb https://nginx.org/packages/ubuntu/ focal nginx
   $ deb-src https://nginx.org/packages/ubuntu/ focal nginx 
   ```

2. install nginx

   ```
   $ sudo apt update
   $ sudo apt install nginx
   ```

   

apt를 이용해 설치했다면, nginx의 설치 파일 기본 경로는 `/etc/nginx`에 있다.





#### nginx.conf

application기본 환경 설정

`nginx.conf` 파일은 Nginx가 동작해야 할 방식(option값)을 설정 값을 통해 지정한다.

해당 file의 구조 확인

```
worker_processes  1;				
events {							# network 동작에 관련된 설정 영역
    worker_connections  1024;
}
http { 								# web server에 대한 동작을 설정하는 영역
    include       mime.types;
    server {						# 하나의 website를 선언하는데 사용된다. 가상 호스팅(Virtual Hosk의 개념)
        listen       80;
        location / {				# 특정 URL을 처리하는 방법 정의
            root   html;
            index  index.html index.htm;
        }
    }
}

```





아래는 `nginx.conf` 파일의 예시 설정값.

```
user www-data;									# NGINX 프로세스가 실행되는 권한, root 권한은 보안상 위험함
												# root 권한을 피하고 보안을 강화하기 위해 존재.
												
worker_processes auto;							# 사용할 worker의 개수 설정.
												# auto설정 시 CPU 코어 수 만큼 worker생성
												
worker_rlimit_nofile 8192;						# NGINX worker process가 열 수 있는 최대 파일 디스크립터의 설정. 
												# 대량의 동시 접속이 예상되는 서버에서 필요한 자원을 확보하기 위해 사용
                                                
pid /run/nginx.pid;								# Nginx process의 PID (Process ID)가 저장될 파일의 위치 지정

include /etc/nginx/modules-enabled/*.conf;		# 다양한 추가 모듈들의 설정을 포함한다.

events {		# network 동작에 관련된 설정 
        worker_connections 768;					# 동시에 처리할 최대 연결 수
        										# 768으로 설정할 경우 384개의 client요청을 처리하고, 
        										# 이에 대응하는 384개의 backend연결을 만들 수 있다.
        										# Nginx가 동시에 처리하는 연결의 수 = (worker_processes x worker_connections)
        										
        # multi_accept on;						# worker process가 한 번에 여러 개의 새 연결을 수락할 것인지 지정
        										# default off : 한 번에 하나의 연결만 수락하며, 연결 수락에 대한 부하를 균등하게 분배할때 유용.
}

http {			# web server에 대한 동작을 설정

        ## 
        # Configs 
        ## 
        include    conf/mime.types;					# MIME 타입 설정 파일을 포함
        include    /etc/nginx/proxy.conf;			# proxy 설정 포함
        include    /etc/nginx/fastcgi.conf;			# fastcgi 설정 포함
        index    index.html index.htm index.php;    # web server가 dir에 대한 요청을 받았을 때, 기본적으로 제공할 파일들의 우선 순위를 설정     

        ##
        # Basic Settings
        ##

        sendfile on;							# 정적 파일을 효과적으로 전송하기 위해 
        										# 운영 체제의 sendfile 시스템 호출을 사용할 것인지를 결정
        										
        tcp_nopush on;							# sendfile on;이 활성화된 경우에 유용. 응답 헤더를 한 패킷으로 전송한다.
        
        tcp_nodelay on;							# 작은 패킷들이 가능한 한 빠르게 전송되도록 한다.
        										# 짧고 빈번한 요청이 있는 경우에 유용하다. (API서버 등)
        										
        keepalive_timeout 65;					# keep-alive client 연결이 얼마나 오랫동안 유지되어야 하는지를 설정
        
        types_hash_max_size 2048;				# NGINX가 파일 확장자에 따라 MIME 타입을 찾을 때 사용하는 해시 테이블의 최대 크기
        										# 예를 들어, '.html' 확장자는 text/html MIME 타입과 관련이 있고,
                                                # '.png'는 image/png MIME 타입과 관련이 있다.
        										# NGINX가 이런 관계를 빠르게 찾기 위해 해시 테이블이라는 자료 구조를 사용
        
        # server_tokens off;					# off시 NGINX가 응답 헤더에 자신의 버전 정보를 표시하지 않는다. 보안을 위해 종종 off사용

        # server_names_hash_bucket_size 64;		# server이름을 저장하기 위해 사용되는 hash bucket의 크기를 설정.
        										# server이름이 너무 길어서 hash bucket size를 넘는다면 
        										# 'could not build the server_names_hash'와 같은 오류 메시지 발생
        
        # server_name_in_redirect off;			# redirection URL에 server_name (지시자에 설정된 값)을 사용할지 여부를 결정
        										# default: on

        include /etc/nginx/mime.types;			# 외부 파일 /etc/nginx/mime.types를 포함하도록 지시
        										# mime.types 파일은 여러 파일 확장자와 그에 해당하는 MIME 타입들의 매핑을 포함한다.
        
        default_type application/octet-stream;	# NGINX가 알려진 MIME 타입을 찾지 못할 경우 사용할 기본 Content-Type을 설정	
        										# 'application/octet-stream'은 이진 데이터를 나타내는 일반적인 MIME 타입

        ##
        # SSL Settings
        ##

        ssl_protocols TLSv1 TLSv1.1 TLSv1.2 TLSv1.3; # Dropping SSLv3, ref: POODLE
        										# NGINX가 어떤 버전의 SSL/TLS 프로토콜을 사용하여 클라이언트와 통신할 것인지를 지정
        
        ssl_prefer_server_ciphers on;			# client와 server간의 SSL/TLS 통신에서 사용할 
        										# 암호화 알고리즘(암호) 세트를 결정할 때 
        										# server의 암호 목록을 client의 것보다 우선시할지 여부를 지정합니다
												# on으로 설정시 server가 지정한 암호 목록 순서대로 client와 협상
        ##
        # Logging Settings
        ##

        access_log /var/log/nginx/access.log;	# NGINX의 access에 관한 log 파일의 위치를 지정
        error_log /var/log/nginx/error.log;		# NGINX의 error에 관한 log 파일의 위치를 지정

        ##
        # Gzip Settings
        ##

        gzip on;								# gzip 압축을 활성화
        										# server 응답의 크기를 줄일 수 있어 네트워크 전송 시간이 단축된다.

        # gzip_vary on; 						# Vary: Accept-Encoding 헤더를 응답에 추가
        										# 이는 cache된 version의 resource가 압축된 version인지 아닌지를 판별하는 데 도움을 준다.
        										
        # gzip_proxied any; 					# 프록시된 요청에 대해서 gzip 압축을 언제 수행할지 결정
        										# any설정 시 모든 프록시 요청에 대해 압축을 수행
        										
        # gzip_comp_level 6; 					# 압축 수준을 설정 (1~9)
        
        # gzip_buffers 16 8k; 					# 압축을 위한 버퍼의 수와 크기를 설정
        										# 16 8k: 16개의 8KB 버퍼를 사용하도록 설정
        										
        # gzip_http_version 1.1; 				# gzip 압축을 사용하는 최소 HTTP 프로토콜 version지정
        
        # gzip_types text/plain text/css application/json application/javascript text/xml application/xml application/xml+rss text/javascript; 
        										# gzip 압축을 적용할 MIME 타입을 지정
        										# 지정된 MIME 타입에 대한 응답만 압축
 
        ## 
        # Virtual Host Configs 
        ## 
 
        include /etc/nginx/conf.d/*.conf; 		# `/etc/nginx/conf.d`은 추가적인 구성이나 모듈에 관한 설정 파일(.conf)을 저장하는 경로
        include /etc/nginx/sites-enabled/*; 	# 각 web site나 application을 위한 'server block' 설정 파일을 저장하는 경로
        										# 특정 사이트의 설정을 활성화하거나 비활성화하할 때 유용.
        									
        ## 
        # example of website conf
        ##
        
        server { 			# 특정 domain에 대한 설정
            listen       80;									# web server가 80 port로 들어오는 HTTP 요청을 기다리도록 설정
            server_name  domain1.com www.domain1.com;			# 설정하여 관리하고자 하는 domain을 지정
            access_log   logs/domain1.access.log  main;			# 해당 domain의 access log를 저장할 file의 path
            root         html;									# 

            location ~ \.php$ {									# .php 확장자로 끝나는 요청을 처리하는 방법을 정의
            
            	fastcgi_pass   127.0.0.1:1025;					# .php 파일에 대한 요청을 처리하기 위해 
            }													# 127.0.0.1 주소의 1025 포트로 실행되는 FastCGI 프로세스에 전달
            
            
        server { # simple reverse-proxy
        listen       80;
        server_name  domain2.com www.domain2.com;
        access_log   logs/domain2.access.log  main;

        # serve static files
        location ~ ^/(images|javascript|js|css|flash|media|static)/  {	# 특정 URI 패턴에 일치하는 요청을 처리하는 방법을 정의
        	root    /var/www/virtual/big.server.com/htdocs;				# 정적 파일을 제공할 디렉토리를 지정
              expires 30d;												# 정적 컨텐츠의 유효기간을 30일로 설정하여, 브라우저 캐싱을 향상
        	}

        # pass requests for dynamic content to rails/turbogears/zope, et al
        location / {													# 루트 URI(/)로 들어오는 모든 요청을 처리하는 방법을 정의
              proxy_pass      http://127.0.0.1:8080;					# 모든 요청을 로컬 호스트의 8080 포트로 proxy
        	}
      	}

} 
 
#mail {						# Nginx를 main proxy server로 사용할 때 활성화.
#       # See sample authentication script at:
#       # http://wiki.nginx.org/ImapAuthenticateWithApachePhpScript
# 
#       # auth_http localhost/auth.php;
#       # pop3_capabilities "TOP" "USER";
#       # imap_capabilities "IMAP4rev1" "UIDPLUS";
# 
#       server {
#               listen     localhost:110;
#               protocol   pop3;
#               proxy      on;
#       }
# 
#       server {
#               listen     localhost:143;
#               protocol   imap;
#               proxy      on;
#       }
#}

```





### proxy.conf

proxy관련 환경 설정 file.

이 설정은 NGINX가 백엔드 서버와 통신할 때의 동작을 조절할때 사용된다.

아래는 `proxy.conf` 파일의 예시 설정값.

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







### fastcgi.conf

fastCGI관련 환경 설정

아래는 `fastcgi.conf` 파일의 예시 설정값.

```
fastcgi_param  SCRIPT_FILENAME    $document_root$fastcgi_script_name;
fastcgi_param  QUERY_STRING       $query_string;
fastcgi_param  REQUEST_METHOD     $request_method;
fastcgi_param  CONTENT_TYPE       $content_type;
fastcgi_param  CONTENT_LENGTH     $content_length;

fastcgi_param  SCRIPT_NAME        $fastcgi_script_name;
fastcgi_param  REQUEST_URI        $request_uri;
fastcgi_param  DOCUMENT_URI       $document_uri;
fastcgi_param  DOCUMENT_ROOT      $document_root;
fastcgi_param  SERVER_PROTOCOL    $server_protocol;
fastcgi_param  REQUEST_SCHEME     $scheme;
fastcgi_param  HTTPS              $https if_not_empty;

fastcgi_param  GATEWAY_INTERFACE  CGI/1.1;
fastcgi_param  SERVER_SOFTWARE    nginx/$nginx_version;

fastcgi_param  REMOTE_ADDR        $remote_addr;
fastcgi_param  REMOTE_PORT        $remote_port;
fastcgi_param  SERVER_ADDR        $server_addr;
fastcgi_param  SERVER_PORT        $server_port;
fastcgi_param  SERVER_NAME        $server_name;

# PHP only, required if PHP was built with --enable-force-cgi-redirect
fastcgi_param  REDIRECT_STATUS    200;

```



### mime.types

file 확장명과 MIME type목록