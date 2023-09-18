# MongoDB 

1. install

   new repository를 추가하기 위한 종속성 install

   ```
   $ sudo apt update
   $ sudo apt install dirmngr gnupg apt-transport-https ca-certificates software-properties-common
   ```

   repository GPG key확보

   

   ```
   $ wget -qO - https://www.mongodb.org/static/pgp/server-4.4.asc | sudo apt-key add -
   $ sudo add-apt-repository 'deb [arch=amd64] https://repo.mongodb.org/apt/ubuntu focal/mongodb-org/4.4 multiverse'
   ```

   

   설치

   ```
   $ sudo apt install mongodb-org
   ```

   

   확인

   ```
   $ mongo --eval 'db.runCommand({ connectionStatus: 1 })'
   ```

   

   실행

   ```
   $ mongo
   ```

   

   

   

2. add user

   ```
   $ mongo
   ```

   

   Database전환

   ```
   > use admin
   ```

   > `> use {DB이름}`

   

   user list확인

   ```
   > show users			# mongosh 명령어
   > db.getUsers()			# mongoDB method
   ```

   

   create user

   ```
   db.createUser(
     {
       user: "kakaortb",
       pwd: "kakaortb1234",
       roles: [ { role: "readWrite", db: "admin" } ]
     }
   )
   ```

   > - user name: `kakaortb`
   >
   > - user password: `kakaortb1234`
   >
   > - 계정 권한: `userAdminAnyDatabase`  (admin)
   >   - "read"
   >   - "readWrite"
   >
   > - 대상 db: `admin`
   >
   > 

   ```
   # 출력
   Successfully added user: {
           "user" : "kakaortb",
           "roles" : [
                   {
                           "role" : "userAdminAnyDatabase",
                           "db" : "admin"
                   }
           ]
   }
   ```

   

   > delete user
   >
   > ```
   > > db.dropUser("kakaortb")
   > ```



### 3T

MongoDB의 UI를 지원하는 tool

