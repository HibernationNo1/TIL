## MongoEngine



**mongoDB에 접근하여 document적재**

```python
from flask import Flask
from flask_mongoengine import MongoEngine

from datetime import datetime

app = Flask(__name__)

# mongodb설정값 적용
app.config['MONGODB_DB'] = 'database_name'			# 연결된 device에 있는 특정 DB에 접근
app.config['MONGODB_HOST'] = '127.0.0.1'			# HOST와 PORT로 연결하고자 하는 device결정
app.config['MONGODB_PORT'] = 27014
app.config['MONGODB_USERNAME'] = 'username'			# mongodb의 특정 collection에 들어갈 
app.config['MONGODB_PASSWORD'] = 'passward1234'		


# mongoDB와 flask 연동
db = MongoEngine(app)

# collection에 넣을 내용 정의
class ImageData(db.Document):		# MongoEngine의 instance 상속
    # 여러 field에 대한 복합index생성
    # 필드의 정렬 방향   1: 오름차순, -1: 내림차순
    # query 속도 향상
    meta = {
        'indexes': [[("userid", 1), ("pcode", 1), ("reg_datetime", 1)]]
    }

	# field 정의
    userid = db.StringField(max_length=50, required=True, comment='광고주아이디')
    pcode = db.StringField(max_length=100, required=True, comment='상품코드')
    image_path = db.StringField(max_length=1000, required=True, comment='이미지경로')
    reg_datetime = db.DateTimeField(default=datetime.utcnow, comment='등록일시')        # document생성시 시간
    

if __name__ == "__main__":
    # 정의할 field를 parameter로 전달한다.
    # 이 parameter가 column이 된다
    image_data = ImageData(userid=userid, pcode=pcode, image_path=image_path)
    
    # mongodb에 접근하여 image_data에 구성된 document를 적재
    result = image_data.save()		
```

- ImageData의 document형식

  ```
  {
      "_id": ObjectId("someUniqueIDGeneratedByMongoDB"),
      "userid": "사용자제공값",
      "pcode": "사용자제공값",
      "image_path": "사용자제공값",
      "reg_datetime": ISODate("생성시간")
  }
  ```






### db = MongoEngine()

#### db.connection

##### list_collection_names()

**collection list확보**

```python
from flask import Flask
from flask_mongoengine import MongoEngine
# from config.config import MongoConfig

app = Flask(__name__)

db = MongoEngine(app)

# mongodb설정값 적용
app.config['MONGODB_DB'] = 'database_name'			# 연결된 device에 있는 특정 DB에 접근
app.config['MONGODB_HOST'] = '127.0.0.1'			# HOST와 PORT로 연결하고자 하는 device결정
app.config['MONGODB_PORT'] = 27014
app.config['MONGODB_USERNAME'] = 'username'			# mongodb의 특정 collection에 들어갈 
app.config['MONGODB_PASSWORD'] = 'passward1234'		

def get_all_collections():
    connection = db.connection
    return connection[app.config['MONGODB_DB']].list_collection_names()


if __name__ == "__main__":
    with app.app_context():  # Set up an application context
        print(get_all_collections())
```

- error

  ```
  This typically means that you attempted to use functionality that needed
  to interface with the current application object in some way. To solve
  this, set up an application context with app.app_context().  See the
  documentation for more information.
  ```

  위와 같은 error발생 시 

  `with app.app_context(): ` 를 추가해야 한다.





#### db.Document 상속

db.Document를 상속받아 collection에 mapping되는 model class를 정의

```python
from flask_mongoengine import MongoEngine


# mongoDB와 flask 연동
db = MongoEngine(app)


class Collection(db.Document):
    userid = db.StringField(max_length=32, required=True)
    password = db.StringField(max_length=32, required=True)
    token = db.StringField(max_length=32, required=True)
    status = db.BooleanField()
    reg_datetime = db.DateTimeField()
    
    def __str__(self):
        return f"User: {self.userid}, Token: {self.token}, Status: {self.status}, Registered: {self.reg_datetime}"
```

- `__str__`: print()를 사용해서 출력할 때 사용



##### objects

위 code기준 예제

```
query = Collection.objects(userid = userid)
```

`userid` 필드가 userid라는 변수값과 일치하는 모든 document를 query한다.









```
from flask import Flask
from flask_mongoengine import MongoEngine
# from config.config import MongoConfig

app = Flask(__name__)

db = MongoEngine(app)

# mongodb설정값 적용
app.config['MONGODB_DB'] = 'database_name'			# 연결된 device에 있는 특정 DB에 접근
app.config['MONGODB_HOST'] = '127.0.0.1'			# HOST와 PORT로 연결하고자 하는 device결정
app.config['MONGODB_PORT'] = 27014
app.config['MONGODB_USERNAME'] = 'username'			# mongodb의 특정 collection에 들어갈 
app.config['MONGODB_PASSWORD'] = 'passward1234'		

class ApiUsers(db.Document):
    userid = db.StringField(max_length=32, required=True)
    password = db.StringField(max_length=32, required=True)
    token = db.StringField(max_length=32, required=True)
    status = db.BooleanField()
    reg_datetime = db.DateTimeField()

user = ApiUsers.objects(userid=self.userid).first()
```

DB에 연결되었고

DB안에는 collection이 한 개도 생성되지 않은 경우



위 code는 ApiUsers라는 class의 collection에 

위와 같은 경우 `user` 라는 변수가 None이 반환될 수 있나?

