# elasticsearch_query



## Query(요청)

Query의 동작은 `GET`, `POST`, `PUT`, `DELETE`가 있다.

- 기본 구조

  ```
  GET index_name/_search
  {
    "_source": "field_name", 
    "query": {
      "query_name": {
        "field_name": "word_for_searching"
      }
    }
  }
  ```

  - `index_name`: name of index
  - `query_name`
  - `field_name`

Query는 크게 **leaf query**, **compound query**로 나뉘며, leaf query는 다시 **Full Text Query**와 **Term level Query**로 나뉜다.



- **leaf query**: 특정 field에서 용어를 찾는 query
  - **Full Text Query** : 포함 검색이 목적이며, 텍스트가 많은 필드에서 특정 용어를 검색할 때 사용
    - **Match Query** : 전체 text중에서 특정 용어나, 조합 용어를 검색할 때 사용된다.
      - **Match Query**: 1개의 단어를 하나의 검색어로 검색할 때 사용된다.
      - **Match Phrase Query** : 2개 이상의 단어를 하나의 검색어로 검색할 때 사용된다.
      - **Multi-match Query**: 여러 field에서 검색을 할 때 사용된다.
    - **Intervals Query** : 일치하는 용어의 순서와 근접성 등 여러 사항을 세밀하게 제어해서 검색
  - **Term level Query** : 정확한 검색이 목적이다.
    - **Term Query** : 1개의 단어를 하나의 검색어로 검색할 때 사용된다.
    - **Terms Query** : 2개 이상의 단어를 하나의 검색어로 검색할 때 사용된다.
- **compound query**: 여러 leaf query를 조합해 사용되는 query
  - **bool query** : leaf query를 조합할 때 명시하는 query명

> 그 외에는 추후 추가...



### leaf query

주어진 fields에 대해 값을 검색 시 하나의 poeration만 허용한다.  (n field + 1 operation)



#### Full Text Query

포함 검색이 목적이며, 텍스트가 많은 필드에서 특정 용어를 검색할 때 사용한다.

Full Text Query를 사용할 field는 mapping단계에서 type을 구성할 때 text type이 포함되어 구성해야 한다.

> field가 text type으로 mapping된 경우 모든 data는 token화되어 저장된다.
>
> "tmp Poo BAR" 라는 data를 저장했다면, ['tmp', 'poo', 'bar']로 3개의 토큰과 소문자로 저장된다.

##### Match

전체 text중에서 특정 용어나, 조합 용어를 검색할 때 사용된다.

'one two'의 경우 전문 검색을 사용하면 분석기에 의해 ['one', 'two']로 토큰화되고 'one'이나 'two'가 있는 경우 매칭된다. 

분석기에 의해 토큰화 될 때 대소문자는 전부 소문자로 변환되어 토큰화 되기 때문에, 검색 시 대소문자를 구분하지 않고 검색한다.



- **match**

  1개의 단어를 하나의 검색어로 검색할 때 사용된다.

  ```
  GET index_name/_search
  {
    "_source": "field_name", # field_name이라는 필드만 보여줌
    "query": {
      "match": {
        "field_name": "tmp"
      }
    }
  }
  ```

  - 2개 이상의 단어를 검색할 때

    ```
    GET index_name/_search
    {
      "_source": "field_name", 
      "query": {
        "match": {
          "field_name": "tmp bar"
        }
      }
    }
    ```

    위와 같은 경우, `tmp` 와`bar`사이의 공백은 OR로 연산되기 때문에 `tmp baz` 나 `baz bar` 와 같이 두 단어 중 하나만 포함된 data가 매칭된다.

    만일 두 단어 모두 포함하는 data를 찾고 싶다면 operator를 사용하여 공백을 "and"로 명시해주어야 한다.

    ```
    GET index_name/_search
    {
      "_source": "field_name", 
      "query": {
        "match": {
          "field_name": "tmp bar",
          "operator": "and"
        }
      }
    }
    ```

