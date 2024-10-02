from prometheus_client import Histogram, Counter

PROMETHEUS_REGISTRY = dict()


PROMETHEUS_REGISTRY['Histogram'] = Histogram('function', 'Latency of run function (unit: seconds)')
PROMETHEUS_REGISTRY['latency_time'] = Histogram('latency_time', 'Latency in specific parts of code (unit: seconds)')
"""
PROMETHEUS_REGISTRY['key_name'] = Histogram('{metrics_이름}', '{metrics 설명}')
- apply to code
    request_latency = PROMETHEUS_REGISTRY['key_name']
    @request_latency.time()
- PromQL
    - 최근 하루동안의 요청 횟수
        increase({metrics_이름}_count[1d])
    - 5분간의 요청 평균 수행 시간
        rate({metrics_이름}_sum[1m]) / rate({metrics_이름}_count[1m])
"""

PROMETHEUS_REGISTRY['count'] = Counter('count', 'Count of result; save')
