# Connect

## mysql

#### check port number

```sql
mysql> show global variables like 'PORT';
```



해당 port가 외부에 의해 열려있는지 확인

```
$ netstat -tnlp
```

```
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name 
tcp        0      0 127.0.0.1:3306            0.0.0.0:*               LISTEN      -               
```

`Address`의 값이 `127.0.0.1:3306` 인 경우 local의 접속만 허용한다.

이를 바꿔줘야 한다.



mysql의 config file 찾아 `bind-address = 127.0.0.1` 를 `bind-address = 0.0.0.0`으로 변경

```
$ find / -name "my.cnf"
```

```
/etc/mysql/my.cnf
```

해당 file 변경

```
$ vi /etc/mysql/my.cnf
```

> 만일 `bind-address = 127.0.0.1`라는 문구가 없으면
>
>  ```
>  vi /etc/mysql/mysql.conf.d/mysqld.cnf
>  ```
>
> 여기서 확인

```
#bind-address = 127.0.0.1			주석처리하고
bind-address = 0.0.0.0				# 추가
```



이후 다시 `netstat -tnlp`확인

```
$ netstat -tnlp
```

```
Proto Recv-Q Send-Q Local Address           Foreign Address         State       PID/Program name 
tcp        0      0 0.0.0.0:3306            0.0.0.0:*               LISTEN      -           
```

`0.0.0.0:3306 `: 외부에서도 접속 가능

> ```
> $ sudo netstat -ntlp |grep mysql
> ```





#### user확인

```
$ sudo mysql -u root -p
```

```sql
mysql> SELECT User, Host, authentication_string FROM mysql.user;
```

```
+------------------+-----------+------------------------------------------------------------------------+
| User             | Host      | authentication_string                                                  |
+------------------+-----------+------------------------------------------------------------------------+
| debian-sys-maint | localhost | $A$005$~DYR\1nV7r]X^c^nG90/YP1G1ldSZXxz.bsVkXrZP7m2BiETQNph8yHThD      |
| mysql.infoschema | localhost | $A$005$THISISACOMBINATIONOFINVALIDSALTANDPASSWORDTHATMUSTNEVERBRBEUSED |
| mysql.session    | localhost | $A$005$THISISACOMBINATIONOFINVALIDSALTANDPASSWORDTHATMUSTNEVERBRBEUSED |
| mysql.sys        | localhost | $A$005$THISISACOMBINATIONOFINVALIDSALTANDPASSWORDTHATMUSTNEVERBRBEUSED |
| root             | localhost |                                                                        |
+------------------+-----------+------------------------------------------------------------------------+
6 rows in set (0.00 sec)
```

위의 출력에서 `Host`는 접속을 허용하는 host의 이름이다. `Host` 의 값이`localhost`인 경우 local의 접속만 허용한다.

외부의 접속도 허용하는 user를 만들어보자



##### create user

1. CREATE USER, DATABASE

   ```sql
   mysql>  CREATE USER 'user_name'@'%' IDENTIFIED BY 'pw';
   ```

   - `user_name`: 만들고자 하는 user의 name
   - `%`: 모든 host의 접근 허용
   - `pw` : 만들고자 하는  user의 password

   

   ```sql
   mysql> CREATE DATABASE database_name
   ```

   - `database_name`: 새롭게 만들 database의 이름

2. ip접근 허용

   ```sql
   mysql> GRANT ALL PRIVILEGES ON database_name.* TO 'user_name'@'%' WITH GRANT OPTION;
   ```

   - `database_name.*` : `database_name`라는 DB에 모든(`*`)권한 허용 

     > `*.*` 으로 한다면 모든 DB에 대한 모든 권한을 허용

   - `'user_name'@'%'`: `database_name`에 권한을 허용할 user정보 명시

   확인

   ```sql
   mysql> SHOW GRANTS FOR 'database_name'@'%'
   ```

   ```
   GRANT ALL PRIVILEGES ON `database_name`.* TO `user_name`@`%`  
   ```

   > 위 출력이 정상적으로 뜨는지 확인

   설정 적용

   ```sql
   mysql> FLUSH PRIVILEGES;
   ```

3. confirm

   ```sql
   mysql> SELECT User, Host, authentication_string FROM mysql.user;
   ```

   ```
   +------------------+-----------+------------------------------------------------------------------------+
   | User             | Host      | authentication_string                                                  |
   +------------------+-----------+------------------------------------------------------------------------+
   | user_name        | %         | $A$005$e/!cJ_@tL8c/ ywqYze7usjLLHFg8YBFp66.18mT8W.Zk7/nP3STU/jw6L/     |
   | debian-sys-maint | localhost | $A$005$~DYR\1nV7r]X^c^nG90/YP1G1ldSZXxz.bsVkXrZP7m2BiETQNph8yHThD      |
   | mysql.infoschema | localhost | $A$005$THISISACOMBINATIONOFINVALIDSALTANDPASSWORDTHATMUSTNEVERBRBEUSED |
   | mysql.session    | localhost | $A$005$THISISACOMBINATIONOFINVALIDSALTANDPASSWORDTHATMUSTNEVERBRBEUSED |
   | mysql.sys        | localhost | $A$005$THISISACOMBINATIONOFINVALIDSALTANDPASSWORDTHATMUSTNEVERBRBEUSED |
   | root             | localhost |                                                                        |
   +------------------+-----------+------------------------------------------------------------------------+
   ```

   - `user_name`이라는 user확인
   - `Host`값 `%`임을 확인

   > 비번 변경
   >
   > ```sql
   > mysql>  SET PASSWORD FOR 'root'@'localhost' = PASSWORD('바꿀비번');
   > ```

4. restart 

   ```
   $ sudo service mysql restart
   ```

   ```
   $ systemctl status mysql
   ```

   



