# Public key

private repository를 git clone하기 위한 방법

###  

## personal-access-token



**remote: Support for password authentication was removed on August**

git push과정에서 

```
Username for 'https://github.com': HibernationNo1
Password for 'https://HibernationNo1@github.com':
```

password입력 시 아래와 같은 메시지를 만날 경우

```
remote: Support for password authentication was removed on August 13, 2021.
```

개인 access key가 만료되었다는 뜻

github계정에서 setting > 좌측 하단  Developer settings > Personal access tokens

Note : access key의 이름

발급시 `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` 와 같은 key(Password)를 받을 수 있다.



만일 이미 clone된 repository에 새로 발급한 personal-access-token을 적용하고 싶다면 아래 명령어

```
git remote set-url origin https://<your-username>:<your-personal-access-token>@github.com/<your-username>/<your-repo>.git
```





## SSH key

### generate

- check if already exist before generate public key

  ```
  $ cd /home/username/.ssh
  ```

  - `username` 본인 계정

  위 경로에 다른 key가 있는지 확인할 것.

  이미 public key가 있는데, 또 만들면 덮어씌워짐



1.  generate ssh public key

   ```
   $ ssh-keygen -t rsa -C "github_email"
   ```

   > - `-t`: public key 지문 종류 중 하나 결정
   >
   >   > `rsa`, `Ed25519`, `ECDSA` 등이 있다.
   >
   > - `-C "github_email"` : public key를 적용할 github계정 이멜

   ```
   Generating public/private rsa key pair.
   ```

   

   - 저장하고자 하는 위치 결정

     ```
     Enter file in which to save the key (/home/username/.ssh/id_rsa): 
     ```

     그냥 enter치면 명시된 path에 key가 생성된다.

     ```
     Your identification has been saved in /home/username/.ssh/id_rsa
     Your public key has been saved in /home/username/.ssh/id_rsa.pub
     The key fingerprint is:
     SHA256:SCI00gpV8VA26kuCpB2j6UILPW/zMmgcchyM3/yNDRU username@gmail.com
     The key's randomart image is:
     +---[RSA 3072]----+
     |.o+.+o+          |
     |.o.. = .E        |
     |.=+ o o  .       |
     |=*o= o ..        |
     |*+=+o ..S        |
     |= *=o..          |
     |.* o=. =         |
     |. +.ooo o        |
     | .   o.          |
     +----[SHA256]-----+
     ```

   생성된 path에 가서 확인

   ```
   $ cd /home/username/.ssh
   $ ls
   ```

   ```
   id_rsa  id_rsa.pub  known_hosts
   ```

   - `id_rsa`: private key가 저장되어 있음

     개인키는 절대 공개되어선 안된다.

   - `id_rsa.pub`: pubilc key가 저장되어 있음

     > rsa방식으로 key를 생성하는 경우 위와 같은 name으로 file이 생성된다.

2. public key registration to github

   1. confirm private key

      ```
      $ cat id_rsa.pub
      ```

      해당 key 복사

   2. login github and go `setting` > `SSH and GPG keys` 

      `New SSH key` 선택

   3. add key

      - `title`: 구분하기 편한 name
      - key복붙





### dockerfile

`mv` 명령어를 통해 `id_rsa`를 build할 docker file과 같은 위치로 이동

```

# To fix GPG key error when running apt-get update
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/machine-learning/repos/ubuntu1804/x86_64/7fa2af80.pub
RUN apt-get update 

RUN apt-get install -y git

RUN mkdir /root/.ssh
ADD id_rsa /root/.ssh/id_rsa
RUN chmod 600 /root/.ssh/id_rsa
RUN touch /root/.ssh/known_hosts
RUN ssh-keyscan github.com >> /root/.ssh/known_hosts

RUN git clone git@github.com:HibernationNo1/pipeline_dataset.git
```

- `RUN mkdir /root/.ssh` : public key를 저장할 dir 생성
- `ADD id_rsa /root/.ssh/id_rsa`: ADD private key 
- `RUN chmod 600 /root/.ssh/id_rsa` : public key의 권한 설정
- `RUN touch /root/.ssh/known_hosts` : known_hosts생성
- `RUN ssh-keyscan github.com >> /root/.ssh/known_hosts` : github의 repo를 clone할 것이기 때문에 미리 허용
- `RUN git clone git@github.com:HibernationNo1/pipeline_dataset.git` : git clone시 hhtp가 아닌, ssh를 clone해야 한다.