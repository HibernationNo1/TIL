#  Process

process란 실행중인 program이라고 할 수 있는데, 이는 실행파일(program)이 memory에 적재되어 CPU를 할당받아 실행(연산)되는 것을 의미한다.

> '실행파일(program)이 memory에 적재된다.' 는 것은 process가 운영체제로부터 memory공간을 할당받는 것을 의미한다.

CPU는 특정 program(code)이 하드 디스크(HDD)에 있는 경우는 읽을 수 없고, 오직 ram memory에 적제된 경우에만 읽을 수 있다.

- memory의 영역

  memory는 총 4가지의 역역이 있다.

  - stack

    code내에서 정의된 함수, 매개변수 등을 저장하는 영역이다.

    함수가 반환을 할 때 해당 영역도 전부 반환되기 때문에, 임시 memory영역이라고도 한다.

  - heap

    프로그래머가 code상에서 직접 공간을 할당하도록 하여, runtime중에 할당되는 동적 메모리 할당이 이루어 지는 영역이다

  - data

    code내에서 전역변수와 static변수를 저장하는 영역이다

  - code

    사용자가 짠 code를 compile하게 되면 기계어로 번역되는데, 이것을 보관하는 영역이다. 

  memory는 각 process마다 할당된다.



- CPU의 연산(process가 실행되는 과정)

  1. 특정 process가 memory공간을 할당받게되면, 해당 memory의 code영역에 기계어로 번역된 명령어들이 저장되게 된다. 

  2. CPU 내부에 있는 PC(program counter) register에는 위 명령어 중 다음번 연산에서 읽어야할 명령어의 주소값이 저장된다. 

     > 첫 연산에는 첫 번째 명령어를 읽어온다.

  3. CPU가 PC register에 저장된 주소로부터 명령어를 읽어오고 연산을 실행한다. 

  4. 다시 2번 - 3번의 반복



## Multi process

2개 이상의 process가 동시에 실행되는 것을 의미한다. 



### concurrency

동시성

CPU core가 1개일 때, 여러 process를 짧은 시간동안 번갈아 가면서 연산을 하게 되는 시분할(time sharing) 시스템으로 실행되는 것

시분할로 아주 빠르게 실행되기 때문에, 동시에 실행되는 것 같이 보이는 것이다.

#### CPU의 연산

> `process_1`, `process_2`가 동시에 진행되고 있을 때

PC register가 `process_1`의 code영역의 명령어 주소를 가지고 있다가, `process_2`의 code영역의 명령어 주소를 가지게 된다. 이 동작이 아주 빠르게 번갈아가며 이루어지게 된다.

CPU는 PC register가 가리키는 곳에 따라 process연산을 하게 된다.



#### Context

time sharing system에서는 PC register가 여러 process를 옮겨다니다 보니, 어떤 process의 어떤 명령어까지 실행했었는지에 대한 정보가 필요하게 된다.

Context는 process가 현재 어떤 상태로 어떤 명령어가 수행되고 있는지에 대한 총체적인 정보를 의미한다.

context정보들은 **PCB**(Process Control Block)에 저장한다. 

- context switch

  한 process에서 다른 process로 CPU제어권을 넘겨주는 것을 의미한다.

  이 때 이전의 process의 상태를 PCB에 저장하여 보관하고, 다른 process의 PCB로부터 정보를 읽어 보관된 상태를 복구하는 작업이 이루어진다. 



#### PCB

Process Control Block

PCB는 운영 체제가 process를 표현한 **자료구조**이다.

PCB는 각 process마다 할당된다.

PCB에는 process의 중요한 정보가 포함되어 있기 때문에, 일반 사용자가 접근하지 못하도록 보호된 memory영역 안에 저장이 된다.

> 일부 운영 체제에서 PCB는 kernel stack에 위치한다.

PCB에 저장되는 정보

- process state

  process의 state는 아래 세 가지로 구분된다.

  - running

    process가 CPU를 점유하고 명령을 수행중인 상태

  - ready

    CPU만 할당받으면 즉시 명령을 수행할 수 있는 상태

  - wait, sleep, blocked

    CPU를 할당받아도 명령을 실행할 수 없는 상태

