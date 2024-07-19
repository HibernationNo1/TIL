_name_ = 'security'

jwt = dict(
    tokenUrl = 'token',     # application에서 자체적으로 OAuth2 인증 서버를 구현했다면, tokenUrl은 해당 서버의 토큰 발급 endpoint를 가리켜야 한다. ('/auth/token')
    algorithm = "HS256",    # jwt의 Claims을 인코딩하고 서명하기 위해 사용할 algorithm 결정
    exp_time = 365,         # JWT 만료기간 설정
    secret_key = 'test'
)