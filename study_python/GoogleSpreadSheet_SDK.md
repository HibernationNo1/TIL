# gspread

**install**

```
pip install gspread
```



## Client

```python
import gspread

key_filename = 'path_of_key.json'

client = gspread.service_account(filename=key_filename)

if isinstance(client, gspread.Client):
    google_spread_client = client
```

- `path_of_key.json`

  key 생성 방법

  1. `google cloud 콘솔` > `project선택` > `IAM 및 관리자` >  `서비스 계정`

     해당 project의 이메일을 확인할 수 있다.

  2. `key값 이메일 선택(클릭) ` > `키` > `키 추가` > `새 키 만들기`

      키 유형은 json으로 선택 

     바로 json의 비공개 키 download

  위 방법으로 생성한 key의 path를 `key_filename`에 할당한다.
  
- 특정 spreadsheet에 접근 후 write를 하려면 권한이 있어야 한다.

  권한은 spreadsheet의 주관자가 우측 상단 `공유` 버튼을 누른 후 `사용자 및 그룹 추가`에 `key값 이메일`을 입력해야 한다.

  





### list_spreadsheet_files

spreadsheet의 정보들을 반환한다.

```python
spreadsheet_list = google_spread_client.list_spreadsheet_files()

google_sheet_list = []
for sheets in spreadsheet_list:
    for sheet in sheets:
        if isinstance(sheet, dict):
            google_sheet_list.append(sheet['name'])

print(f"google_sheet_list : {google_sheet_list}")
```







### open

특정 spreadsheet에 접근한다.

```python
spreadsheet = google_spread_client.open("spreadsheet_name")
```



#### worksheets

spreadsheet의 worksheet목록을 가져온다.

```python
worksheets = spreadsheet.worksheets()
for worksheet in worksheets:
    print(worksheet.title)
```



#### worksheet

spreadsheet의 `worksheet_name`이라는 worksheet에 접근한다.

```python
worksheet = spreadsheet.worksheet("worksheet_name")

value = worksheet.cell(1, 1).value
print(value)
```



##### update_cell

특정 cell에 접근하여 값을 입력한다.

```python
worksheet.update_cell(row, column, "MyValue")
```

- `row`: 열
- `column`: 행





##### cell

특정 cell에 접근하여 값을 가져온다.

```python
value = worksheet.cell(row, column).value
print(value)
```





##### get_all_values

worksheet의 모든 row를 반환한다.

```python
all_values = worksheet.get_all_values()
for row in all_values:
    print(row)
```



