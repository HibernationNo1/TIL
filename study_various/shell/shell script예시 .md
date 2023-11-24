





#### `OS: linux`인 경우 특정 shell script실행

```
# `OSTYPE`: linux, windows 등의 os name을 담고 있다.
# `-f`: test연산자. 지정된 path가 일반 file이며, 존재하는 경우 return True  (os.path.isfile())
# `source`:  지정된 file(path)의 내용을 현재 shell session에서 실행

if [[ "$OSTYPE" == "linux"* ]]; then
    if [[ -f "$CODE_DIR"/start.sh ]]
        then
        source "$CODE_DIR"/start.sh
    fi
fi
```



#### `os.getcwd()`

```
# `BASH_SOURCE``: script file의 relative path
# `--`: 이후에 오는 argument가 `-`로 시작되는 경우(예: `-filename`), 해당 argument가 option으로 해석되지 않도록 한다.
# `&`: 앞선 명령어에 대해 특정 동작(예: > /dev/null)을 적용하기 위해 사용
# `> /dev/null`: command에 의한 출력이 있는 경우 그 뒤에 붙이면 출력을 숨긴다.
#    단, 추가 option을 주지 않았으므로 표준 출력만 숨긴다.
#       추가 option예시 : `2>&1`
#       I/O 스트림이 다음과 같이 번호가 매겨져 있다.
#       0 - 표준 입력 (stdin)
#       1 - 표준 출력 (stdout)
#       2 - 표준 에러 (stderr)
#       2>&1 명령은 표준 에러 (2번)의 출력을 표준 출력 (1번)으로 간주하게 하며, 
#       `> /dev/null 2>&1` 라는 명령어는 error출력까지 숨기게 한다. 

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" & > /dev/null && pwd )
```



#### 변수에 값을 할당하는 경우

- 단순 할당

  ```
  # `-z: test연산자. 주어진 문자열의 길이가 0인경우(값이 없는 경우) return True 
  
  if [[ -z "${install_dir}" ]]
  then
      install_dir="$SCRIPT_DIR"
  fi
  ```

- export할당

  ```
  # `export`: 일시적 환경 변수 설정.  login shell에 한해 적용되기 때문에 logout이나 reboot시 삭제된다. 
  
  if [[ -z "${GIT}" ]]
  then
      export GIT="git"
  fi
  ```

- 값 비교 할당

  ```
  # `-eq`: 숫자 비교 연산자. `==`와 같다.
  if [[ -z "${venv_dir}" ]] && [[ $use_venv -eq 1 ]]
  then
      venv_dir="venv"
  fi
  ```



#### script실행 시 option활용

- `bash start.sh -f` 실행 시 

  ```
  # `do....done` while문의 본문
  # `getopts "f" flag`: shell script를 실행할 때 option을 받은 경우, 해당 option명을 flag에 parsing한다.
  #       getopts는 추로 while문과 함께 쓰인다.
  # `> /dev/null 2>&1`: 표준 출력과 error 출력까지 출력하지 않는다.
  
  
  get_option=0
  while getopts "f" flag > /dev/null 2>&1
  do
      # `case - esac`: 각 case에 따라서 동작 수행
      case ${flag} in
          f) get_option=1;;      		# flag에 `f`가 담겨있는 경우: `bash webui.sh -f`으로 실행된 경우
          *) break;;                  # 그 외의 경우 `break`으로 while문 종료
      esac
  done
  
  
  ### getopts가 처리한 옵션들을 `$@`에서 제외하는 경우 사용
  # `OPTIND`: `getopts`가 사용되었을 경우, 다음에 처리될 위치 argument의 index반환
  #       `getopts`가 한 번도 실행되지 않았을 경우 1의 값을 가진다.
  #       위 `while`문으로 인해 `OPTIND`에는 2의 값이 할당된다.
  # `shift`: positional parameters를 왼쪽으로 이동시키는 명령어
  #       특정 int가 input으로 주어지면 그 만큼 왼쪽으로 이동시키며, 이동된 만큼의 data는 삭제된다.
  shift $((OPTIND - 1))
  
  ```

- `bash start.sh -f -a` 실행 시

  ```
  get_option=0
  while getopts "fa" flag > /dev/null 2>&1
  do
      # `case - esac`: 각 case에 따라서 동작 수행
      case ${flag} in
          f) get_option=1;;      		# flag에 `f`가 담겨있는 경우: `bash webui.sh -f`으로 실행된 경우
          *) break;;                  # 그 외의 경우 `break`으로 while문 종료
      esac
  done
  ```

shell실행 시 option은 입력된 순서에 따라 shell내부에서 우선순위로 사용되어야 한다.



#### 특정 문구 출력

```
# `\n`: `새로운 줄 시작`        `%s`: 뒤에 명시되는 문자열 formmat지정
#       printf로 출력 시 변수값 할당을 통해 출력하려면 `%s`사용 필요
# `\e`: escape 문자 시작 문구. 모든 escape 문자는 `\e`으로 시작
#   `[1m`   # 문자 bolding
#   `[32m`  # 문자 색 변경
#       30: black       31: red     32: green       33: yellow      34: blue    등

