from fastapi import Request
# fastAPI를 위한 middleware를 정의하기 위해 starlette 사용
#   starlette: 고성능 비동기 웹 프레임워크로, ASGI(Asynchronous Server Gateway Interface) 표준을 기반으로 한다.
from starlette.middleware.base import BaseHTTPMiddleware, RequestResponseEndpoint
from starlette.responses import JSONResponse
from logging import Logger
import uuid


class APPMiddleWare(BaseHTTPMiddleware):
    """
        application에서 request를 받으면 endpoint로 전달하기 전에 중간과정을 제어하기 위해 사용
        - 사용법: 
            app = FastAPI()
            app.add_middleware(APPMiddleWare, allowed_ips=["127.0.0.1", "192.168.1.1"], logger = logger)
    """
    def __init__(self, app, allowed_ips:list, **kwargs):
        super().__init__(app)
        # 허용하는 IP 설정
        if 'all' in allowed_ips: self.allowed_ips = 'all'           # 모든 IP 허용
        else:                    self.allowed_ips = allowed_ips
        
        
        self.response_print = False
        if isinstance(kwargs.get("logger", None), Logger):  
            # Middleware의 동작 간 logging 과정을 활성화    
            self.logger = kwargs["logger"]
            if kwargs.get("response_print", False):                  # response의 내용을 출력하고자 할 경우
                self.response_print = True
        
        
        if kwargs.get("content_type", None) is not None:        
            # 허용하는 content_type 설정
            self.allowed_content_type = kwargs['content_type']
        
            
            
    def generate_trace_id(self):
        return str(uuid.uuid4())
            
    async def dispatch(self, request:Request, call_next:RequestResponseEndpoint):
        """
            call_next: 요청을 전달할 endpoint
        """
        # 각 요청에 대한 추적을 위해 고유 id 할당
        trace_id = self.generate_trace_id()
        request.state.trace_id = trace_id
        
        
        if hasattr(self, 'logger'):  self.log_request(request, trace_id)
        
        if hasattr(self, 'allowed_content_type'):
            # content_type 필터링
            if not self.validate_request(request):
                received_content_type = request.headers.get("Content-Type")
                content={
                        "detail": "Invalid Content-Type",
                        "received": received_content_type,
                        "expected": self.allowed_content_type,
                        "trace_id": trace_id
                    }
                if hasattr(self, 'logger'): self.logger.Error(f"Middleware:: {str(content)}")
                return JSONResponse(
                    status_code=400,
                    content = content
                )

        if self.allowed_ips != "all":
            # client IP 필터링
            if not self.validate_ip(request):
                content={"detail": "Access forbidden"}
                if hasattr(self, 'logger'): self.logger.Error(f"Middleware:: {str(content)}, Client IP: {request.client.host}")
                return JSONResponse(status_code=403, content=content)
            

        response = await call_next(request)
        response.headers["X-Trace-Id"] = trace_id
    
        if self.response_print: self.log_response(response, trace_id)       # 응답 내용을 로깅

        return response
    
    def log_request(self, request: Request, trace_id: str):
        self.logger.info(f"Request: {request.method} {request.url.path} | trace_id: {trace_id}")
        
    def validate_request(self, request: Request) -> bool:
        # Content-Type이 application/json인지 확인
        return request.headers.get("Content-Type") == self.allowed_content_type
    
    def validate_ip(self, request:Request) -> bool:
        client_ip = request.client.host     # 요청을 준 client IP 
        return client_ip in self.allowed_ips
    
    def log_response(self, response: JSONResponse, trace_id: str):
        self.logger.info(f"Response: status={response.status_code}, trace_id={trace_id}, body={response.body.decode('utf-8')}")

    