- **match_phrase**

  2개 이상의 단어를 하나의 검색어로 검색할 때 사용된다.

  ```
  GET index_name/_search
  {
    "_source": "field_name", 
    "query": {
      "match_phrase": {
        "field_name": "tmp bar"
      }
    }
  }
  ```

  위에서 operator를 사용해 검색하는것과는 다르게, 두 단어`tmp bar`를 하나의 단어로 인식되기 때문에 `tmp bar`가 포함된 data가 매칭된다.

- **multi_match**: 

  여러 field에서 검색을 할 때 사용된다.

  ```
  GET index_name/_search
  {
    "_source": ["field_name_1", "field_name_2", "field_name_3"],
    "query": {
      "multi_match": {
        "query": "tmp"
        "fields": [
        	"field_name_1", 
        	"field_name_2", 
        	"field_name_3", 
        ]		
      }
    }
  }
  ```

  

  

##### Intervals

일치하는 용어의 순서와 근접성 등 여러 사항을 세밀하게 제어해서 검색

query안에 query를 정의해서 제어한다.

```
GET index_name/_search
{
  "query": {
    "intervals": {
      "field_name": {
        "matching_rule" {
          ...
        }
      }
    }
  }
}
```



- `matching rule`: intervals를 정의할 때 구성하는 규칙(rule)

  - `all_of`: 하위의 모든 rule이 충족되어야 한다.

  - `any_of` : 하위의 모든 rule중 하나라도 충족되어야 한다.

  - `filter`

  - `match` : full text query의 match query동작을 수행한다.

    > `matching rule`에서는 term query를 지원하지 않는다.

  - `prefix`

  - `wildcard`

  - `fuzzy`

  해당 rule의 하위에는 아래와 같은 option이 올 수 있다.

  - `ordered`: 같은 level 또는 하위의 rule이나 token이 순서대로 조건에 부합하는지를 결정한다. True인 경우 순서가 중요하다 판단된다.

  - `max_gaps`: 검색어 token간에 허용되는 최대 누락 개수를 지정한다.

    예를 들어 "tmp poo bar baz" 라는 text는 4개의 토큰으로 이루어지고,  `max_gaps = 1` 인 경우 "tmp poo baz"나 "bar baz poo"는 매칭되지만 "poo bar"는 매칭되지 않는다.

  - `query` : 검색하고자 하는 token을 명시한다.(검색어)

  - `intervals`: 하위에  `matching rule`를 구성할 수 있다. 이를 통해 여러 rule을 다양하게 지정할 수 있다.

예시

```
POST girl_group/_search
{
  "query": {
    "intervals" : {					# intervals query선언
      "my_girl_group" : {			# field 명
        "all_of" : {				# 하위 모든 rule이 중족되어야 함
          "ordered" : true,			# 하위 모든 rule이 순서대로 충족되어야 함
          "intervals" : [			# intervals query선언
            {
              "match" : {							# match검색 query
                "query" : "my favorite girl group",	# 검색할 token 4개 지정
                "max_gaps" : 0,						# 누락을 허용하지 않음
                "ordered" : true					# 위 token 4개의 순서가 맞아야함
              }
            },
            {
              "any_of" : {									# 하위 rule이 최소 1개는 충족되어야 함
                "intervals" : [								# intervals query선언
                  { "match" : { "query" : "black pink" } },	# 검색할 2개의 token 지정 후 match로 검색
                  { "match" : { "query" : "red velvet" } }	# 검색할 2개의 token 지정 후 match로 검색
                ]
              }
            }
          ]
        }
      }
    }
  }
}
```





#### Term level Query

정확한 검색을 목적으로 하며, 분석기를 거치지 않기 때문에 대소문자를 구분하여 검색해야 한다.

