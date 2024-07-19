from addict import Dict
from pathlib import Path
import importlib.util
import os, os.path as osp

CONFIG_REGISTRY = dict()

CONFIGDICT_NAME = 'class_config'
BASE_KEY = '_base_'
NAME_KEY = '_name_'


def pretty_text(_cfg_dict, print_str = '', depth = 0):
    # config가 다중 dict 또는 list로 구성된 경우 들여쓰기(indent) 설정
    if depth == 0: 
        indent = ''
    else:
        indent = '    '*depth
    
    if isinstance(_cfg_dict, dict):
        if depth != 0:          
            print_str +=f"\n{indent}" + "{"     # dict 시작 표시
        for key, val in _cfg_dict.items():
            print_str += f"\n{indent}'{key}': "
            print_str = pretty_text(val, print_str, depth +1)
        if depth != 0:          
            print_str += f"\n{indent}" + "}"    # dict 끝 표시

        # print_str += f'\n{indent})'
    elif isinstance(_cfg_dict, list):
        print_str +=f"\n{indent}" + f"[\n{indent}"      # list 시작 표시
        for ele in _cfg_dict:
            print_str = pretty_text(ele, print_str, depth +1)
        print_str += f"\n{indent}" + "]"                # list 끝 표시

    elif isinstance(_cfg_dict, (int, float)):
        print_str += f'{_cfg_dict}, '
        
    elif isinstance(_cfg_dict, str):
        print_str += f'"{_cfg_dict}", '
    
    return print_str


class ConfigDict(Dict) :
    """
    Use to get sub config from main config by chain method like 'config.sub_config' 
    """

    @property
    def _class_name(self):
        return CONFIGDICT_NAME

    def __missing__(self, name):
        raise KeyError(name)

    def __getattr__(self, name):  
        """
        cfg = Config(tmp_dict)
        cfg.pretty_text
        """  
        # chain형식으로 dict의 하위 값에 접근할 수 있도록 한다.        
        if name == 'pretty_text':
            # pretty_text를 호출할 경우, config를 가독성 좋은 text로 변환하여 return한다.
            return pretty_text(self)
        else:
            try:
                # 하위 config값은 attrybute로 포함하고 있기 때문에 `__getattr__`로 가져온다.
                value = super().__getattr__(name)       
            except KeyError:
                ex = AttributeError(f"'{self.__class__.__name__}' object has no attribute '{name}'")
            except Exception as e:
                ex = e
            else:
                return value
            raise ex
    

class Config:
    """
    cfg = Config(cfg_dict)
    cfg = Config.fromfile(file_path)
    """        

    def __new__(cls, cfg_dict = None):
        # instance를 생성하는 대신 value를 return

        if cfg_dict is None:
            cfg_dict = dict()
        elif not isinstance(cfg_dict, dict):
            raise TypeError(f'cfg_dict must be a dict, but got {type(cfg_dict)}')
        
        for key in cfg_dict:
            # dict의 key로 허용하지 않는 key name
            if key in ['filename', 'text', 'pretty_text']:              
                raise KeyError(f'{key} is reserved for config file')
        return ConfigDict(cfg_dict)
    

    @staticmethod
    def fromfile(filename):
        """
        Get dict type 'config' by load python script file
        How to: 
            cfg = Config.fromfile(file_path)
        """
        if isinstance(filename, Path):
            filename = str(filename)
        cfg_dict = Config._file2dict(filename)

        return ConfigDict(cfg_dict)
    

    def _file2dict(file_name):
        file_path = osp.join(os.getcwd(), file_name)
        if not osp.isfile(file_path):
            raise OSError(f"{file_path} is not exist")
        if not file_name.endswith('.py'):
            raise OSError(f'Only py type are supported. but {file_name} is not python script file.')
        
        # 동적으로 모듈을 로드하기 위한 spec 객체 생성
        spec = importlib.util.spec_from_file_location("module.name", file_path)
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)

        file_dict = dict()
        # 하위 config file의 path를 key값으로, 해당 file의 내용을 value로 갖도록 할 dict
        base_file_dict_dict = dict()        
        attributes = module.__dict__
        for key in attributes:
            # 기본적으로 module에 포함된 magic method
            if key in ['__name__', '__doc__', '__package__', '__loader__', 
                       "__spec__", '__file__', '__cached__', '__builtins__']:                                   
                continue

            # '__init__' 과 같은 key는 존재하지 않도록 한다
            if key.startswith("__"):
                raise TypeError(f"Key name cannot start with '__'. \ncheck key name: {key} in {file_path} ")    

            
            if key == BASE_KEY:
                # 하위 config file을 포함하여 dict구성
                base_path_list = getattr(module, key, None)
                if not isinstance(base_path_list, list):
                    raise TypeError(f"Only list type are supported for {BASE_KEY} key ")

                for base_path in base_path_list:
                    # 하위 config file의 path
                    sub_file_path = osp.join(osp.dirname(file_path), base_path)    
                    base_file_dict_dict[sub_file_path] = Config._file2dict(sub_file_path) 
            elif key == NAME_KEY:
                cfg_name = getattr(module, key, None)
                if not isinstance(cfg_name, str):
                    raise TypeError(f"Only string type are supported for {NAME_KEY} key ")           
                
                
                if cfg_name in CONFIG_REGISTRY.keys():
                    # 같은 이름의 config registry는 허용하지 않음
                    raise KeyError(f"'{cfg_name}' config already exists in config registry. ")
                else:
                    # config registry에 cfg_name의 key값을 만들어놓는다.
                    CONFIG_REGISTRY[cfg_name] = None
            else:
                file_dict[key] = getattr(module, key, None)

        # file_dict가 전부 구성된 후 file_dict와 하위 config file을 marge한다.
        for sub_file_path, sub_file_dict in base_file_dict_dict.items():
            # marge하기 전에 두 dict간 동일한 key값이 있는지 확인
            base_dict_keys = set(sub_file_dict.keys())
            file_dict_keys = set(file_dict.keys())
    
            common_keys = file_dict_keys.intersection(base_dict_keys)
        
            if common_keys:     # 두 dict간 동일한 key값이 있을 경우
                raise KeyError(f"'{osp.basename(file_path)}' and"\
                               f"'{osp.basename(sub_file_path)}' have common keys: {common_keys}")
    
            file_dict = {**file_dict, **sub_file_dict}
        
        try:
            # registry에 config 추가
            CONFIG_REGISTRY[cfg_name] = file_dict
        except:
            # 모든 config파일에는 _name_ key값으로 config의 이름을 명시해야 한다.
            raise KeyError(f"{file_path} must have a '_name_' key as a string.")
        return file_dict
    



def show_cfg_registry_list(name): 
    if len(CONFIG_REGISTRY.keys()) == 0:
        print("CONFIG_REGISTRY is empty!")
        return None
    
    if name not in CONFIG_REGISTRY.keys():
        raise KeyError(f"The config `{name}` dose no exist!")
    
    for i, cfg_name in enumerate(CONFIG_REGISTRY.keys()):
        print(f"Number: {i+1}. Config name: `{cfg_name}`")

def get_config_from_registry(name):
    if len(CONFIG_REGISTRY.keys()) == 0:
        raise OSError("CONFIG_REGISTRY is empty!")
    
    if name not in CONFIG_REGISTRY.keys():
        raise KeyError(f"The config `{name}` dose no exist!")
    
    return CONFIG_REGISTRY[name]