# aiohttp, asyncio

#### asyncio

비동기 I/O를 위한 기본 프레임워크를 제공한다.

비동기 프로그래밍을 통해 I/O 작업이 완료될 때까지 기다리지 않고, 다른 작업을 동시에 처리할 수 있다.

- **Event Loop**: `asyncio`는 이벤트 루프를 중심으로 동작한다. 이벤트 루프는 비동기 함수(`coroutines`)를 스케줄링하고 실행한다.

- **Coroutines**: 비동기 함수는 `async def`로 정의되고, `await` 키워드를 사용하여 다른 비동기 함수를 호출한다.

- **Tasks**: 코루틴을 태스크로 감싸서 실행할 수 있다. 태스크는 이벤트 루프에서 실행된다.

- **Futures**: 비동기 작업의 결과를 나타내는 객체

- **Protocols and Transports**: 네트워크 통신을 위해 저수준의 API를 제공한다.



#### asyncio

`asyncio`를 기반으로 한 비동기 HTTP 클라이언트/서버 라이브러리.

이를 사용하면 비동기 HTTP 요청을 보내거나 비동기 HTTP 서버를 쉽게 구축할 수 있다.





## 비동기 request 예시

#### server

아래 4개의 파일을 생성

- `tmp_1.py`

  ```
  from flask import Flask, request, jsonify
  import time
  
  app = Flask(__name__)
  
  @app.route("/api", methods = ['POST'])
  def tmp_api():
      data = request.get_json()
      sleep_time = data['sleep_time']
      print(f"sleep {sleep_time} sec")
      time.sleep(int(sleep_time))
  
      response = {
          'status': 'success',
          'data': data
      }
      return jsonify(response)
  
  if __name__ == '__main__':
      app.run(debug = True, host = '0.0.0.0', port = 30001)
  ```

- `tmp_2.py`

  ```
  from flask import Flask, request, jsonify
  import time
  
  app = Flask(__name__)
  
  @app.route("/api", methods = ['POST'])
  def tmp_api():
      data = request.get_json()
      sleep_time = data['sleep_time']
      print(f"sleep {sleep_time} sec")
      time.sleep(int(sleep_time))
  
      response = {
          'status': 'success',
          'data': data
      }
      return jsonify(response)
  
  if __name__ == '__main__':
      app.run(debug = True, host = '0.0.0.0', port = 30002)
  ```

- `tmp_3.py`

  ```
  from flask import Flask, request, jsonify
  import time
  
  app = Flask(__name__)
  
  @app.route("/api", methods = ['POST'])
  def tmp_api():
      data = request.get_json()
      sleep_time = data['sleep_time']
      print(f"sleep {sleep_time} sec")
      time.sleep(int(sleep_time))
  
      response = {
          'status': 'success',
          'data': data
      }
      return jsonify(response)
  
  if __name__ == '__main__':
      app.run(debug = True, host = '0.0.0.0', port = 30003)
  ```

- `tmp_4.py`

  ```
  from flask import Flask, request, jsonify
  import time
  
  app = Flask(__name__)
  
  @app.route("/api", methods = ['POST'])
  def tmp_api():
      data = request.get_json()
      sleep_time = data['sleep_time']
      print(f"sleep {sleep_time} sec")
      time.sleep(int(sleep_time))
  
      response = {
          'status': 'success',
          'data': data
      }
      return jsonify(response)
  
  if __name__ == '__main__':
      app.run(debug = True, host = '0.0.0.0', port = 30004)
  ```

그리고 아래 `main.py` 를 실행하여 출력을 확인





#### request

```python
import aiohttp      # aiohttp==3.9.1
import asyncio
import json
import time


api_dict = dict(
    tmp_1 = dict(
        protocol = 'http',
        host = 'localhost',
        port = '30001',
        route = '/api',
        content_type = 'application/json',
        time_out = 50,
        data = dict(sleep_time = 1)
    ),
    tmp_2 = dict(
        protocol = 'http',
        host = 'localhost',
        port = '30002',
        route = '/api',
        content_type = 'application/json',
        time_out = 50,
        data = dict(sleep_time = 2)
    ),
    tmp_3 = dict(
        protocol = 'http',
        host = 'localhost',
        port = '30003',
        route = '/api',
        content_type = 'application/json',
        time_out = 50,
        data = dict(sleep_time = 3)
    ),
    tmp_4 = dict(
        protocol = 'http',
        host = 'localhost',
        port = '30004',
        route = '/api',
        content_type = 'application/json',
        time_out = 50,
        data = dict(sleep_time = 4)
    )
)

async def fetch(session, api_name, request_info):
    address = f"{request_info['protocol']}://{request_info['host']}:{request_info['port']}{request_info['route']}"
    timeout = aiohttp.ClientTimeout(total=request_info['time_out'])
    headers = {'Content-Type': request_info['content_type']}
    async with session.post(address, data=json.dumps(request_info['data']), headers=headers, timeout=timeout) as response:
        try:
            response_status = response.status
            response_text = await response.json()       # response.text()가 완료될때까지 wait
            return api_name, response_status, response_text
        except Exception as e:
            message = f"{e}"
            # 예외 상황에서도 return 개수는 일정하게 유지
            # 비동기 작업이 끝난 후 return값에 대한 coroutine한 data를 형성하기 위함.
            return api_name, message, None

async def main():
    start_time = time.time()
    # 비동기 http session을 생성
    async with aiohttp.ClientSession() as session:
        tasks = []
        for api_name, request_info in api_dict.items():
            # event loop에서 비동기 함수를 실행하기 위해 ensure_future 사용
            # ensure_future의 return은 완료되지 않은 상태의 객체(Future 객체), 비동기 작업이 완료되면 온전히 완료되어 반환된다.
            task = asyncio.ensure_future(fetch(session, api_name, request_info))
            tasks.append(task)
        # tasks: coroutine data

        # coroutine 한 Future 객체를 병렬로 실행
        # return_exceptions: gather 동작 중 예외가 발생하더라도 예외를 발생시키지 않고, 대신 예외 객체를 결과 리스트에 포함
        # await: gather가 전부 완료될때까지 대기
        responses = await asyncio.gather(*tasks, return_exceptions=True)
        for response in responses:
            if isinstance(response, Exception):
                print(f"Error response: {response}")
            else:
                print(f"response: {response}")
    end_time = time.time()
    return end_time - start_time



loop = asyncio.get_event_loop()
result = loop.run_until_complete(main())
print(f"총 걸린 시간: {result:.3f} sec")
```

