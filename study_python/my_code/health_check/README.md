# Telegram - API health check



### Install telegram python sdk

```
$ pip install python-telegram-bot==13.4.1
```



### send message to bot

1. telegram어플 설치

2. 우측 상단 검색버튼 누르고 BotFather 선택

   start(시작) 

   `I can help ...`라는 봇의 답변 중 `/newbot` 이라는 문구 클릭

   `Alright, a new ...`라는 봇의 답변이 뜨면 bot과의 채팅에 사용할 채팅방 이름 입력

   `Good, now let's ...`라는 봇의 답변이 뜨면 bot의 채팅계정 이름 입력

   `Done! Congratulations on ...` 라는 봇의 답변이 뜨면 

   - `Use this token ...` 이라는 문장으로 시작하는 문단에 token이 있음 `'6818574021:AAEjZxXVUXLCST-u84Un5dYVY-XC3unpdj8'` 와 같은 형태

   - `t.me/채팅계정이름_bot` 이라는 문구 클릭 시 >> bot과의 채팅방으로 이동됨

3. chat ID얻기

   ```
   $ curl https://api.telegram.org/bot[Token 값]/getUpdates
   ```

   으로 curl요청 시 `{"ok":true,"result":[]}`이라는 응답 오면 제대로 연결된 것.

4. bot과의 채팅방에서 hello와 같이 아무 말이나 입력 후 위 curl요청 다시 준다.

   이번엔 아래와 같은 응답이 온다

   ```
   {"ok":true,"result":[{"update_id":829241423,
   "message":{"message_id":4,"from":{"id":6317154277,"is_bot":false,"first_name":"TaeUk","language_code":"ko"},"chat":{"id":6317154266,"first_name":"TaeUk","type":"private"},"date":1705567309,"text":"ih"}}]}
   ```

   위 정보 중 `6317154277` 이 부분이 chat ID

5. python에서 chat 보내기

   - version 13.4.1      `동기식`

     ```
     import telegram
     
     telegram_token = 'token값'
     chat_id = 'chat ID'
     def send_message(bot_token, chat_id, text):
         bot = telegram.Bot(token=bot_token)
         bot.sendMessage(chat_id=chat_id, text=text, timeout=100)
     
     send_message(telegram_token, chat_id, 'test')
     ```

   - verson 20.4  `비동기식`

     ```
     import telegram
     import asyncio
     import time
     
     telegram_token = 'token값'
     chat_id = 'chat ID'
     async def send_message(bot_token, chat_id, text):
         bot = telegram.Bot(token=bot_token)
         await bot.send_message(chat_id=chat_id, text=text)
     
     try:
         asyncio.run(send_message(telegram_token, chat_id, text))
     except Exception as e:
         print(f" Telegram Error: {e}")
     time.sleep(3)
     ```

     



**단톡방으로 chat보내기**

1. 단톡방 만들기

   텔레그램 app 의 좌측 `tap` > `그룹 만들기` > 그룹명 설정

   - 단톡방에 사람 추가하기

     만들어진 그룹 챗의 상단 이름 클릭 > `참가자 추가` > `링크를 통해 그룹에 초대` > 링크 복붙해서 고융

   - 단톡방에 bot추가하기

     > 단톡방 생성 후 추가해야됨. 단톡방 생성 과정에서 bot 추가 시 chat id인식 안됨
     
     bot 채팅방의 상단 이름 클릭 > `그룹 또는 채널에 추가` > 단톡방 선택 > `봇 추가 참가자로`

2. 단톡방 ID얻기

   ```
   $ curl https://api.telegram.org/bot[Token 값]/getUpdates
   ```

   위 요청을 보내면 여러 chat에 대한 정보가 뜬다.

   그 중 음수값으로 표현된 ID (예시: `-1002019712434`)

   가 바로 단톡방의 chat ID이다

