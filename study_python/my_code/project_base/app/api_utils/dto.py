# 데이터 유효성 검사 및 설정 관리를 위해 pydantic 사용.
# pydantic: FastAPI와 함께 사용되어 요청 데이터의 유효성을 검사하고, 파이썬 객체로 변환
from pydantic import BaseModel, validator, Field

import hashlib

class SignupDTO(BaseModel):
    # type hints를 사용해서 유효성 검사  
    # Field 를 사용하여 변수의 메타데이터 정의
    username : str = Field(title='username', min_length=4)    
    password : str = Field(title='password')

    @validator('password')
    def hashing_password(cls, v:str):
        return hashlib.sha256(v.encode('utf-8')).hexdigest()
    
class LoginDTO(BaseModel):
    username: str = Field(title='username', min_length=4)
    password: str = Field(title='password')

    @validator('password')
    def hashing_password(cls, v:str):
        return hashlib.sha256(v.encode('utf-8')).hexdigest()

class SortItemDto(BaseModel):
    product_id: int
    sort_num: int
    ctgr:str