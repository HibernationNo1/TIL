### Taint & Toleration

- **taint** : pod를 schedule할지 여부를 결정하는 option. node마다 설정가능. 

  설정한 노드에는 pod이 스케줄되지 않음

- **toleration** : taint를 무시할수있는 option



주로 노드를 지정된 역할만 하게 할 때 사용된다.

>  e.g) GPU만 쓰는 노드에는 GPU관련 pod만 구동되도록 하도록





#### taint

##### options

- `NoSchedule` : toleration이 없으면 pod이 스케쥴되지 않음, 기존 실행되던 pod에는 적용 안됨
- `PreferNoSchedule` : toleration이 없으면 pod을 스케줄링안하려고 하지만 필수는 아님, 클러스터내에 자원이 부족하거나 하면 taint가 걸려있는 노드에서도 pod이 스케줄링될 수 있음
- `NoExecute`: toleration이 없으면 pod이 스케줄되지 않으며 기존에 실행되던 pod도 toleration이 없으면 종료시킴.



##### apply taint

taint의 구별은 `key`, `value`으로 한다.

```
$ kubectl taint node node_name key_name=value:option
```

- `node_name`: 해당 taint규칙을 적용할 node의 이름
- `key_name`:  해당 taint규칙의 label 
-  `value`: 해당 taint규칙의 custom name
- `option`: 적용하고자 하는 taint규칙
  - `NoSchedule`
  - `PreferNoSchedule`
  - `NoExecute`

e.g.

```
$ kubectl taint node hibernation worker_1=value_1:NoSchedule
```





##### taint on-off

- 특정 node에서 taint관계 없이 모든 pod가 구동 가능하게 taint해제

  ```
  $ kubectl taint nodes node_name node-role.kubernetes.io/master-
  ```

- 다시 taint 켜기

  ```
  $ kubectl taint nodes node_name node-role.kubernetes.io=master:NoSchedule
  ```

  

#### Toleration

##### apply Toleration

특정 daemonset에 pod구동에 대한 규칙(taint)를 설정하는 방법

1. edit resource

   

   ```
   $ kubectl edit daemonset daemonset_name -n name_space
   ```

   spec.tolerations 아래 아래 문구를 추가한다.

   - master node에도 pod를 구동하도록 할 때

     ```
     spec:
     	tolerations
     		- key: node-role.kubernetes.io/master
      		  effect: NoSchedule
     ```

   - 특정 node에 pod를 구동하도록 할 때

     ```
     spec:
     	tolerations
     		- key: key_name
     		  value: value_name
     		  operator: Equal
      		  effect: NoSchedule
     ```

     - `key`: 적용할 taint규칙의 label name
     - `value`: 적용할 taint규칙의 custom name
     - `operator`: 
       - `Equal`: key와 value값이 적용할 taint규칙과 전부 일치하는지 확인
       - `Exists`: 어떤 taint가 존재하든 무시
     - `effect`: 적용할 taint규칙의 명시된 option

2. 이후 해당 resource 재시작

   ```
   $ kubectl rollout restart daemonset daemonset_name -n name_space
   ```

