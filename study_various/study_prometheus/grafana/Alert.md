# Alert

사용자가 원하는 조건을 설정하여 알람을 보낼 수 있다.



## Contact points

알람을 어떻게 보낼 지 결정

`Add contack point` 선택

1. name: 알람 이름 결정
2. Integration: 알람을 어디로 보낼지 결정



### Integration

#### Telegram

Alert의 Contact points >> Integration 에서  Telegram선택 시

**BOT API Token**

1. telegram어플 설치

2. 우측 상단 검색버튼 누르고 BotFather 선택

   start(시작) 

   `I can help ...`라는 봇의 답변 중 `/newbot` 이라는 문구 클릭

   `Alright, a new ...`라는 봇의 답변이 뜨면 bot과의 채팅에 사용할 채팅방 이름 입력

   `Good, now let's ...`라는 봇의 답변이 뜨면 bot의 채팅계정 이름 입력

   `Done! Congratulations on ...` 라는 봇의 답변이 뜨면 

   - `Use this token ...` 이라는 문장으로 시작하는 문단에 token이 있음 `'6818574021:AAEjZxXVUXLCST-xxxxxxx-XC3unpdj8'` 와 같은 형태

**Chat ID**

1. chat ID얻기

   ```
   $ curl https://api.telegram.org/bot[Token 값]/getUpdates
   ```

   으로 curl요청 시 `{"ok":true,"result":[]}`이라는 응답 오면 제대로 연결된 것.

2. bot과의 채팅방에서 hello와 같이 아무 말이나 입력 후 위 curl요청 다시 준다.

   이번엔 아래와 같은 응답이 온다

   ```
   {"ok":true,"result":[{"update_id":829241423,
   "message":{"message_id":4,"from":{"id":6317154277,"is_bot":false,"first_name":"TaeUk","language_code":"ko"},"chat":{"id":6317154266,"first_name":"TaeUk","type":"private"},"date":1705567309,"text":"ih"}}]}
   ```

   위 정보 중 `6317154277` 이 부분이 chat ID

> 1. 단톡방 만들기
>
>    텔레그램 app 의 좌측 `tap` > `그룹 만들기` > 그룹명 설정
>
>    - 단톡방에 사람 추가하기
>
>      만들어진 그룹 챗의 상단 이름 클릭 > `참가자 추가` > `링크를 통해 그룹에 초대` > 링크 복붙해서 고융
>
>    - 단톡방에 bot추가하기
>
>      > 단톡방 생성 후 추가해야됨. 단톡방 생성 과정에서 bot 추가 시 chat id인식 안됨
>
>      bot 채팅방의 상단 이름 클릭 > `그룹 또는 채널에 추가` > 단톡방 선택 > `봇 추가 참가자로`
>
> 2. 단톡방 ID얻기
>
>    ```
>    $ curl https://api.telegram.org/bot[Token 값]/getUpdates
>    ```
>
>    위 요청을 보내면 여러 chat에 대한 정보가 뜬다.
>
>    그 중 음수값으로 표현된 ID (예시: `-1002019712434`)
>
>    가 바로 단톡방의 chat ID이다



## Alert rules(dashboard)

### 1. Set an alert rule name

alert rule에 대한 이름 설정



### 2. Set a query and alert condition

어떤 query의 결과에 대하여 알람을 보낼지 그 조건을 선택한다.

#### query

- prometheus가 metrics를 수집하고 있는 app의 이름

- 추적하는 시간 범위 

  `now-5m to now`: 현재 시간으로부터 5분 전 ~ 현재 시간 까지의 metrics를 추적

- `Max data points`: graph에서 data를 표현하는데 사용할 point의 개수 

- `Make this the alert condition`: 현재 이 조건으로 알람을 보낼 수 있는지 결정

  만일 `you cannot use time series data as an alert condition` 라는 문구가 뜬다면

  해당 query는 시계열 데이터이기 때문에 알람 조건으로 사용이 불가능하다는 의미.

  **Sub condition** 의 input으로 자동 사용된다.