delimiter="################################################################"
printf "\n%s\n" "${delimiter}"
printf "\e[1m\e[32mStart shell script \n"
printf "\n%s\n" "${delimiter}"

```



#### root사용자로 실행하는지 확인

```
# `id`: unix 및 unix 계열 OS에서 사용자의 식별 정보를 출력하는 명령어
#       확인: `echo $(id)`
#       `$(id -u)`: 현재 사용자의 UID만 출력.  root사용자인 경우 0 출력

if [[ $(id -u) -eq 0 && can_run_as_root -eq 0 ]]
then
    printf "\n%s\n" "${delimiter}"
    printf "\e[1m\e[31mERROR: This script must not be launched as root, aborting...\e[0m"
    printf "\n%s\n" "${delimiter}"
    exit 1
else
    printf "\n%s\n" "${delimiter}"
    printf "Running on \e[1m\e[32m%s\e[0m user" "$(whoami)"
    printf "\n%s\n" "${delimiter}"
fi
```

`can_run_as_root`: 사전에 값이 할당된 변수



#### 32bit인지 64bit인지 확인

```
# `$(getconf LONG_BIT)`: 현재 system의 word 길이 확인(32bit or 64bit)

if [[ $(getconf LONG_BIT) = 32 ]]
then
    printf "\n%s\n" "${delimiter}"
    printf "\e[1m\e[31mERROR: Unsupported Running on a 32bit OS\e[0m"
    printf "\n%s\n" "${delimiter}"
    exit 1
fi
```



#### 현재 path상 dir에 어떤 file이 있는지 확인 (`os.listdir(os.getcwd())`)

```
# `-d`: 현재 path상 dir에 어떤 file이 있는지 확인할 때 사용

if [[ -d .git ]]
then
    printf "\n%s\n" "${delimiter}"
    printf "Repo already cloned, using it as install directory"
    printf "\n%s\n" "${delimiter}"
    install_dir="${PWD}/../"
    clone_dir="${PWD##*/}"
fi


```



#### Check GPU model

```
# `lspci`: system에 연결된 hardware구성 요소의 세부 정보를 출력 (`echo $(lspci)`)
# `2>/dev/null`: error 출력만 숨긴다.
# `grep`
#       `-E`: grep사용시 추가할 수 있는 option으로, 복잡한 pattern을 찾을때 사용(여러 연산자를 활용)
#       `-q`: 특정 값이 포함되면 0 반환.  때문에 특정 값이 포함되는 경우 True를 return으로 받고 싶다면 `!`과 함께 사용해야한다.
# 할당되는 값: 01:00.0 VGA compatible controller: NVIDIA Corporation Device 2487 (rev a1)

gpu_info=$(lspci 2>/dev/null | grep -E "VGA|Display")

# 활용
if ! echo "$gpu_info" | grep -q "NVIDIA";
then
    export TORCH_COMMAND="pip install torch==2.0.1+rocm5.4.2 torchvision==0.15.2+rocm5.4.2 --index-url https://download.pytorch.org/whl/rocm5.4.2"

