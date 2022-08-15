# secret



## from-literal

환경변수 `AWS_ACCESS_KEY_ID`, `AWS_SECRET_ACCESS_KEY` 에 저장된 값을 secret을 통해 전달

1. **create secert**

   ```
   $ export AWS_ACCESS_KEY_ID=value_1
   $ export AWS_SECRET_ACCESS_KEY=value_2
   ```

   

   ```
   $ kubectl -n NAMESPACE create secret SECRET_TYPE SECRET_NAME \
       --from-literal=AWS_ACCESS_KEY_ID=${AWS_ACCESS_KEY_ID} \
       --from-literal=AWS_SECRET_ACCESS_KEY=${AWS_SECRET_ACCESS_KEY}
   ```

   > `SECRET_NAME` : name of secret (`_`, `.` 는 포함하면 안됨)
   >
   > `-n NAMESPACE` : name space where secret is located
   >
   > - secret값을 전달하고자 하는 component가 동작하는 namespace가 `kubeflow-user-example-com` 라면, 해당 name space안에서 secret을 생성해야 한다. 
   >
   > `SECRET_TYPE` : 
   >
   > - `generic`  : 로컬 파일, 디렉터리 또는 리터럴 값을 사용할 때

   

   check secret

   ```
   $ kubectl get secret -n kubeflow
   ```

   

   if you want modify

   ```
   $ kubectl edit secret/SECRET_NAME -n kubeflow
   ```

   >수정할땐 secret값을 직접 base64로 인코딩해서 넣어야 한다.
   >
   >

2. **apply in component**

   ```python
   from kubernetes.client.models import V1EnvVar, V1EnvVarSource, V1SecretKeySelector
   
   import kfp.dsl as dsl
   
   @dsl.pipeline(name="hibernation_project")
   def project_pipeline(input_mode : str, input_dict : dict, gs_secret : dict):
       secret_name = "SECRET_NAME"
       _set_config_op = set_config_op(input_dict).add_env_variable(V1EnvVar(
                                                                   name ='AWS_ACCESS_KEY_ID', 	# set_config_op component의 환경변수 AWS_ACCESS_KEY_ID 값을 넣는다
                                                                   value_from= V1EnvVarSource(
                                                                               secret_key_ref=V1SecretKeySelector(
                                                                                               name=secret_name, 	# secret의 name을 특정
                                                                                               key = 'AWS_ACCESS_KEY_ID')))) \	# 특정된 secret안의 key값 
                                                  .add_env_variable(V1EnvVar(
                                                                   name ='AWS_SECRET_ACCESS_KEY', 
                                                                   value_from= V1EnvVarSource(
                                                                               secret_key_ref=V1SecretKeySelector(
                                                                                               name=secret_name, 
                                                                                               key = 'AWS_SECRET_ACCESS_KEY'))))                             
                                                                               
   ```





## from-file

특정 file의 content를(1개의 값) secret value로 전달



- `client_secrets_1.txt`

  ```
  AWS_ACCESS_KEY_ID=value_1
  ```

  

- `client_secrets_2.txt`

  ```
  AWS_SECRET_ACCESS_KEY=value_2
  ```



#### notice

단 아래처럼 `\n`이 포함된 경우` from-env-file`, `from-file` 을 사용하면 `\\n`으로 전달이 되어 버린다. 

`client_secrets_exam.txt`

```
-----BEGIN PRIVATE KEY-----\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n-----END PRIVATE KEY-----\n
```

- echo 출력

  ```
  subprocess.call(['echo $private_key'], shell=True)
  ```

  ```
  -----BEGIN PRIVATE KEY-----
  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  -----END PRIVATE KEY-----
  
  ```

  `\n` 이 줄바꿈으로 변환

  이 처럼 나와야함

- os.environ 출력

  ```
  print("os.environ['private_key']")
  ```

  ```
  -----BEGIN PRIVATE KEY-----\nxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n-----END PRIVATE KEY-----\n
  ```

  `\n` 이 줄바꿈으로 변환 없이 그대로 출력

  ```python
  flag = False
  private_key = ""
  for arp in list(os.environ['private_key']):
      if arp == '\\':
          private_key+=arp
          flag = True
          continue
  
      if arp == 'n' and flag == True:
          private_key = private_key[:-1]
          private_key +='\n'
          flag = False
          continue
  
       private_key+=arp
  print(private_key)
  ```

  ```
  -----BEGIN PRIVATE KEY-----
  xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  -----END PRIVATE KEY-----
  
  ```

  위 코드처럼 변환시켜줘야함





1. **create secert**

   ```
   $ export PATH_TO_FILE1=/home/ainsoft/hibernation/pipeline/client_secrets_1.txt
   $ export PATH_TO_FILE2=/home/ainsoft/hibernation/pipeline/client_secrets_2.txt
   ```

   

   ```
   $ kubectl -n kubeflow create secret generic SECRET_NAME \
     --from-file ${PATH_TO_FILE1} \
     --from-file ${PATH_TO_FILE2}
   ```

   

   check secret

   ```
   $ kubectl get secret -n kubeflow
   ```

   

   if you want modify

   ```
   $ kubectl edit secret/SECRET_NAME -n kubeflow
   ```

2. **apply in component**

   ```python
   from kubernetes.client.models import V1EnvVar, V1EnvVarSource, V1SecretKeySelector
   
   import kfp.dsl as dsl
   
   @dsl.pipeline(name="hibernation_project")
   def project_pipeline(input_mode : str, input_dict : dict, gs_secret : dict):
       secret_name = "SECRET_NAME"
       ev_AWS_ACCESS_KEY_ID = V1EnvVar(name ='AWS_ACCESS_KEY_ID', value_from= V1EnvVarSource( secret_key_ref=V1SecretKeySelector( name=client_sc_name, key = 'AWS_ACCESS_KEY_ID')))
       ev_AWS_SECRET_ACCESS_KEY = V1EnvVar(name ='AWS_SECRET_ACCESS_KEY', value_from= V1EnvVarSource( secret_key_ref=V1SecretKeySelector( name=client_sc_name, key = 'AWS_SECRET_ACCESS_KEY')))
       
       _set_config_op = set_config_op(input_dict).add_env_variable(ev_AWS_ACCESS_KEY_ID) \	
                                                  .add_env_variable(ev_AWS_SECRET_ACCESS_KEY)                             
                                                                               
   ```



## from-env-file

특정 file의 contents를(2개 이상의 값) secret value로 전달

`client_secrets.txt`

```
type=service_account
project_id=adroit-xxxxx-xxxx
private_key_id=0b55dxxxxxxx30211daf249b0xxxxxxxx
private_key=
client_email=xxxxxxx8@adroit-xxxxxxx-xxxxxx.iam.xxxxxxxx.com
client_id=xxxxxxxxxxxxxxxxxxxx4
auth_uri=https://accounts.google.com/o/xxxx/xxxx
token_uri=https://xxxx.googleapis.com/xxxxx
auth_provider_x509_cert_url=https://www.googleapis.com/xxxxx/v1/xxxxx
client_x509_cert_url=https://www.googleapis.com/robot/v1/metadata/xxxx/xxxxxxxxx-xxxxxxxxxxr-xxxxx.iam.gserviceaccount.com
```

- 9개의 값 한 번에 전달



단 아래처럼 `\n`이 포함된 경우` from-env-file`, `from-file` 을 사용하면 `\\n`으로 전달이 되어 버린다. 

[notice](#notice)













