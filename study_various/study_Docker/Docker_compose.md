# Docker_compose

Docker compose file(YAML file)에 여러 container를 일괄적으로 정의하고 실행하며, container들의 실행 순서 DB연결 등을 정할 수 있는 tool이다.



### install

https://docs.docker.com/compose/install/

```
$ sudo curl -L "https://github.com/docker/compose/releases/download/1.29.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
```

```
$ sudo chmod +x /usr/local/bin/docker-compose
```

check

```
$ docker-compese version
```





### command

##### up

create containers and execution docker compose

```
$ docker-compose up -d
```

`-d` : background model로 실행

- `-f` : 다른 directory에 존재하는 compose file을 실행하고싶을 때 사용

  ```
  $ docker-compose -f /other-dir/tmp_name/docker-compose.yml
  ```



##### start

execution docker compose(when created cotainers)

```
$ docker-compose start
```



##### stop

stop containers in docker compose

```
$ docker-compose stop
```

- **kill** : 강제 정지

  ```
  $ docker-compose kill
  ```

  



##### ps

docker compose의 statuse를 확인

```
$ docker-compose ps
```



##### scale

specific한 container의 개수를 늘리고 싶을 때 사용

```
$ docker-compose scale servise_name = 2
```

> ```
> $ docker-compose scale inference = 2
> ```
>
> inference라는 container를 2개로 늘린다.



##### run

specific한 container만 running하고싶을 때 사용

```
$ docker-compose run servise_name
```



##### down

docker compose에 포함된 container를 stop하는 command

```
$ docker-compose down
```



##### config

docker compose file의 구성 확인

```
$ docker-compose config
```





## YAML file

### version

compose version을 의미. 

version에 따라서 지원 gramma가 다르다.



### services

compose를 이용해서 실행할 container option을 definition한다.



#### **image**

compose를 통해 execution할 image를 지정한다.



#### deploy

services distrubution 및 exection과 관련된 구성을 지정한다.

push를 



#### **build**

container build



#### **commad**

container에서 execution할 command 지정



#### **port**

conainer가 공개하는 port를 나열



#### **link**

다른 container와 연계할 때 연계할 container 지정



#### **expose**

port를 link로 연계된 container에게만 공개할 port



#### volumes

container에 volume을 mount



#### environment

container에 appliy할 environment variable을 definition



#### restart

container가 종료될 때 apply할 restart 정책



#### depends_on

container간의 종속성을 definition. 

definition한 contianer가 먼저 execution되어야 한다.



### e.g.

```yaml
version : "3.9"		

services:
	ubuntu:
		image: 
	anaconda:
		image: 
	cuda:
		image: 
	cudnn:
		image: 
	
	inference:
```

