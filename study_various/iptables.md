#  iptables

## introduction

linux에서 방화벽을 설정하는 도구

> Ubuntu에는 default로 설치되어 있다.
>
> ```
> $ which iptables
> $ iptables -V
> ```



iptables는 Chain이라는 규칙을 연결한 table 구조로 되어 있다. 각 table은 자신만의 고유한 Chain 집합을 가지고 있다.

> 사용자가 공통태그와 관련된 규칙집합을 만들기 위해 사용자 정의 Chain을 생성할 수 있다.



#### table 

iptables 는 filter, nat, mangle, raw, security와 같은 5개의 table이 있다.

- `filter` : iptables의 기본 테이블로 패킷 필터링 담당
- `nat` : Network Address Translation, IP 주소 변환
- `mangle` : 패킷 데이터를 변경하는 특수 규칙을 적용하는 테이블, 성능향상을 위한 TOS(Type of Service) 설정
- `raw` : 넷필터의 연결추적 하위시스템과 독립적으로 동작해야 하는 규칙을 설정하는 테이블
- `security` : 리눅스 보안 모듈인 SELinux에 의해 사용되는 MAC(Mandatory Access Control) 네트워크 관련 규칙 적용



#### Chain

일치하는 패킷의 규칙을 연결하는 단위

- INPUT : 시스템 외부에서 내부로 들어오는 체인
- OUTPUT : 시스템 내부에서 외부로 나가는 체인
- FORWARD : 시스템을 통과하는 체인



### Command



##### initialize

- 모든 chain에 설정된 모든 rule을 제거

  ```
  # iptables -F
  ```

- 기본 chain을 제외한 나머지 모든 chain에 설정된 모든 rule을 제거

  ```
  # iptables -X
  ```

  

##### check iptables

```
# iptables -L
```

- `iptables -L -v` : 상세 조회
- `iptables -L -n` : port number로 표시하여 조회



##### check rule

```
# iptables -S
```

- `iptables -S -v` : 상세 조회



### port forwarding