#### expression

Main condition query의 결과를 input으로 받아 알람 조건으로 사용 가능하도록 계산법을 적용한다.

**`Make this the alert condition` 라는 파란 글을 누르면 해당 expression 또는 query기준으로 alert를 실행한다.**

##### Reduce

시계열 정보를 추적하여 얻은 값들을 하나의 값으로 치환하는 function들을 모아놓은 그룹

Main condition의 query가 시계열 데이터인 경우처럼, 알람 조건으로 사용이 불가능한 경우 보통 Reduce를 사용한다.

- `Function`: A type의 query 결과 정보 중 어떤것을 사용할지 결정

  - `Last`: A type의 query 결과 정보 중 마지막 값을 사용
  - `avg`: 추적하는 시간 범위의 값에 대한 평균값 사용.
  - `Sum`, `min`, `max`

- `Mode`:

  - `Strict`: 선택된 데이터 포인트들 중에서 숫자가 아닌 값을 포함하는 경우, 에러를 발생

    이 모드는 데이터의 정확성을 보장하고자 할 때 유용하다.

  - `Drop Non-numeric Values`: 숫자가 아닌 값들을 결과에서 제외하고, 숫자로만 구성된 값들에 대해서만 집계 함수를 적용.

  - `Replace Non-numeric Values`: 숫자가 아닌 값들을 특정 숫자로 대체한 후 집계 함수를 적용. 

    비정상적인 데이터 포인트를 기본값으로 치환하고자 할 때 사용한다.

##### Threshold

알람 조건으로 사용이 가능한 정보를 input으로 받아 알람 조건을 완성한다.

- `IS ABOVE`: 집계된 데이터 값이 특정 임계값을 초과하는 경우 알람 발송
- `IS BELOW`: 집계된 데이터 값이 특정 임계값의 미만인 경우 알람 발송
- `IS OUTSIDE RANGE`: 집계된 데이터 값이 특정 임계값 범위를 벗어나는 경우 알람 발송
- `IS WITHIN RANGE`: 집계된 데이터 값이 특정 임계값 범위 안에 있는 경우 경우 알람 발송



### 3. Alert evaluation behavior

알림 규칙을 얼마나 자주 평가할지와 관련된 설정



- `Folder`: Alert Rule이 속한 dashboard의 폴더를 지정

- `Evaluation group (interval)`: 여러 Alert Rule들을 그룹화하여 일괄적으로 평가할때 사용

  같은 평가 주기를 공유하는 Alert Rule들을 하나의 "Evaluation group"으로 묶어서 관리할때 사용

**Evaluate every**: 알림 규칙을 얼마나 자주 평가할지 결정

> `Evaluate every`를 "1m" (1분)으로 설정하면, Grafana는 매분마다 알림 규칙을 평가하여 설정된 조건이 충족되는지 확인

**for**: 설정된 조건이 지속적으로 충족되어야 하는 시간을 지정

> `for`를 "5m" (5분)으로 설정하면, 설정된 조건이 최소 5분 동안 계속해서 충족될 때만 알림이 발송



#### status

- **pending**: 설정된 알림 조건에 충족되었고, for의 설정 기간인 경우 

- **Firing**: 알림이 설정된 조건을 충족하고, 설정된 지속 시간 동안 그 조건이 계속 유지되어 실제로 알림이 발송된 상태인 경우 
- **Resolved**: Firing알림이 있었음 이후에, 해당 문제가 해결된 상태



#### configure no data and error handling

- Alert state if no data or all values are null

  app가 종료되는 등의 issue로 data수집이 안될 경우

  - **Alerting**: 알림을 발송한다.
  - **No data**: 알림을 발송하지 않고 "데이터 없음" 상태로 분류한다.
  - **OK**: 문제 없는 정상 상태로 판단한다.

