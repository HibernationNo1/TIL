from fastapi import Depends
# OAuth2PasswordBearer: FastAPI에서 OAuth2 인증을 위한 토큰 제공자 스키마를 설정하는 데 사용되는 class
# 주로 Depends와 함께 사용되어 FastAPI 엔드포인트에서 인증이 필요한 경우 이를 처리한다.
from fastapi.security import OAuth2PasswordBearer

from api_utils.database import User
from handlers.exceptions import *
from datetime import timedelta, datetime
import jwt

from handlers.config import CONFIG_REGISTRY
jwt_cfg = CONFIG_REGISTRY['security'].jwt

# token 발급 URL 설정 
oauth2_scheme = OAuth2PasswordBearer(tokenUrl=jwt_cfg.tokenUrl)     

def jwt_encode(user:User):
    if user:
        payload = {
            'exp': datetime.now() + timedelta(days=jwt_cfg.exp_time),       # JWT 만료기간 설정
            'iat': datetime.now(),                                      # JWT 발급시간 기록
            'user_id':user.id                                           # 사용자 정의 Claims
        }
        return jwt.encode(payload, jwt_cfg.secret_key, jwt_cfg.algorithm)

def jwt_decode(token:str):
    try:
        payload = jwt.decode(token, jwt_cfg.secret_key, [jwt_cfg.algorithm])
    except jwt.DecodeError as e:
        raise AuthException(431, f'Authentication failed!  Error: {e}')        
    return payload


def authenticate_token(token: str = Depends(oauth2_scheme)):
    payload = jwt_decode(token)
    if not payload:
        raise AuthException(432, f'Invalid token. Authentication failed!')
    return payload.get('user_id')