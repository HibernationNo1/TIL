class BaseException(Exception):
    def __init__(self, status_code: int, detail: str) -> None:
        self.status_code = status_code
        self.detail = detail

    def __str__(self) -> str:
        return self.detail
    
class ImageLoadException(BaseException):
    def __init__(self, status_code: int=400, detail: str='image load failed') -> None:
        super().__init__(status_code, detail)

class ModelAPIConnectionException(BaseException):
    def __init__(self, status_code: int=500, detail: str="model api can't connect") -> None:
        super().__init__(status_code, detail)

class ValidationException(BaseException):
    def __init__(self, status_code: int=400, detail: str = "Invalid value") -> None:
        super().__init__(status_code, detail)

class RedisException(BaseException):
    def __init__(self, status_code: int=500, detail: str = "Redis Error") -> None:
        super().__init__(status_code, detail)

class JWTAuthException(BaseException):
    def __init__(self, status_code: int=500, detail: str = "WJT Error") -> None:
        super().__init__(status_code, detail)

class AuthException(BaseException):
    def __init__(self, status_code: int=404, detail: str = "Authentication failed") -> None:
        super().__init__(status_code, detail)