fi
```



#### 사용하고자 하는 command가 모두 정상적으로 사용 가능한지 확인

- 기본형

  ```
  # `GIT`과 `python_cmd`를 순차적으로 preq에 할당
  
  for preq in "${GIT}" "${python_cmd}"
  do
      # `hash 명령어`: 주어진 command가 사용 가능한지 확인
      if ! hash "${preq}" &>/dev/null     # `command not found`가 뜨는 경우 True
      then
          printf "\n%s\n" "${delimiter}"
          printf "\e[1m\e[31mERROR: %s is not installed, aborting...\e[0m" "${preq}"
          printf "\n%s\n" "${delimiter}"
          exit 1
      fi
  done
  ```

- array사용

  ```
  # 배열 변수를 선언
  command_list=("${GIT}" "${python_cmd}")
  
  for preq in "${command_list[@]}"
  do
      # `hash 명령어`: 주어진 command가 사용 가능한지 확인
      if ! hash "${preq}" &>/dev/null     # `command not found`가 뜨는 경우 True
      then
          printf "\n%s\n" "${delimiter}"
          printf "\e[1m\e[31mERROR: %s is not installed, aborting...\e[0m" "${preq}"
          printf "\n%s\n" "${delimiter}"
          exit 1
      fi
  done
  ```

  



#### 특정 path로 이동

```
### install DIR로 이동. 실패시 error출력

cd "${install_dir}"/ || { printf "\e[1m\e[31mERROR: Can't cd to %s/, aborting...\e[0m" "${install_dir}"; exit 1; }
```



#### git clone

```
### git clone이 이미 되어있다면 clone dir로 이동, 아니라면 git clone실행

if [[ -d "${clone_dir}" ]]
then
    cd "${clone_dir}"/ || { printf "\e[1m\e[31mERROR: Can't cd to %s/%s/, aborting...\e[0m" "${install_dir}" "${clone_dir}"; exit 1; }
else
    printf "\n%s\n" "${delimiter}"
    printf "Clone stable-diffusion-webui"
    printf "\n%s\n" "${delimiter}"
    "${GIT}" clone https://github.com/AUTOMATIC1111/stable-diffusion-webui.git "${clone_dir}"
    cd "${clone_dir}"/ || { printf "\e[1m\e[31mERROR: Can't cd to %s/%s/, aborting...\e[0m" "${install_dir}" "${clone_dir}"; exit 1; }
fi
```



#### python script실행

- `python3 start.py pwd_dir --all --name taeuk`이라는 명령어가 실행되도록 하는 shell script

  ```
  if [[ -z "${python_cmd}" ]]
  then
      python_cmd="python3"
  fi
  
  if [[ -z "${PYTHON_SCRIPT}" ]]
  then
      PYTHON_SCRIPT="start.py"
  fi
  
  # `$@`: shell script에서 받은 모든 arguments
  # bebui.sh arg1 arg2 arg3와 같은 스크립트를 실행하면, bebui.sh 내에서 `$@`는 `arg1 arg2 arg3`라는 값을 가지게 된다.
  
  printf "\n%s\n" "${delimiter}"
  printf "start %s..." "${PYTHON_SCRIPT}"
  printf "\n%s\n" "${delimiter}"
  "${python_cmd}" -u "${PYTHON_SCRIPT}" "$@"
  ```

  ```
  $ bash start.sh pwd_dir --all --name teno
  ```

- `python3 start.py pwd_dir -f -a --all --name taeuk` 이라는 명령어가 실행되도록 하는 shell script

  > 조건
  >
  > - `tmp`에 1이라는 값 할당, `boo`에 2라는 값 할당
  > - `python3 start.py pwd_dir --all --name taeuk` 을 실행

  ```
  #!/bin/bash
  
  delimiter="============================================"
  tmp=0
  boo=0
  
  # getopts를 사용하여 여러 옵션을 처리
  while getopts "fa" flag
  do
      case ${flag} in
          f) tmp=1;;      					# `-f` 옵션을 받았을 때
          a) boo=2;;                        	# `-a` 옵션을 받았을 때
          *) break;;                  		# 그 외의 경우 while문 종료
      esac
  done
  
  # getopts가 처리한 옵션들을 제외하기 위해 shift 명령어를 사용
  shift $((OPTIND - 1))
  
  if [[ -z "${python the_kor}" ]]
  then
      python_cmd="python3"
  fi
  
  if [[ -z "${PYTHON_SCRIPT}" ]]
  then
      PYTHON_SCRIPT="start.py"
  fi
  
  
  printf "\n%s\n" "${delimiter}"
  printf "start %s..." "${PYTHON_SCRIPT}"
  printf "\n%s\n" "${delimiter}"
  "${python_cmd}" -u "${PYTHON_SCRIPT}" "${args[@]}"
  ```

  