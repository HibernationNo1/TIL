{:toc}



# PypI

pip install로 나만의 package를 load할 수 있다.



**order**

**directory map**

```
package(dir)	┬	custom_package(dir)		┬	__init__.py
				└	setup.py				...
```

> - `custom_package(dir)` : pypi에 upload할 package
> - `setup.py` : custom package를 upload할 때 사용할 python file
> - `__init__.py` : custom package upload를 위해 package 의 각 요소(class)를 포함시키는 python file



1. install `wheel`, `twine`

   ```
   $ pip install wheel && pip install twine
   ```

2. set setup.py

3. build package `$ python setup.py bdist_wheel`

4. upload package 



## setup.py

```python
import os
from setuptools import setup, find_packages

version_file = os.path.join(os.getcwd(), 'pipeline_taeuk4958', 'version.py')             # version이 명시된 file

def get_version():
    with open(version_file, 'r') as f:
        exec(compile(f.read(), version_file, 'exec'))
    return locals()['__version__']


if __name__ == '__main__':
    setup(
        name='pipeline_taeuk4958',      # package 명
        version=get_version(),
        description='package to load file from docker local in docker container during container running',
        author='taeuk4958 ',
        author_email='taeuk4958@gmail.com',
        url='https://github.com/HibernationNo1/project_4_kubeflow_pipeline.git',
        packages=find_packages(),
        include_package_data=True,
        license='Apache License 2.0',
        install_requires=['numpy'])
```



### exam_package(dir)

#### version.py

```python
__version__ = '1.0.1'       
short_version = __version__


def parse_version_info(version_str):
    version_info = []
    for x in version_str.split('.'):
        if x.isdigit():
            version_info.append(int(x))
        elif x.find('rc') != -1:
            patch_version = x.split('rc')
            version_info.append(int(patch_version[0]))
            version_info.append(f'rc{patch_version[1]}')
    return tuple(version_info)


version_info = parse_version_info(__version__)

```



#### __init__.py

```python
from .version import __version__, short_version
__all__ = ['__version__', 'short_version']
```





## build package

`setup.py` 이 있는 위치에서

```
$ python setup.py bdist_wheel
```

```
...
removing build\bdist.win-amd64\wheel
```

> 위 출력이 뜨면 성공



**directory map**

```
package(dir)	┬	custom_package(dir)		┬	__init__.py
				├	setup.py				...
				├	build(dir)				
				├ 	dist(dir)				─ custom_package-1.0.1-py3-none-any.whl
				└	custom_package.egg-info(dir)
```

> `build`, `dist`, `custom_package.egg-info `세 dir이 생성된 것을 확인
>
> `dist` 안에는 `custom_package-1.0.1-py3-none-any.whl` 가 생김





## upload package 

1. PypI 가입
   - `Username`과 `Password`는 기록
   - 가입 후 Account Email은  `UNVERIFIED` 상태이다. email인증을 해서 ` VERIFIED` 상태로 만들자



2. upload

   ```
   $ twine upload dist/custom_package-1.0.1-py3-none-any.whl
   ```

   ```
   Enter your username: 
   Enter your password: 
   ```

   > `username`, `password` 를 입력

   ```
   View at:
   https://pypi.org/project/custom_package/1.0.1/
   ```

   > upload완료

   

3. check

   ```
   $ pip install custom_package
   ```

   