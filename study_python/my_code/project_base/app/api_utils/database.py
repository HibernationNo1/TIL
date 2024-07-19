# sqlalchemy: python에서 데이터베이스와 상호작용하기 위한 ORM library
#   FastAPI와 함께 사용할경우 FastAPI에 의해 SQLAlchemy와의 통합을 원활하게 지원받으며, 데이터베이스 작업을 쉽게 수행할 수 있도록 도와준다.
#   FastAPI는 SQLAlchemy와의 통합을 위해 데이터베이스 세션 관리를 자동화하고, 요청-응답 주기 동안 세션을 생성 및 종료하는 기능을 제공한다.
#   astAPI의 종속성 주입 시스템(Depends)을 통해 SQLAlchemy 세션을 관리하여 데이터베이스 작업을 보다 효율적으로 처리할 수 있다.
from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import sessionmaker     

from sqlalchemy import Column, ForeignKey, Integer, String
from sqlalchemy.orm import relationship


from handlers.config import CONFIG_REGISTRY
db_cfg = CONFIG_REGISTRY['database'].sqlalchemy

# DB와의 연결을 생성하고 관리하는 객체 새성
# create_engine은 기본적으로 연결 풀링을 사용하기 때문에 DB 연결을 재사용하여 성능을 최적화한다.
engine = create_engine(
    db_cfg.db.sqlite.url, 
    connect_args={'check_same_thread': db_cfg.db.sqlite.check_same_thread}       # connect_args를 사용해서 추가적인 인자 전달.
    # SQLite의 check_same_thread 인자를 사용해 멀티스레딩 지원 여부 결정.
)

SessionLocal = sessionmaker(autocommit = db_cfg.session.autocommit, 
                            autoflush = db_cfg.session.autoflush, 
                            bind=engine)        # session이 DB 엔진과 연결되도록 설정

# 모든 ORM(Object-Relational Mapping) 모델 클래스가 상속해야 하는 기본 클래스를 생성
#       ORM 모델 클래스: 객체 지향 프로그래밍 언어에서 관계형 데이터베이스를 class로 정의하여 쉽게 사용할 수 있게 하는 기술 
Base = declarative_base()

def get_db():
    db = SessionLocal()
    try:
        # FastAPI는 요청이 끝난 후에 생성기를 다시 실행하여 finally 블록을 실행하기 위해 yield 사용
        yield db
    finally:
        db.close()
        
        
class User(Base):
    """
        - user 생성 방법
            user = User(username=username, password=password)
    """
    __tablename__ = 'user'
    id = Column(Integer, primary_key=True, index=True)      # column 생성 (type: Integer)
    username = Column(String, index=True)
    password = Column(String)

    # Item 테이블 간의 관계를 정의, 관리하기 위해 사용
    item = relationship('Item', back_populates='user')  # back_populates: 자신의 table명시. 이를 통해 양방향 관계임을 설정 

# 부모-자식 같에 1:N (N>=1) 의 관계 성립
class Item(Base):
    """
        - item 생성 방법
            item = Item(user_id=user_id, ctgr=ctgr, product=product, sort_num=sort_num)
    """
    __tablename__ = 'item'
    id = Column(Integer, primary_key=True, index=True)
    
    # User table의 primary key(id)와 연결, 두 table간의 관계 정의.
    user_id = Column(Integer, ForeignKey('user.id'), index=True)        # Item의 부모 class는 user table을 정의한 class임을 명시. 
    ctgr = Column(String)
    product = Column(String, index=True)
    sort_num = Column(Integer, default=9999)
    
    user = relationship('User', back_populates='item')
    