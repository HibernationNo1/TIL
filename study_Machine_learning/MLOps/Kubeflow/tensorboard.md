# Tensorboard

object store 또는 PVC에 event file을 save하여 tensorboard viewer를 사용할 수 있게 하는 기능이다.



`+ New TensorBoard`

- Object Store

  - google cloud storage
  - S3
  - Minio

- PVC

  - PVC Name: 기존에 만들어둔 persistent volume중에서 선택

  - Mount Path: PVC의 경로를 기준으로 event file이 save될 path

    > PVC의 경로가 `/pvc`일 때, 
    >
    > Mount Path: `tensorboard/` 라면
    >
    > event file은 `/pvc/tensorboard/` 에 저장되어야 한다.



tip)

tensorboard를 만들 때 시점의 path의 event file만 읽어온다.

특정 tensorboard를 만든 후 해당 path의 event file을 전부 삭제 후 새로운 event file을 만들어도 기존의 tensorboard는 새롭게 만들어진 file이 아닌, 이미 삭제 된 이전의 file을 읽어오게 된다.

때문에 같은 path에 새로운 event file을 만든 후 읽어오고자 한다면 `+New tensorboard`를 통해 path를 설정하여 새롭게 만들어야 한다.



**CONNECT**

tensorboard viewer를 확인할 수 있다.

