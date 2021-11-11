# PowerShell

```
. : 이 시스템에서 스크립트를 실행할 수 없으므로 C:\Users\ITC\Documents\WindowsPowerShell\profile
.ps1 파일을 로드할 수 없습니다. 자세한 내용은 about_Execution_Policies(https://go.microsoft.com/
fwlink/?LinkID=135170)를 참조하십시오.
위치 줄:1 문자:3
+ . 'C:\Users\ITC\Documents\WindowsPowerShell\profile.ps1'
+   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    + CategoryInfo          : 보안 오류: (:) [], PSSecurityException
    + FullyQualifiedErrorId : UnauthorizedAccess
```

원인 : 시스템의 설정에서 스크립트를 실행할 수 있는 권한이 부여되어있지 않은 상태라서 해당 작업 명령을 수행할 수 없어서 발생하는 오류



해결

1. Windows PowerShell 앱을 검새하여 관리자로 실행

2. 현재 권한상태를 확인

   ```
   get-ExecutionPolicy
   ```

   - Restricted : default설정값으로, 스크립트 파일을 실행할 수 없습니다.  << 위 오류가 발생한 이유

   - AllSigned : 신뢰할 수 있는(서명된) 스크립트 파일만 실행할 수 있습니다.

   - RemoteSigned : 로컬에서 본인이 생성한 스크립트와, 신뢰할 수 있는(서명된) 스크립트 파일 실행할 수 있습니다.

   - Unrestricted : 모든 스크립트 실행가능

   - ByPass : 경고/차단 없이 모든 것을 실행가능하도록함

   - Undefined : 권한을 설정하지 않겠음

3. 권한 상태를 "RemoteSigned"으로 변경합니다.

   ```
   Set-ExecutionPolicy RemoteSigned
   ```

4. 권한이 정상적으로 변경되었는지 다시 확인

   ```
    get-ExecutionPolicy
   ```

   

