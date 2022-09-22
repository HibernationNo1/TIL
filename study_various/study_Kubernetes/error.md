error



### node STATUS NotReady

```
$ kubectl get nodes
```

```
NAME                 STATUS     ROLES                  AGE   VERSION
master.example.com   NotReady   control-plane,master   30s   v1.22.13
```



kubelet 상태 확인

```
$ systemctl status kubelet
```

Active :`activating` 확인



kubelet 에러 로그 확인

```
$ journalctl -xeu kubelet
```





#### no networks found in /etc/cni/net.d

```
Sep 21 10:10:45 master.example.com kubelet[74043]: I0921 10:10:45.253800   74043 cni.go:239] "Unable to update cni config" err="no networks found in /etc/cni/net.d"
Sep 21 10:10:45 master.example.com kubelet[74043]: E0921 10:10:45.879933   74043 kubelet.go:2381] "Container runtime network not ready" networkReady="NetworkReady=false reason:NetworkPluginNotReady message:d>
```

와 같은 에러 발생: 네트쿼트 플러그인이 없다는 의미

`/etc/cni/net.d`에 `10-flannel.conflist` 가 있는지 확인한다. 

없다면 

```
$ vim 10-flannel.conflist
```

```
{
  "name": "cbr0",
  "plugins": [
  {
    "type": "flannel",
    "delegate": {
      "hairpinMode": true,
      "isDefaultGateway": true
      }
  },
  {
    "type": "portmap",
    "capabilities": {
      "portMappings": true
      }
  }
  ]
}
```

추가



#### "Error getting node" err="node \"{hostname}\" not found"

```
Sep 21 10:27:16 master.example.com kubelet[86015]: E0921 10:27:16.222895   86015 kubelet.go:2456] "Error getting node" err="node \"master.example.com\" not found"
```