- process number

- program counter

  해당 process가 다음에 실행할 명령어의 주소

- register값들

- memory limits

  memory의 사용 가능한 범위



### parallelism

병렬성

 CPU core가 여러개일 때, 각각의 core가 각각의 process를 연산함으로써 process가 동시에 실행되는 것이다.





### IPC

원칙적으로 process는 독립적인 주소 공간을 갖기 때문에 다른 proecess의 주소 공간을 참조할 수 없다. 

하지만 운영체제는 multi process환경에서 process간의 data를 주고받을 수 있도록 IPC(Inter Process Comunication)을 제공한다.

IPC방식

#### shared memory

공유메모리(shared memory) 방식

공유한 memory영역에 **read/wirte**를 통해 통신한다.

1. process가 공유 메모리 할당을 kernel에 요청하면 kernel은 해당 process에 memory공간을 할당해준다.

2. 공유 메모리 영역이 구축된 이후에는 모든 접근이 일반적인 memory 접근으로 취급된다.

   kernel의 도움 없이도 각 process들이 해당 메모리 영역에 접근할 수 있다.

3. process들이 공유한 memory영역에 read/write통해서 통신을 수행한다.

kernel의 관여 없이 data통신을 할 수 있기 때문에 빠르다.

동시에 같은 memory에 접근하면 동기화 문제가 발생할 수 있기 때문에 구현시 동기화 과정이 필요하다.

#### message passing

메시지 전달(message passing) 방식

kernel을 통해 **send와 receive**라는 두 가지 연산을 제공받는다.

1. `process_1`이 kernel로 message를 보낸다
2. kernel이 `process_1`으로부터 받은 data를 `process_2`로 message로 보낸다

shared memory방식 보다는 속도가 느리지만 충돌을 회피할 필요가 없기 때문에 적은 양의 data를 교한하는데 유용하다.

구현하기 쉽다.







---



# Thread

Thread는 한 process내에서 실행되는 동작을 의미하며, 독립적으로 함수를 호출하여 기능을 수행하는 것이다.

> 각 process내에서도 여러 기능들이 있는데, 이 기능을 수행하는 단위를 tread라고 한다.

Multi thread란 하나의 process내에 여러개의 thread가 실행되는 것을 의미한다.

하나의 process내에서도 여러 기능이 있고, 이를 수행하기 위해 multi thread가 사용되게 되는데

이 또한 multi process의 concurrency처럼 context switching이 이루어지며 time sharing system으로 진행되는 것이다.

- 각 thread는 process의 stack memory를 제외한 나머지 memory영역을 공유할 수 있다.
- 각 thread는 독립적인 stack memory와 PC register가 필요하다.
  - thread가 독립적인 함수를 호출하기 위해서는 인자 전달, return address저장, 함수 내 지역변수 저장 등을 위한 stack memory공간을 필요로 한다.
  - process내에서도 여러개의 thread끼리 context switching이 이루어지며 작업이 진행되기 때문에 PC register에 code address가 저장되어 있어야 한다.



process는 운영체제로부터 자원들 할당받는 작업의 단위이고, tread는 process가 할당받은 자원을 이용하는 실행의 단위이다.



**하나의 process를 구성할 때(code를 설계할 때) `multi process` vs `multi tread`**

- single tread의 multi process로 사용하는 경우

  - memory의 구분이 필요한 경우 사용하면 유리하다.

  - 많은 memory공간과 CPU의 시간을 차지하지만, 안정성이 높다.

- single process의 multi thread로 사용하는 경우

  - data의 공유가 빈번하거나 자원을 효율적으로 사용해야 되는 경우 유리하다.

  - 적은 memory공간을 차지하고 CPU시간을 적게 먹지만, 안정성은 낮다.

    > 한 개의 tread가 멈출 경우 다른 tread까지 모두 멈출 수 있다.

  - tread간 같은 자원을 공유하기 때문에 동일안 자원에 동시에 접근하여 엉뚱한 값을 읽거나 수정하는 문제가 발생할 수 있다.(**동기와 문제**) 

