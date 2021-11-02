# Cloud SDK

google cloud는 구글에서 만든 가상머신 유로 플랫폼이다. 

>  project단위로 구동됨.



좌측 컴퓨터 인스턴스 > VM인스턴스

VM인스턴스의 사양에 따라 개당 가격이 측정된다.

> GPU사용시 비용이 크게 늘어난다.

컨테이너 이밎 배포 형식 > 쿠버네티스 사용시 



1. 프로젝트 만들기





### install

[공식문서](https://cloud.google.com/sdk/docs/quickstarts)

1. exe file download

   ```
   $ (New-Object Net.WebClient).DownloadFile("https://dl.google.com/dl/cloudsdk/channels/rapid/GoogleCloudSDKInstaller.exe", "$env:Temp\GoogleCloudSDKInstaller.exe")
   ```

2. exe file 실행

   ```
   & $env:Temp\GoogleCloudSDKInstaller.exe
   ```



### gcloud  CLI인증

Cloud SDK를 처음 시작하면 `default`라는 단일 configuration이 제공된다.

`gcloud init` 명령어를 실행하거나 `gcloud config set` 를 직접 실행하여 구성에서 속성을 설정할 수 있다.



```
$ gcloud init
```

SDK를 초기화한다.



1. 기존 설정된 config가 없는 경우

   ```
   Pick configuration to use:
    [1] Re-initialize this configuration [default] with new settings
    [2] Create a new configuration
   ```

   1. `2` 선택

      작업 시작

      1. configuration name 결정

         ```
         Enter configuration name. Names start with a lower case letter and contain only lower case letters a-z, digits 0-9, and hyphens '-':
         ```

         > str-number 형태의 configuration name를 결정
         >
         > (`init-1`)

      2. 계정 결정

         ```
         Choose the account you would like to use to perform operations for this configuration:
          [1] taeuk4958@gmail.com
          [2] Log in with a new account
         ```

         > 1 : 기존에 있던 account
         >
         > 2 : 새 계정에 login

         ```
         You are logged in as: [taeuk4958@gmail.com].
         
         This account has no projects.
         ```

         projects 존재 여부도 알려준다.

         - project가 없는 경우

           ```
           Would you like to create one? (Y/n)?  
           ```

           새 project 생성시

           ```
           Would you like to create one? (Y/n)? 
           ```

           project name 입력

           ```
           Enter a Project ID. Note that a Project ID CANNOT be changed later.
           Project IDs must be 6-30 characters (lowercase ASCII, digits, or
           hyphens) in length and start with a lowercase letter.
           ```

           > tensorflow-pytorch-3304 처럼

   2. `1` 선택

      1. 계정 결정

         ```
         Choose the account you would like to use to perform operations for this configuration:
          [1] taeuk4958@gmail.com
          [2] Log in with a new account
         ```

         > 1 : 기존에 있던 account
         >
         > 2 : 새 계정에 login

         ```
         You are logged in as: [taeuk4958@gmail.com].
         
         This account has no projects.
         ```

         projects 존재 여부도 알려준다.

         - project가 없는 경우

           ```
           Would you like to create one? (Y/n)?  
           ```

         

2. 기존 설정된 config가 있는 경우

   > `init-1` 이라는 configuration이 존재할 때

   ```
   Pick configuration to use:
    [1] Re-initialize this configuration [init-1] with new settings
    [2] Create a new configuration
    [3] Switch to and re-initialize existing configuration: [default]
   ```

   1, 2 입력시 위 기존 설정된 config가 없는 경우와 같다.

   `3`입력 > 계정결정



이제 `gcloud` 명령줄 도구 사용 가능





### Command

##### gcloud

- ```
  gcloud info
  ```

  gcloud의 version 등 information을 볼 수 있다.



- ```
  $ gcloud components update
  ```

  gcloud의 component를 업데이트한다.



##### configurations

- ```
  $ gcloud config configurations list
  ```

  현재 저장되어 있는 configurations 출력



- ```
  $ gcloud config configurations activate [configuration name]
  ```

  해당 이름의 configuration으로 전환



- ```
  $ gcloud config configurations describe [configuration name]
  ```

  해당 이름의 configuration의 정보 출력



- ```
  $ gcloud config configurations delete [configuration name]
  ```

  해당 이름의 configuration 삭제





- ```
  $ gcloud config list
  ```

  configurations의 설정 확인

  - region 서울로 설정

    ```
    $ gcloud config set compute/region asia-northeast3
    ```

  - zone 서울로 설정

    ```
    $ gcloud config set compute/zone asia-northeast3-a
    ```

  zone같은 경우 미리 설정해놓으면 `--zone` flag를 사용하지 않아도 default로 설정된 zone을 따라간다.





##### project

- ```
  $ gcloud config list project
  ```

  현재 configurations에 저장된 project 출력

  ```
  [core]
  project = planar-night-330807
  
  Your active configuration is: [default]
  ```



- ```
  $ gcloud projects delete [project_name]
  ```

  특정 project 삭제



- ```
  $ gcloud projects create [project_name]
  ```

  > [project_name]은 `-`이 두개 들어갈 정도로 길게

 

##### account

- ```
  $ gcloud auth list
  ```

  account정보 확인



#### property

- `--zone ZONE`

