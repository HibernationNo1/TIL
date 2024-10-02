# install

#### with docker

docker-compose.yml

```
services:

  mongo_datacollector:
    image: 'mongo:7.0.14'
    container_name: 'mongo_datacollector'
    ports: 
      - '27018:27017'
    # volumes:
    #   - ./mongo/data:/var/lib/mongodb   # MongoDB 데이터 디렉토리 마운트
    #   - ./mongo/log:/var/log/mongodb    # MongoDB 로그 디렉토리 마운트
```







### Add user 

1. docker에 접속

   ```
   $ docker exec -it mongo_datacollector /bin/bash
   ```

2. user 추가  

   mongosh 실행

   ```
   $ mongosh
   ```

   `admin` 데이터베이스를 선택 후 user 추가

   ```
    > use admin
    > db.createUser({
     user: "user_name",
     pwd: "pwd",
     roles: [{ role: "readWrite", db: "collected_data" }]
   })
   ```

   - **ID**: user_name, **PW**: pwd



### 