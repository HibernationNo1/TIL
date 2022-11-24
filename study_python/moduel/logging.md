# logging



#### log level

덜 심각한 순으로 나열

- DEBUG
- INFO
- WARNING
- ERROR
- critical



### basicConfig

basic한 log를 남길 때 사용

```python
import logging
logging.basicConfig(filename =, level=)
```

- `filename`: log를 남기고자 하는 `.log` form의 file path
- `level`: 어느 level의 log까지 남길 것인지 설정
  - `logging.DEBUG`
  - `logging.INFO`
  - `logging.WARNING`
  - `logging.ERROR`
  - `logging.critical`



**e.g.**

```python
import logging
logging.basicConfig(filename ="test.log", level=logging.INFO)

# log를 남길 부분에 다음과 같이 log level에 맞추어 출력해주면 해당 내용이 log file에 포함된다.
logging.debug("debug log")
logging.info("info log")
logging.warning("warning log")
logging.error("error log")
logging.critical("critical log")
```

> 출력 시 **년-월-일 시:분:초 사용자,  어느 file의 몇 line**인지 표시하며 출력한다.



### getLogger

logger 객체를 만들어 사용할 수 있다.

```
logger = logging.getLogger('name')
```

- `name` : logger에 대한 이름을 명시



`debug`, `info`, `warning`, `error`, `critical` 과 같은 method를 모두 호출하여 하사용할 수 있다.



### handlers

#### FileHandler

file로 log를 저장

```python
import logging
from logging.handlers import FileHandler
file_handler = RotatingFileHandler("exam_log.log")
file_handler.setLevel(logging.WARNING)		# 어느 level까지 logging할지 명시
```



#### RotatingFileHandler

file로 log를 저장하되, file이 정해진 size를 넘어가면 새로운 file로 생성

```python
import logging
from logging.handlers import RotatingFileHandler
file_handler = RotatingFileHandler("exam_log.log", maxBytes = 2000, backupCount = 10)
file_handler.setLevel(logging.WARNING)		
```

- `maxBytes` : 하나의 file 최대 size 
- `backupCount`: file 갯수



#### StreamHandler

```python
import logging
from logging.handlers import StreamHandler
stream_handler = StreamHandler()
```





e.g.		**`get_logger`**

```python
import logging
log_recorder: dict = {} 

def get_logger(name, log_file=None, log_level=logging.INFO, file_mode='w'):
    """Initialize and get a logger by name.

    If the logger has not been initialized, this method will initialize the
    logger by adding one or two handlers, otherwise the initialized logger will
    be directly returned. During initialization, a StreamHandler will always be
    added. If `log_file` is specified and the process rank is 0, a FileHandler
    will also be added.

    Args:
        name (str): Logger name.
        log_file (str | None): The log filename. If specified, a FileHandler
            will be added to the logger.
        log_level (int): The logger level. Note that only the process of
            rank 0 is affected, and other processes will set the level to
            "Error" thus be silent most of the time.
        file_mode (str): The file mode used in opening log file.
            Defaults to 'w'.

    Returns:
        logging.Logger: The expected logger.
    """
    logger = logging.getLogger(name)
    if name in logger_initialized:       
        return logger
    # handle hierarchical names
    # e.g., logger "a" is initialized, then logger "a.b" will skip the
    # initialization since it is a child of "a".
    for logger_name in logger_initialized:
        if name.startswith(logger_name):
            return logger

    # handle duplicate logs to the console
    # Starting in 1.8.0, PyTorch DDP attaches a StreamHandler <stderr> (NOTSET)
    # to the root logger. As logger.propagate is True by default, this root
    # level handler causes logging messages from rank>0 processes to
    # unexpectedly show up on the console, creating much unwanted clutter.
    # To fix this issue, we set the root logger's StreamHandler, if any, to log
    # at the ERROR level.
    for handler in logger.root.handlers:
        if type(handler) is logging.StreamHandler:
            handler.setLevel(logging.ERROR)

    stream_handler = logging.StreamHandler()
    handlers = [stream_handler]


    # only rank 0 will add a FileHandler
    if log_file is not None:
        # Here, the default behaviour of the official logger is 'a'. Thus, we
        # provide an interface to change the file mode to the default
        # behaviour.
        file_handler = logging.FileHandler(log_file, file_mode)
        handlers.append(file_handler)

    formatter = logging.Formatter(
        '%(asctime)s - %(name)s - %(levelname)s - %(message)s')
    for handler in handlers:
        handler.setFormatter(formatter)
        handler.setLevel(log_level)
        logger.addHandler(handler)

    logger.setLevel(log_level)

    logger_initialized[name] = True

    log_recorder[name] = logger
```