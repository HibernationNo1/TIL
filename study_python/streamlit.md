# streamlit

```
import streamlit as st
```



#### set_page_config

wep page의 구성요소를 결정한다.

```
st.set_page_config(page_title="Enliple AI 연구소", layout='centered')
```

- `page_title` :  page의 이름
- `layout`:  `wide` or `centered`



#### columns

page의 layout section '열' 형태로 구성한다.

그 높이는 해당 section에 포함될 내용에 의해 동적으로 구성된다.

```
col = st.columns(input)
```

`input`:  `list` 또는 `int`

- `list`: element의 개수 만큼 page를 분할, 각각의 element는 그 크기만큼의 비율로 화면을 구성한다

  element의 개수 만큼 return개수를 구성해야 한다.

  ```
  col_1, col_2, col_3 = st.columns([1.0, 0.5, 1.0])
  ```

  - 2, 1, 2 의 **넓이** 비율로 page를 구성
  - list의 길이가 3이기 때문에 return의 개수도 3개



특정 layout section에 위젯 배치

```
with col_1:
    st.title("Login Page")
```

col_1에 할당된 layout section의 title을 "Login Page" 로 결정  



- 여러 layout section구성

  ```
  _, title_col_1, _ = st.columns([1.5, 1.0, 1.0])
  with title_col_1:
      st.title("Login Page")
  _, login_col_2, _ = st.columns([1.0, 0.5, 1.0])
  with login_col_2:
      username = st.text_input('ID').lower()
      password = st.text_input('Password', type='password')
      _, _, button_col = st.columns([1.5, 1.5, 1.0])
      with button_col:
          if st.button("Login"):
  ```

  - `login_col_2`는 `login_col_1`의 아래에 위치하게 되며, 서로 겹치지 않는다.

    또한 각 layout의 높이는 그 section에 담고 있는 크기에 의해 동적으로 결정되기 때문에 `st.columns`을 많이 생성하면 빽빽하게 위치하게 된다.

  - `button_col`은 `login_col_2`의 section안에 위치한다.







#### widget

- `st.title("string")`

- `st.header("string")`

- `button_check = st.button("string")`

  해당 button이 눌린 경우 `True`반환. 그 외 `False`반환

- `st.spinner("string")`

  Streamlit 앱에서 잠시 시간이 걸리는 작업을 수행하는 동안 사용자에게 피드백을 제공하기 위한 시각적 요소

  ```
  with st.spinner('Wait for it...'):
  	시간이 걸리는 작업 수행
  ```





