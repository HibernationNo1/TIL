# elasticsearch_mapping

index에 색인 될 document의 구조를 정의한다.

**Dynamic mapping**

Elasticsearch 는 동적 매핑을 지원하기 때문에 미리 정의하지 않아도 인덱스에 도큐먼트를 새로 추가하면 자동으로 mapping이 생성된다.

```
PUT index_name/_doc/1
{
  "field_name_1": "tmp",
  "field_name_2": "1562-12-01T00:00:00",
  "field_name_3": 125
}
```

- `field_name_1` 이라는 field에 tmp라는 text type의 data를 색인
- `field_name_2` 이라는 field에 날짜/시간 형식의 text data를 색인
- `field_name_3` 이라는 field에 125라는 int type의 data를 색인

`index_name`라는 index는 첫 번째 document를 받으며 자동으로 mapping이 생성된다.  



## Define mapping

### create

mapping을 생성하는 query의 기본 형식은 아래와 같다.

```
PUT <인덱스명>
{
  "mappings": {
    "properties": {
      "<필드명>":{
        "type": "<필드 타입>"
        … <필드 설정>
      }
      …
    }
  }
}
```



### add field

기존 mapping에 field추가

```
PUT <인덱스명>/_mapping
{
  "properties": {
    "<추가할 필드명>": { 
      "type": "<필드 타입>"
      … <필드 설정>
    }
  }
}
```





TODO