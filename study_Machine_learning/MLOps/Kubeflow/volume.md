# Volume

### persistent volume

#### dashboard

kubeflow dashboard를 통해 persistent volume을 생성

`+ New Volume`: 



**Storage Class**

- `local-path`: local에 persistent volume과 mount되는 directory가 생성된다.

  - path : `/opt/local-path-provisioner/volume_name`

  - **Only support `ReadWriteOnce` access mode**

- `None`: data보존은 가능하지만 local에서의 접근이 안된다.



**Access Mode**

- `ReadWriteOnce`: 1명의 사용자(생성한 본인)만 read, write 가능
- `ReadOnlyMany`: 2명 이상의 사용자와 공유하며 read만 가능
- `ReadWriteMany`: 2명 이상의 사용자와 공유하며 read, write 가능





#### SDK

**VolumeOp**

```python
import kfp.dsl as dsl

@dsl.pipeline(name="exam")
def exam_pipeline(input_1: int, input_2: str):  
    vop = dsl.VolumeOp(name="pipeline-volume",
                       resource_name="pipeline-pvc",
                       modes=dsl.VOLUME_MODE_RWO,
                       size="10Gi")
    
    _exam_op = exam_op(cfg_train).add_pvolumes({'/mount_path': vop.volume})
```

- `name`: volume의 name   `volume_name`은 없는 arg

- `resource_name`: 생성될 PVC의 원하는 이름

- `modes`: Access Mode 결정

  - `dsl.VOLUME_MODE_RWO`: ReadWriteOnce
  - `dsl.VOLUME_MODE_RWM`: ReadWriteMany
  - `dsl.VOLUME_MODE_ROM`: ReadOnlyMany

- `storage_class`: PVC에 사용할 storage_class결정

  > default: `None` == `local_path`
  >
  > `local_path` 인 경우 `modes`는 반드시 `dsl.VOLUME_MODE_RWO` 이여야 한다.

- `size` : volume의 크기



**tip)**

- pipeline function안에서 위 PVC가 선언되면 kubeflow dashboard의 volumes에 pvc가 생성된 것을 확인할 수 있고, `/opt/local-path-provisioner`에서 `~~~pipeline-pvc`라는 dir을 확인할 수 있다.

- 같은 name의 volume은 중복되어 create될 수 없으며, 한 번 생성된 `VolumeOp`를 그대로 두고 사용하게 된다. 

  이 때 modes, size같은 부분을 변경하여 선언하여도 기존 생성된 volume에 변경점 없이 그대로 사용된다.

  





#### delete

volume을 delete할 땐 dashboard에서 진행해도 되지 않는다.

```
$ kubectl delete pvc pvc_name -n project-pipeline
```





