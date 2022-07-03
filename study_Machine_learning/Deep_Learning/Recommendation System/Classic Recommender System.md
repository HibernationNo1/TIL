{:toc}





# Classic Recommender System

## Information Filtering

Information Filtering은 보통 service에 가입된 user의 profile을 몇 가지의 reference 특성들과 비교한다.

reference 특성을 크게 item의 특성과 user의 특성으로 나눌 수 있다.

item의 특성을 통해 recommend하는 system은 **Collaborative-based Filtering**, user의 특성을 통해  recommend하는 system은 **Contents-based Recommender System** 이 있다.



### Contents-based

user가 과거에 좋아했던 item을 파악하고, 그 item과 비슷한 item을 recommend

> 좋아함의 기준 : 평점







### Collaborative-based

비슷한 성향 또는 취향을 갖는 user집단에서, 한 명의 user가 좋아한 item을 다른 user에게 recommend한다.

> 좋아함의 기준 : 평점
>
> - 예시 : 
>   1. user A, B 가 스파이더맨 영화에 좋은 평점 부여  >> A와 B는 비슷한 취향을 가지고 있다고 판단
>   2. user A가 영화 M에도 좋은 평점 부여 
>   3. user B에게 영화 M을 recommend

Collaborative-based Filtering은 적절한 item을 추천해주기 위해 item에 대한 user의 interaction에 의존하게 된다. 







#### 기억 기반

##### 사용자 기반



##### item 기반





#### 모델 기반



### Hybrid

### Others.. 

#### Context-based Recommendation

- Context-based Recommendation System
- Local-based Recommendation System
- Real-time or Time Sensitive Recommendation System



#### Community-based Recommendation

SNS등의 뉴스피트 또는 네트워크 데이터 등을 활용







#### Knowledge-based Recommendation

특정 도메인 지식을 바탕으로 아이템의 features를 활용한 추천

- Case-based Recommendation system
- Constraint-based Recommendation system



## 연관성 분석





## 기타

### 베스트 셀러

### 질의 응답

### ...





