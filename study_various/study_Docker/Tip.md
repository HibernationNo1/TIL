# Tip



## Shared Memory



```
$ docker build train --no-cache -t localhost:5000/exam:0.1
```

```
$ docker run --rm -it --name exam_1 localhost:5000/exam:0.1
```

- `--rm `: container가 종료될 때 container와 관련된 resource까지 제거된다.

  container를 일회성으로 실행할 때 주로 쓰인다.

- `--name` : 실행할 container의 별칭 설정



ShmSize 확인

```
$ docker inspect exam_1 | grep -i shm
```

```
"ShmSize": 67108864,
```



ShmSize 확인

```
$ docker run --rm -it --name exam_2 --shm-size=2gb localhost:5000/train:0.1
```

```
$ docker inspect exam_2 | grep -i shm
```

```
"ShmSize": 2147483648,
```



