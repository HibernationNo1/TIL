# Selenium





## webdriver

```python
from selenium import webdriver
```



#### ChromeOptions

webdriver의 여러 option을 설정한다

```python
chrome_options = webdriver.ChromeOptions()
```

option설정은 `add_argument`를 사용한다

```
chrome_options.add_argument('--option')
```

**option**

- `start-maximized`: Chrome window 최대화
- `no-sandbox`: GUI 사용 안함
- `enable-automation`: 접근성 트리 사용
- `disable-dev-shm-usage`: Linux /dev/shm 공유 메모리 사용 안함
- `disable-gpu`: GPU 사용 안함
- `disable-infobars`: 상단에 표기되는 정보표시줄 사용 안함
- `disable-browser-side-navigation`: Navigation 기능 사용 안함



### chrome.service

#### ChromeService

```python
from selenium.webdriver.chrome.service import Service as ChromeService

service = ChromeService(executable_path=executable)
```

- `executable` : chromedriver_linux 파일의 path



### Chrome

```python
browser = webdriver.Chrome(service=service, options=chrome_options)
```

- `service` : service instance of `ChromeService`
- `options` : options instance of `ChromeOptions`



##### get

특정 url의 page를 open한다.

```python
browser.get(url)
```

- `url`: 열고자 하는 page의 url





### support

#### WebDriverWait

명시적으로 어떤 조건이 성립될때 까지 기다리는 동작을 한다.

조건이 성립되지 않을 시 timeout으로 설정된 시간만큼 최대한 기다린다.

```python
from selenium.webdriver.support.ui import WebDriverWait

wait_page = WebDriverWait(browser, timeout = 100)
```

- `browser`: instance of `webdriver.Chrome`

  해당 instance의 정보를 기반으로 web창이 생성된다.

- `timeout` : 최대 기다리는 시간



조건 할당 시 아래처럼 `until`을 사용한다.

```
wait_page.until(조건)
```







#### EC

web browser를 탐색하는 동안 특정 조건이 충족될 때까지 기다리는 동안 사용되는 조건들의 모음

```python
from selenium.webdriver.support import expected_conditions as EC
```



##### presence_of_element_located

특정 web요소가 DOM에 존재하는지 확인. 존재할 경우 True반환

```python
EC.presence_of_element_located((By.CSS_SELECTOR, 'div#section__inner-content-body-container'))
```

- input parameter는 (`common.By`, `표적 내용`)형식으로 한다.

- `By.CSS_SELECTOR`: CSS형식의 정보를 찾도록 지정

- `div#section__inner-content-body-container`:

  CSS형식 중 \<div id=''selction__inner-content-body-container">라는 요소가 있을 경우 True반환



`WebDriverWait`의 until의 parameter로 사용된다.

```python
wait_page = WebDriverWait(self.browser, 100)
wait_page.until(EC.presence_of_element_located((By.CSS_SELECTOR, 'div#section__inner-content-body-container')))
```

> ##### common.By
>
> web page의 특정 element를 찾을 때, 어떤 방식으로 찾을지 그 기준을 결정한다.
>
> ```python
> from selenium.webdriver.common.by import By
> ```
>
> - `CLASS_NAME` = 'class name'
>
> - `CSS_SELECTOR` = 'css selector'
>
> - `ID` = 'id'
>
> - `LINK_TEXT` = 'link text'
>
> - `NAME` = 'name'
>
> - `PARTIAL_LINK_TEXT` = 'partial link text'
>
> - `TAG_NAME` = 'tag name'
>
> - `XPATH` = 'xpath'





WebDriverWait의 until에 EC의 특정 조건을 할당하여 page의 특정 정보를 탐색할 때는, 해당 정보가 포함되어 있을 것으로 기대되는 web page가 요청되어 있어야 한다.

따라서 아래처럼 사용되어야 한다.

```python
from selenium import webdriver

browser = webdriver.Chrome(service=service, options=chrome_options)
browser.get(page_url)

wait_page = WebDriverWait(self.browser, 100)
wait_page.until(EC.presence_of_element_located((By.CSS_SELECTOR, 'div#section__inner-content-body-container')))
```