process간의 통신(IPC)보다 thread간의 통신 비용이 적기 때문에 overhead가 적다.





# 동기화 문제

서로 다른 tread 또는 proecess가 특정 memory를 공유하여 동일안 자원에 동시에 접근하는 과정에서 

엉뚱한 값을 읽거나 수정하는 문제가 발생하는 경우를 동기화 문제라고 한다.



- **race condition**(경쟁 상황)

  특정 변수 `count`의 값을 1 올리는 `count++`의 명령을 수행하는 경우 CPU는 3개의 작은 동작(atomic poerations)를 수행한다.

  1. `count`변수의 값을 가져온다
  2. `count`변수의 값을 1 증가시킨다
  3. 변경된 `count`변수의 값을 저장한다.

  만일 여러개의 thread가 공유 메모리에 접근하여 같은 data에 대해 위와 같은 동작을 수행하는 경우 

  각각의 process/thread에 의한 atomic poerations의 순서가 겹치는 경우가 발생할 수 있다. 이런 경우 의도했던 동작이 이루어지지 않을 수 있다.

  이를 race condition 라고 한다.

- **critical section**(임계 영역)

  둘 이상의 process/thread가 동시에 공유 memory상의 동일한 자원에 접근하도록 하는 code부분을 의미한다.

  여기서 race condition가 발생하지 않기 위해서는 

  1. process/thread가 critical section내의 code에 진입할 때 진입 허기를 요청하도록 해야 한다.
  2. 진입 허가 요청(entry section)에서 진입이 허가되면, critical section부분이 끝난 후 exit section으로 퇴출을 하게 된다.
  3. 특정 process/thread가 critical section내의 code에 진입한 상태하면, 또 다른 process/thread는 critical section진입이 거부된다.
  
  위 1, 2번 동작이 이루어지는 것을 critical section내의 code가 '**atomically적으로 실행된다**고' 한다.
  
- **Deadlock**(교착상태)

  둘 이상의 process/thread가 또 다른 process/thread가 점유하고 있는 자원을 서로 기다릴 때, 무한 대기에 빠지는 상황

  > 예시
  >
  > - `resource_1`을 사용하는 `thread_1`가 있다. 이 때 `resource_1`은 이미 `thread_1`에 의해 사용되고 있기 때문에 lock이 걸려 있다.
  >
  > - `resource_2`를 사용하는 `thread_2`가 있다. 이 때 `resource_2`는 이미 `thread_2`에 의해 사용되고 있기 때문에 lock이 걸려 있다.
  >
  > 위 두 조건의 상황에서
  >
  > `thread_1`이 `resource_2`의 data를 사용할 상황이 생겨 접근하지만, lock이 걸려 있어 사용하지 못하는 상태가 되면 작업이 일시중지 상태가 되고
  >
  > `thread_2`또한 `resource_1`의 data를 사용할 상황이 생겨 접근하지만, lock이 걸려 있어 사용하지 못하는 상태가 되면
  >
  > 무한 대기에 빠지게 된다.



## mutex

1개의 process/tread만이 공유 memory에 접근할 수 있도록 하여 경쟁 상황(race condition)을 방지하는 기법이다.

공유 자원을 점유하는 process/thread가 lock을 걸면, 다른 process/thread는 unlock상태가 될 때까지 해당 자원에 접근할 수 없다.





## semaphore

S(2 이상)개의 process/thread만이 공유 memory에 접근할 수 있도록 제어하는 기법이다.

1. 정수형 변수 S(semaphore)값을 가용한 자원의 수로 초기화한다.
2. 특정 process/thread가 자원에 접근할 때는 `S--`연산을 수행
3. 접근했던 process/thread가 다시 연결을 끊으면 `S++`연산을 수행한다.
4. S값이 0인 경우 모든 자원이 사용중임을 의미하고, 이후 자원을 사용하려는 process/thread는 S값이 0보다 커질 때까지 block된다.

