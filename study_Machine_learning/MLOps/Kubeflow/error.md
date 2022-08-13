

### Invalid input error: Unrecognized

```
kfp_server_api.exceptions.ApiException: (500)
Reason: Internal Server Error
HTTP response headers: HTTPHeaderDict({'Content-Length': '685', 'Content-Type': 'application/json', 'Date': 'Fri, 12 Aug 2022 02:14:31 GMT', 'Ngrok-Trace-Id': '9cd8d32381328fa4e531e3b07cf45748', 'Server': 'istio-envoy', 'X-Envoy-Upstream-Service-Time': '51', 'X-Powered-By': 'Express'})
HTTP response body: {"error":"Failed to create a new run.: InternalServerError: failed to generate the ExecutionSpec.: Failed to verify parameters.: Invalid input error: Unrecognized input parameter: gs_secret","code":13,"message":"Failed to create a new run.: InternalServerError: failed to generate the ExecutionSpec.: Failed to verify parameters.: Invalid input error: Unrecognized input parameter: gs_secret","details":[{"@type":"type.googleapis.com/api.Error","error_message":"Internal Server Error","error_details":"Failed to create a new run.: InternalServerError: failed to generate the ExecutionSpec.: Failed to verify parameters.: Invalid input error: Unrecognized 
input parameter: gs_secret"}]}
```

- **point** : `Invalid input error: Unrecognized `
- pipeline compile됨
- input parameters가 maching되지 않을 때 발생



### Incorrect string value

```
kfp_server_api.exceptions.ApiException: (500)
Reason: Internal Server Error
HTTP response headers: HTTPHeaderDict({'Content-Length': '817', 'Content-Type': 'application/json', 'Date': 'Fri, 12 Aug 2022 04:57:57 GMT', 'Ngrok-Trace-Id': '8a3ce8e4ecf960f3eeb77576661a134c', 'Server': 'istio-envoy', 'X-Envoy-Upstream-Service-Time': '119', 'X-Powered-By': 'Express'})
HTTP response body: {"error":"Failed to create a new run.: InternalServerError: Failed to store run hibernation-project-tc998 to table: Error 1366: Incorrect string value: '\\xEC\\x97\\xAC\\xEA\\xB8\\xB0...' for column 'WorkflowRuntimeManifest' at row 1","code":13,"message":"Failed to create a new run.: InternalServerError: Failed to store run hibernation-project-tc998 to table: Error 1366: Incorrect string value: '\\xEC\\x97\\xAC\\xEA\\xB8\\xB0...' for column 'WorkflowRuntimeManifest' at row 1","details":[{"@type":"type.googleapis.com/api.Error","error_message":"Internal Server Error","error_details":"Failed to create a new run.: InternalServerError: Failed to store run hibernation-project-tc998 to table: Error 1366: Incorrect string value: '\\xEC\\x97\\xAC\\xEA\\xB8\\xB0...' for column 'WorkflowRuntimeManifest' at row 1"}]}
```

- **point** : `Incorrect string value `
- pipeline compile됨
- component에 한글이 포함되어 있을 때(주석이라도) 발생