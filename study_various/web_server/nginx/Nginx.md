# Nginx

- 강력한 고성능 웹 서버, 리버스 프록시, 이메일 프록시(POP3/IMAP), HTTP 캐시 등으로 사용되는 툴
- 비동기 이벤트 기반 구조로 설계되어 많은 동시 연결을 효율적으로 처리할 수 있다.
- 로드 밸런싱, 웹 콘텐츠 캐싱, 보안 기능을 제공하여 웹 애플리케이션의 성능과 안정성을 향상시킬 수 있다.



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



**설치 과정**

1. nginx를 구성하는 설정 파일을 확보한다. (최초 1회)
2. 설정 파일에 본인이 필요로 하는 설정을 추가한다.
3. 변경된 내용의 설정 파일을 volume mount하여 nginx container를 실행한다.



#### configure file 확보하기

1. nginx container 실행

   `docker-compose_nginx.yml`

   ```
   version: "3"
   services:
     nginx:
       image: 'nginx:stable-bullseye-perl'		 
       container_name: 'nginx'
       ports: 
         - '80:80'
         
   # docker-compose -f docker-compose_nginx.yml up -d
   ```

2. 기본 파일 확보

   ```
   $ docker cp nginx:/etc/nginx/sites-enabled/default ./nginx/sites-enabled/
   $ docker cp nginx:/etc/nginx/sites-enabled ./nginx/sites-enabled/
   $ docker cp /etc/nginx/conf.d ./nginx/conf.d
   $ docker cp nginx:/etc/nginx/nginx.conf ./nginx/nginx.conf
   ```

   

#### start nginx

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
  
        
  # docker-compose -f docker-compose_nginx.yml up -d
  ```
  
  - git으로 버전관리를 할 때,  `./nginx/conf.d`이 경로가 .gitignore에 없음에도 추적 안되는 경우가 있음. 반드시 확인할 것. 
  -  `./nginx/conf.d` 이 경로에 `default.conf`가 반드시 있어야함
  - port에는 nginx 리버스 프록시의 역할로 사용할 port번호를 를 추가해야 한다. 





