# nginx.conf

- Nginx 웹 서버의 주요 설정 파일로, Nginx의 작동 방식과 각종 설정을 정의한다.

   Nginx가 시작할 때 읽어들여지며, 서버의 기본 동작, 연결 처리 방법, 로깅, 파일 위치 등을 설정하는 데 사용된다.

- 해당 파일은 `/etc/nginx/nginx.conf`에 위치한다





## 기본 구조

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



 `nginx.conf` 파일의 예시 설정값.

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

  - 기본 log format 형식

    ```
    '$remote_addr - $remote_user [$time_local] '		
    '"$request" $status $body_bytes_sent '
    '"$http_referer" "$http_user_agent" '
    ```

  - `upstream_response_time` : 응답까지 걸린 시간 기록

  - `upstream_addr`:  어느 ` address:port` 로 요청을 보냈는지 기록