> 검색하고자 하는 field가 text type으로 mapping되어있다면 대문자가 포함된 data를 검색하더라도 매칭이 되지 않을 것이다.
>
> 하지만 field가 keyword type으로 mapping되어 있다면 대문자도 검색하면 매칭된다.
>
> 때문에 index구성 시 mapping과정에서 추후 검색 시 term을 쓸지, match를 쓸지 결정하고 type을 결정해야 한다.
>
> 아니면 text와 keyword type을 모두 갖는 multi field로 지정하는 것도 방법이다. 

주로 keyword type에서 특정 단어를 검색하는데 사용한다.

##### Term



- **term**

  ```
  GET index_name/_search
  {
    "_source": "file_name_text_type",
    "query": {
      "term": {
        "file_name_text_type": "Tmp Bar"
      }
    }
  }
  ```

  - `file_name_text_type`라는 field가 text type으로 mapping되어있다면 위 검색에서 아무것도 매칭되지 않는다.

    검색하려는 문구는 `Tmp Bar` 지만, text type으로 mapping된 `file_name_text_type`라는 field는 해당 문구를 ['tmp', 'bar'] 로 토큰화하여 저장했기 때문이다.

  - `file_name_text_type`라는 field가 ketword type으로 mapping되어있다면 정확히 "Tmp Bar" 라는 문구의 data를 매칭한다.

- **terms query**

  2개 이상의 검색어로 검색을 수행한다.

  ```
  GET index_name/_search
  {
    "_source": "file_name_text_type",
    "query": {
      "term": {
        "file_name_text_type": ["Tmp", "Bar"]
      }
    }
  }
  ```

  "tmp"라는 data가 매칭되거나, "bar"라는 data가 매칭될것으로 기대된다.

  





### compound query

#### bool

여러 query를 조합하기 위해 상위에 bool을 사용하고, 그 안에 option query들을 넣는다. 

options

- `must` : 하위로 지정한 모든 query 결과가 True인 경우 매칭 document로 간주한다.

- `must_not` : 하위로 지정한 모든 query결과가 False인 경우 매일 document로 간주한다.

- `should`: 하위로 지정한 query중 True인 비율이 높은 경우 relevance score가 높다고 판단하여 검색 순위를 높힌다.

- `filter` : 하위로 지정한 모든 query 결과가 True인 경우 매칭 document로 간주한다. 

  > 단, filter는 relevance score 계산에 포함되지 않는 filter type context이다.
  >
  > relevance score를 계산하지 않기 때문에 `must` 보다 검색 속도가 빠르고 캐싱이 가능합니다.



예시 1  `must`, `filter`

```
GET index_name/_search
{
  "query": {
    "bool": {
      "must": [
        {
          "match": {
            "field_name_1.sub_field":"tmp"
          }  
        }
      ]
      "filter": [
        {
          "range": {
            "field_name_2": {
              "lte":15
          }
        }
      ]
    }
  }
}
```

- `must`: match는 `field_name_1`이라는 field에서 `sub_field`라는 하위 field를 대상으로 검색하며, 값이 "tmp"인 document를 매칭한다

  > 

- `filter`: `field_name_2`라는 filed에서 값이 15이하는 document를 매칭한다.

  > field_name_2의 type은 integer으로 mapping되어있음을 알 수 있다.



예시 2:TODO



## 응답

```
{
    "took" : 		# Query를 실행하는데 걸린 시간
    ,"timed_out" : 	# Query 시간이 초과했는 지 True, False로 나타낸다
    ,"_shards" : {
        "total" : 				# Query를 요청한 전체 shard 개수
        ,"successful" : 		# Query에 성공적으로 응답한 shard 개수
        ,"failed" : 			# Query에 실패한 shard 개수
    }
    ,"hits" : {
        "total" : 		# Query에 매칭된 문서의 전체 개수
        ,"max_score" : 	# Query에 일치하는 문서의 스코어 값중 가장 높은 값이다
        ,"hits" : 		# Query 결과를 표시
    }
}
```

