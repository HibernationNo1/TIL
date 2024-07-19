from handlers.logger import Logger

from handlers.config import Config, CONFIG_REGISTRY
cfg = Config.fromfile(f'configs/main.py')

print(CONFIG_REGISTRY.keys())