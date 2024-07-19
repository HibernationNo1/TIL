_name_ = 'database'


sqlalchemy = dict(
    db = dict(
        sqlite = dict(
            # sqlite 을 사용. 로컬 파일로 DB를 구성 (간단하게 하기 위해)
            url = 'sqlite:///./sql_app.db', 
            check_same_thread = False
        ),
        mysql = dict(
            # mysql 사용시 pymysql 드라이버 사용 필요
            url = "mysql+pymysql://teno:teno1234@192.168.110.18:3306/your_database_name" 
        )
    ),
    session = dict(
        autocommit = False,     # session이 DB로 변경사항을 자동으로 flush할지 결정
        autoflush = False       # session이 자동으로 커밋할지 결정
    )
)