- Alert state if execution error or timeout

  timeout 등의 issue로 data수집이 안될 경우

  - **Alerting**: 알림을 발송한다.
  - **No data**: 알림을 발송하지 않고 "데이터 없음" 상태로 분류한다.
  - **Error**: Error 상태로 판단하여 알림을 발송한다.



### 4. Add details for your alert rule

사용자가 특정 알림 규칙(rule)에 대한 추가적인 정보나 설명을 제공할 수 있는 option

알림 규칙의 목적, 작동 방식, 중요한 매개변수 값, 또는 알림을 받는 사람이 알아야 할 기타 중요 정보 알림 내용에 포함하여

전송한다.

- **Dashboard UID**: dashboard의 user id.  반드시 포함되어야 한다.
- **Panel ID**: panel의 id. 반드시 포함되어야 한다.



### 5. Notifications

알림을 처리하는 방법을 정의

- **Root Route**

  사용자가 custom label을 지정하지 않은 경우, 알림은 Root Route를 통해 처리

  어떤 알림이 어느 연락처 포인트로 발송될지 기본 설정을 할 수 있다.

- **Custom Labels**

  알림을 더 세분화하고 구체적인 조건에 따라 다르게 처리할 수 있다.

Label은 python code에서 metrics를 정의할 때 할당할 수 있지만, 데코레이터 사용시 label의 정의가 불가능하기 때문에 사용하지 않는다.



## Notification policies

알림(Alert)을 어떻게 처리할지 정의하는 규칙 세트

알림을 어떤 연락처 포인트(Contact Points)로 보낼지, 어떤 조건에서 알림을 발송하거나 무시할지를 결정하는 policies(정책)를 정의한다.



#### **Matching labels**

알림이 특정 조건에 맞는 레이블을 가지고 있을 때만 해당 알림 정책을 적용하도록 하는 필터

- `=`: 레이블 값이 지정된 값과 정확히 일치
- `!=`: 레이블 값이 지정된 값과 다르면 매칭
- `=~`: 레이블 값이 지정된 정규식에 매칭되면 조건을 만족
- `!~`: 레이블 값이 지정된 정규식에 매칭되지 않으면 조건을 만족

레이블이 없다면 그냥 임의로 아무 값이나 넣으면 된다.



#### Contact point

alert를 발송할 point를 결정

**contact points** 에서 point가 사전에 정의되어 있어야 선택을 할 수 있다.



#### Counting Matching Subsequent Sibling Nodes

특정 조건을 만족하는 알림이 연속해서 발생했을 때 카운트를 증가시키는 기능



#### Override Grouping

알림을 그룹화하는 방법을 재정의

기본적으로 Grafana는 알림을 발송할 때 특정 레이블을 기준으로 알림을 그룹화하지만, 이 설정을 통해 다른 기준으로 그룹화를 변경할 수 있다.



#### Override General Timings

알림 발송의 일반적인 타이밍(예: 알림 발송 주기, 알림 반복 주기 등)을 재정의할 수 있는 설정

전역 설정 대신 특정 알림 정책에 대해서만 다른 타이밍을 적용할때 사용

- **Group Wait**

  첫 번째 알림이 발생한 후, 추가적인 알림이 이 그룹에 포함되기를 기다리는 시간

  이 시간 동안 추가 알림이 발생하면 하나의 알림으로 그룹화되어 발송

- **Group Interval**

  알림 그룹을 발송한 후 다음 알림 그룹을 발송하기 전까지 기다리는 시간

  연속적으로 발생하는 알림이 그룹화되어 반복적으로 발송되는 것을 방지

- **Repeat Interval**

  동일한 알림이 반복해서 발송되는 주기

  알림 상태가 계속해서 경고 상태로 유지될 때, 해당 알림을 얼마나 자주 반복해서 발송할지 결정

  설정 안할 시 default 4시간

#### Mute Timings

특정 시간 동안 알림을 무시(Mute)하는 설정

유지 보수 등으로 인해 일시적으로 알림을 받고 싶지 않을 때 사용







