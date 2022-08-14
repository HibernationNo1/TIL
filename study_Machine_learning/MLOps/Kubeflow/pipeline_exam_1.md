

`create_component_from_func` 을 사용해서 작성한 pipeline예시 code





[TOC]

# pipeline.py

```python
import re
import kfp
import kfp.dsl as dsl
import requests
import os 
import argparse
import json

from set_config import set_config_op
from record.record_dataset import record_op
from record.save_GS import save_dataset_op
from train.load_dataset import download_dataset_op

from config import (USERNAME, PASSWORD, NAMESPACE, HOST,   
                    PIPELINE_PAC, PIPELINE_DISCRIPTION , EXPERIMENT_NAME, RUN_NAME)
    
def connet_client():   
    session = requests.Session()
    response = session.get(HOST)

    headers = {
        "Content-Type": "application/x-www-form-urlencoded",
    }

    data = {"login": USERNAME, "password": PASSWORD}
    session.post(response.url, headers=headers, data=data)                              
    session_cookie = session.cookies.get_dict()["authservice_session"]  

    # client에 접속
    client = kfp.Client(
        host=f"{HOST}/pipeline",
        namespace=f"{NAMESPACE}",
        cookies=f"authservice_session={session_cookie}",
    )
    return client


def upload_pipeline(client, args):
    pipeline_path = os.path.join(os.getcwd(), PIPELINE_PAC)
    if not os.path.isfile(pipeline_path) : raise OSError(f"{pipeline_path} is not exist!")
    
    if client.get_pipeline_id(args.p_name) == None:
        print("\n Upload initial version pipeline named {args.p_name}!")
        client.upload_pipeline(pipeline_package_path= pipeline_path,
                            pipeline_name= args.p_name,
                            description= PIPELINE_DISCRIPTION)
        
        pipeline_id = client.get_pipeline_id(args.p_name)
    else: 
        pipeline_id = client.get_pipeline_id(args.p_name)
        pipelince_versions = client.list_pipeline_versions(pipeline_id = pipeline_id)
        
        versions = []
        for pipeline_index in range(pipelince_versions.total_size):
            versions.append(pipelince_versions.versions[pipeline_index].name)  
        
        if args.p_version in versions: raise TypeError(f"{args.p_version} version of {args.p_name} is exist!")
                
        print(f"\n Upload pipeline {args.p_version} version named {args.p_name}!")
        client.upload_pipeline_version(pipeline_package_path= pipeline_path,
                                    pipeline_version_name = args.p_version,
                                    pipeline_id = pipeline_id,
                                    description = PIPELINE_DISCRIPTION)      
        
        
    return pipeline_id  
    

def run_pipeline(client, experiment_id, pipeline_id, params_dict):
    exec_run = client.run_pipeline(
            experiment_id = experiment_id,
            job_name = RUN_NAME,
            pipeline_id = pipeline_id,
            params = params_dict
            )
    print("\n run pipeline")

    run_id = exec_run.id


    completed_run = client.wait_for_run_completion(run_id=run_id, timeout=600)
    print(f"status of {RUN_NAME} : {completed_run.run.status}")
        
        
def get_params(args, input_dict):
    secrets_path = os.path.join(os.getcwd(), args.client_secrets)
    if not os.path.isfile(secrets_path): raise OSError(f"{secrets_path} is not exist!")
    with open(secrets_path, "r") as f:
        client_secrets_dict = json.load(f)
        
    params_dict = {'input_mode': args.mode, 'input_dict': input_dict, 'gs_secret' : client_secrets_dict}
        
    return params_dict
   
    

def parse_args():
    parser = argparse.ArgumentParser(description="Change structure from comments to custom dataset in json file format.")    
    
    parser.add_argument("--p_name", required = True, help="name of pipeline")    
    parser.add_argument("--p_version", type = str, required = True, help="version of pipeline")    
    
    parser.add_argument('--mode', required = True, choices=['record', 'train', 'test'])
    parser.add_argument("--cfg", required = True, help="name of config file")
    
    # mode : record 
    parser.add_argument("--proportion-val", type=float, default = 0.0, help = "split proportion from train_dataset to val_dataset for valditate during training") 
    parser.add_argument('--dataset', help = 'annotations dir path')
    
    parser.add_argument('--client_secrets', default= 'client_secrets.json',
                        help = 'client_secrets file path (json format)')
    parser.add_argument('--ann_bk_name', help = 'bucket_name of annotation dataset stored in google cloud storage')
    parser.add_argument('--dataset_bk_name', help = 'bucket_name of annotation dataset stored in google cloud storage')
    parser.add_argument('--d_version', type = str, help = 'version of recorded dataset to be store in google cloud storage.')
    
    parser.add_argument('--train', action = 'store_true', help = 'if True, go training after make custom dataset' ) # TODO
    
    # mode : train
    parser.add_argument('--train_json', help= "name of train dataset file in .json format")
    parser.add_argument(
        '--validate',
        default=False,
        action="store_true",
        help='whether do evaluate the checkpoint during training')
    parser.add_argument('--val_json', help= "name of train dataset file in .json format")
    parser.add_argument(
        '--finetun',
        default=False,
        action="store_true",
        help='whether do fine tuning')
    
    parser.add_argument('--model_vers', 
                        type = str,
                        default= 0.1,
                        help= "directory name. version of model to be store in google cloud storage.")
    parser.add_argument('--d_version_t', type = str, help = 'version of recorded dataset in google cloud storage.')
    

    args = parser.parse_args()
    
    input_dict = vars(args)
    
    return args, input_dict

@dsl.pipeline(name="hibernation_project")
def project_pipeline(input_mode : str, input_dict : dict, gs_secret : dict):
    
    _set_config_op = set_config_op(input_dict)
    with dsl.Condition(input_mode == "record") : 	
        _record_op = record_op(gs_secret, _set_config_op.outputs['config'])
        _save_dataset_op = save_dataset_op(gs_secret, _set_config_op.outputs['config'], _record_op.outputs['train_dataset'], _record_op.outputs['val_dataset'])
        
    with dsl.Condition(input_mode == "train") :
        _download_dataset_op = download_dataset_op(gs_secret, _set_config_op.outputs['config'])
        
        pass
         
        
        
if __name__=="__main__":      

    args, input_dict = parse_args()    

    print("\n comile pipeline")
    kfp.compiler.Compiler().compile(
        project_pipeline,
        f"./{PIPELINE_PAC}"
        )

    print("\n connet_client")
    client = connet_client()
    
    pipeline_id = upload_pipeline(client, args)
    
    print("\n get experiment")
    info_experiment = client.get_experiment(experiment_name= EXPERIMENT_NAME, namespace= NAMESPACE)
    experiment_id = info_experiment.id
   
    
    params_dict = get_params(args, input_dict)
    run_pipeline(client, experiment_id, pipeline_id, params_dict)

```



# config.py

```yaml

import os
import json

# kubeflow dashboard
USERNAME = "user@example.com"
PASSWORD = "12341234"
NAMESPACE = "kubeflow-user-example-com"
HOST =  "http://ebbc-1-214-32-67.ngrok.io"     # "http://192.168.0.167:80"       

# docker images
SETUP_IMAGE = 'hibernation4958/record:0.2'
SETUP_COM_FILE = None                   # "set_config.component.yaml"

RECORD_IMAGE = 'hibernation4958/record:0.2'
RECORD_COM_FILE = None                  # "record.component.yaml"

SAVE_GS_IMAGE = RECORD_IMAGE            # 'hibernation4958/for_save.0.1'
SAVE_GS_COM_FILE = None                 # "save_dataset.component.yaml"

LOAD_DATA_IMAGE = "hibernation4958/0810:0.2"
LOAD_DATA_COM_FILE = None               # 


# pipeline
PIPELINE_PAC = "mmdet_project.yaml"
PIPELINE_DISCRIPTION = "test"
EXPERIMENT_NAME = "test2"
RUN_NAME = "test_run"


```



# set_config.py

```python
from genericpath import exists
from kfp.components import OutputPath, create_component_from_func
from config import SETUP_IMAGE, SETUP_COM_FILE  
        

def set_config(args: dict, config_path: OutputPath("dict"), ) :

    import os 
    import pipeline_taeuk4958
    print(f"\n pipeline_taeuk4958.__version__ : {pipeline_taeuk4958.__version__} \n")
    from pipeline_taeuk4958.configs.config import Config

    pipeline_taeuk4958_config_path ='/usr/local/lib/python3.8/site-packages/pipeline_taeuk4958/configs'
    cfg_file_path = os.path.join(pipeline_taeuk4958_config_path, args['cfg'])        
    cfg = Config.fromfile(cfg_file_path)                # cfg_file_path : must be .py format
    
    
    if args['p_name'] is not None : cfg.pipeline.pipeline_name = args['p_name']
    if args['p_version'] is not None : cfg.pipeline.pipeline_version = args['p_version']
    
    if args['mode'] == "record":
        if args['proportion_val'] is not None : cfg.options.proportion_val = args['proportion_val']
        if args['dataset'] is not None : cfg.dataset.dataset_dir = args['dataset']
        
        if args['client_secrets'] is not None : cfg.gs.client_secrets = args['client_secrets']
        if args['ann_bk_name'] is not None : cfg.gs.ann_bucket_name = args['ann_bk_name']
        if args['dataset_bk_name'] is not None : cfg.gs.recoded_dataset_bucket_name = args['dataset_bk_name']
        if args['d_version'] is not None : cfg.gs.recoded_dataset_version = args['d_version']
    
    elif args['mode'] == "train":
        if args['train_json'] is not None : cfg.dataset.train_file_name = args['train_json']
        if args['val_json'] is not None : cfg.dataset.val_file_name = args['val_json']
        if args['validate'] : cfg.train.validate = True
        if args['finetun'] : cfg.train.finetun = True
        if args['model_vers'] is not None : cfg.train.model_version = args['model_vers']
        if args['d_version_t'] is not None : cfg.dataset.dataset_version = args['d_version_t']
    
    
     
    cfg.dump(config_path)                               # save to config_path : {wiorkspace}/outputs/set_config/data
    
    
set_config_op = create_component_from_func(func = set_config,
                                        base_image = SETUP_IMAGE,
                                        output_component_file= SETUP_COM_FILE)


```





# train(dir)

## Dockerfile

```yaml
FROM python:3.8
ENV PYTHONUNBUFFERED 1

RUN git clone https://github.com/HibernationNo1/project_dataset.git
WORKDIR project_dataset/

RUN pip install dvc[gs]
RUN pip install pipeline_taeuk4958==1.1.5
RUN pip install Pillow
RUN pip install tqdm
```



## record_dataset.py

```python
from kfp.components import InputPath, OutputPath, create_component_from_func
from config import RECORD_IMAGE, RECORD_COM_FILE


def record(gs_secret : dict,
            cfg_path: InputPath("dict"),
            train_dataset_path: OutputPath("dict"),
            val_dataset_path: OutputPath("dict")):   
    """
    cfg_path : {wiorkspace}/inputs/cfg/data
    """    
    
    import json
    import subprocess
    import glob
    import os
    import time
    import numpy as np
    import PIL
    from PIL.Image import fromarray as fromarray
    from PIL.ImageDraw import Draw as Draw
    
    from pipeline_taeuk4958.utils.utils import NpEncoder
    from pipeline_taeuk4958.configs.config import load_config_in_pipeline
    
    class Record_Dataset():
        """

        """
        def __init__(self, cfg, dataset_list):
            self.cfg = cfg
            self.dataset_list = dataset_list
            
            self.train_dataset = dict(info = {}, 
                                licenses = [],
                                images = [], annotations = [], categories = [],
                                classes = None)
            self.val_dataset = dict(info = {}, 
                                licenses = [],
                                images = [], annotations = [], categories = [],
                                classes = None)
            
            self.object_names = []
            
            self.dataset_dir_path = None
            self.annnotation_dir_path = None
            
            # json_file = self.train_dataset
            # print(f"json_file['info'].keys() : {json_file['info'].keys()} \n")
            # print(f"json_file['images'][0].keys() : {json_file['images'][0].keys()} \n")
            # print(f"json_file['categories'][0].keys() : {json_file['categories'][0].keys()} \n")
            # print(f"json_file['annotations'][0].keys() : {json_file['annotations'][0].keys()} \n")
            # print(f"json_file['annotations'][0]['image_id'] : {json_file['annotations'][0]['image_id']}, {type(json_file['annotations'][0]['image_id'])}")
            
            self.data_transfer()
            

   
        def get_dataset(self):
            return self.train_dataset, self.val_dataset
  
        
        def data_transfer(self):
            labelme_json_list = self.dataset_list
            
            if self.cfg.options.proportion_val == 0:
                val_split_num = len(labelme_json_list) + 100000
            else:
                val_image_num = len(labelme_json_list) * self.cfg.options.proportion_val     
                if val_image_num == 0 :
                    val_split_num = 1
                else : val_split_num = int(len(labelme_json_list)/val_image_num)
        
            
            print(f" part_1 : info")
            self.get_info("train")
            self.get_info("val")
            
            print(f"\n part_2 : licenses")
            self.get_licenses("train")
            self.get_licenses('val')
            
            print(f"\n part_3 : images")
            self.get_images(labelme_json_list, val_split_num)
            
            print(f"\n part_4 : annotations")
            self.get_annotations(labelme_json_list, val_split_num)
            
            print(f"\n part_5 : categories")
            self.get_categories("train")   
            self.get_categories("val") 

        def get_info(self, mode) : 
            if mode == "train":
                self.train_dataset['info']['description'] = self.cfg.dataset.info.description
                self.train_dataset['info']['url']         =  self.cfg.dataset.info.url
                self.train_dataset['info']['version']     =  self.cfg.dataset.info.version
                self.train_dataset['info']['year']        =  self.cfg.dataset.info.year
                self.train_dataset['info']['contributor'] =  self.cfg.dataset.info.contributor
                self.train_dataset['info']['data_created']=  self.cfg.dataset.info.data_created
                self.train_dataset['info']['for_what']= "train"
            elif mode == "val":
                self.val_dataset['info']['description'] =  self.cfg.dataset.info.description
                self.val_dataset['info']['url']         =  self.cfg.dataset.info.url
                self.val_dataset['info']['version']     =  self.cfg.dataset.info.version
                self.val_dataset['info']['year']        =  self.cfg.dataset.info.year
                self.val_dataset['info']['contributor'] =  self.cfg.dataset.info.contributor
                self.val_dataset['info']['data_created']=  self.cfg.dataset.info.data_created
                self.val_dataset['info']['for_what']= "va;"
                

        def get_licenses(self, mode):            
            if self.cfg.dataset.info.licenses is not None:
                tmp_dict = dict(url = self.cfg.dataset.info.licenses.url,
                                id = self.cfg.dataset.info.licenses.id,
                                name = self.cfg.dataset.info.licenses.name)   
                if mode == "train":
                    self.train_dataset['licenses'].append(tmp_dict)  # original coco dataset have several license
                elif mode == "val":
                    self.val_dataset['licenses'].append(tmp_dict) 
            else: 
                pass  
        
        def get_categories(self, mode):
            for i, object_name in enumerate(self.object_names):
                tmp_categories_dict = {}
                tmp_categories_dict['supercategory'] = object_name                          # str
                tmp_categories_dict['id'] = self.object_names.index(object_name)            # int
                tmp_categories_dict['name'] = object_name                                    # str
                if mode == "train" :
                    self.train_dataset['categories'].append(tmp_categories_dict)
                elif mode == "val" :
                    self.val_dataset['categories'].append(tmp_categories_dict)

            if mode == "train" :
                self.train_dataset['classes'] = self.object_names
            elif mode == "val" :
                self.val_dataset['classes'] = self.object_names
            
            
        def get_annotations(self, labelme_json_list, val_split_num):
            id_count = 1
            for i, json_file in enumerate(labelme_json_list):
                with open(json_file, "r") as fp:
                    data = json.load(fp) 

                    image_height, image_width = data["imageHeight"], data["imageWidth"]
    
                    for shape in data['shapes']:    # shape == 1 thing object.    
                        if shape['label'] not in self.object_names:
                            if shape['label'] in self.cfg.dataset.valid_object:
                                self.object_names.append(shape['label'])
                            else: 
                                if self.cfg.options.only_val_obj: raise KeyError(f"{shape['label']} is not valid object.")   
                                else: continue


                        tmp_annotations_dict = {}
                        if shape['shape_type'] == "polygon":  
                                                    
                            contour = np.array(shape['points'])
                            tmp_segmentation = []
                            points = list(np.asarray(contour).flatten())
                            for point in points:
                                tmp_segmentation.append(round(point, 2))
                            tmp_annotations_dict['segmentation'] = [tmp_segmentation]
                            mask = self.polygons_to_mask([image_height, image_width], contour)
                            x = contour[:, 0]
                            y = contour[:, 1]
                            area = 0.5 * np.abs(np.dot(x, np.roll(y, 1)) - np.dot(y, np.roll(x, 1)))
                            tmp_annotations_dict["area"] = float(area)
                            
                            tmp_annotations_dict['iscrowd'] = 0     # choise in [0, 1]  TODO : add when using included [iscrowd == 1] dataset
                            tmp_annotations_dict['image_id'] = i+1
                            tmp_annotations_dict['bbox'] = list(map(float, self.mask2box(mask)))
                            tmp_annotations_dict['category_id'] = self.object_names.index(shape['label'])       # int, same to category_id
                            tmp_annotations_dict['id'] = id_count
                            id_count +=1
                            
                            
                        else : continue     # TODO : add when using dataset not type of segmentation

                        if i % val_split_num == 0:
                            self.val_dataset['annotations'].append(tmp_annotations_dict)
                        else:
                            self.train_dataset['annotations'].append(tmp_annotations_dict)                    


        def polygons_to_mask(self, img_shape, polygons):
            mask = np.zeros(img_shape, dtype=np.uint8)
            
            mask = fromarray(mask)
            xy = list(map(tuple, polygons))  
            Draw(mask).polygon(xy=xy, outline=1, fill=1)
            mask = np.array(mask, dtype=bool)
            return mask
        
        
        def mask2box(self, mask):
            index = np.argwhere(mask == 1)   
            
            rows = index[:, 0]
            clos = index[:, 1]       

            left_top_r = np.min(rows)  # y
            left_top_c = np.min(clos)  # x

            right_bottom_r = np.max(rows)
            right_bottom_c = np.max(clos)

            
            return [
                left_top_c,
                left_top_r,
                right_bottom_c - left_top_c,
                right_bottom_r - left_top_r,
            ]

        def get_images(self, labelme_json_list, val_split_num):
            yyyy_mm_dd_hh_mm = time.strftime('%Y-%m-%d', time.localtime(time.time())) \
                        + " "+ str(time.localtime(time.time()).tm_hour) \
                        + ":" + str(time.localtime(time.time()).tm_min)
            
            for i, json_file in enumerate(labelme_json_list):                
                tmp_images_dict = {}
                with open(json_file, "r") as fp:
                    data = json.load(fp) 
                    
                    tmp_images_dict['license'] = f"{len(self.train_dataset['licenses'])}"  # just '1' because license is only one
                    tmp_images_dict['file_name'] = data['imagePath']
                    tmp_images_dict['coco_url'] = " "                       # str
                    tmp_images_dict['height'] = data["imageHeight"]         # int
                    tmp_images_dict['width'] = data["imageWidth"]           # int
                    tmp_images_dict['date_captured'] = f"{yyyy_mm_dd_hh_mm}"     # str   
                    tmp_images_dict['flickr_url'] = " "                     # str
                    tmp_images_dict['id'] = i+1                                 # non-duplicate int value
                
                if i % val_split_num == 0:
                    self.val_dataset["images"].append(tmp_images_dict)
                else:
                    self.train_dataset["images"].append(tmp_images_dict)
    

    
    def set_client_secret():
        client_secrets_path = os.path.join(os.getcwd(), cfg.gs.client_secrets)
        
        # save client_secrets
        json.dump(gs_secret, open(client_secrets_path, "w"), indent=4)   
        remote_bucket = f"dvc remote add -d -f bikes gs://{cfg.gs.ann_bucket_name}"
        credentials = f"dvc remote modify --local bikes credentialpath '{client_secrets_path}'" 
      
        subprocess.call([remote_bucket], shell=True)
        subprocess.call([credentials], shell=True)

        subprocess.call(["dvc pull"], shell=True)           # download dataset from GS by dvc
   
                    
    
    if __name__=="__main__":                
        cfg = load_config_in_pipeline(cfg_path)
        
        
        ## download dataset from google cloud stroage bucket by dvc
        dvc_path = os.path.join(os.getcwd(), 'dataset.dvc')             # check file exist (downloaded from git repo with git clone )
        if not os.path.isfile(dvc_path): raise OSError(f"{dvc_path}")
        
        set_client_secret()
        
        data_dir = os.path.join(os.getcwd(), cfg.dataset.dataset_dir)
        dataset_list = glob.glob(f"{data_dir}/*.json")    
        if len(dataset_list)==0 : raise OSError("Failed download dataset!!")
        print(f"\n number of annotations : {len(dataset_list)} \n")
        
        
        ##  get dataset
        labelme_instance = Record_Dataset(cfg, dataset_list)
        train_dataset, val_dataset = labelme_instance.get_dataset()
        
        # save recorded dataset
        json.dump(train_dataset, open(train_dataset_path, "w"), indent=4, cls = NpEncoder)
        json.dump(val_dataset, open(val_dataset_path, "w"), indent=4, cls = NpEncoder)

  
record_op = create_component_from_func(func = record,
                                        base_image = RECORD_IMAGE,
                                        output_component_file=RECORD_COM_FILE)
```





## save_GS.py

```python
import kfp
from kfp.components import InputPath, create_component_from_func

from config import SAVE_GS_IMAGE, SAVE_GS_COM_FILE

def save_dataset(gs_secret : dict,
                 cfg_path: InputPath("dict"),
                 train_dataset_path: InputPath("dict"),
                 val_dataset_path: InputPath("dict")):
    
    import json
    import os
    from pipeline_taeuk4958.utils.utils import NpEncoder
    from pipeline_taeuk4958.configs.config import load_config_in_pipeline
    from pipeline_taeuk4958.cloud.gs import set_gs_credentials
    
    from google.cloud import storage
        

    def load_recorded_dataset(cfg):
        with open(train_dataset_path, "r", encoding='utf-8') as f:
            train_dataset = json.load(f)
        train_dataset_to_upload = os.path.join(os.getcwd(), cfg.dataset.train_file_name)
        json.dump(train_dataset, open(train_dataset_to_upload, "w"), indent = 4, cls = NpEncoder)
        train_dataset_in_storage_path = f'{cfg.gs.recoded_dataset_version}/{cfg.dataset.train_file_name}' 
        
        with open(val_dataset_path, "r", encoding='utf-8') as f:
            val_dataset = json.load(f)
        val_dataset_to_upload = os.path.join(os.getcwd(), cfg.dataset.val_file_name)
        json.dump(val_dataset, open(val_dataset_to_upload, "w"), indent = 4, cls = NpEncoder)
        val_dataset_in_storage_path = f'{cfg.gs.recoded_dataset_version}/{cfg.dataset.val_file_name}'
        
        return train_dataset_in_storage_path, val_dataset_in_storage_path


    
        
        
        
    def save_dataset_gs(cfg, train_dataset_path, val_dataset_path):        
        storage_client = storage.Client()
        bucket = storage_client.get_bucket(cfg.gs.recoded_dataset_bucket_name)
        
        train_blob = bucket.blob(train_dataset_path)
        train_blob.upload_from_filename(cfg.dataset.train_file_name)
        
        val_blob = bucket.blob(val_dataset_path)
        val_blob.upload_from_filename(cfg.dataset.val_file_name)
        
        
        
    if __name__=="__main__":
        cfg = load_config_in_pipeline(cfg_path)
        set_gs_credentials(cfg.gs.client_secrets, gs_secret)
        
        train_dataset_path, val_dataset_path = load_recorded_dataset(cfg)
        
        save_dataset_gs(cfg, train_dataset_path, val_dataset_path)
    
    

    
    
    


save_dataset_op  = create_component_from_func(func =save_dataset,
                                              base_image = SAVE_GS_IMAGE,        
                                              output_component_file=SAVE_GS_COM_FILE)
```





# record(dir)

## Dockerfile

```yaml
FROM python:3.8
ENV PYTHONUNBUFFERED 1

RUN pip install google-cloud-storage
RUN pip install pipeline_taeuk4958==1.1.5
```



## load_dataset.py

```python

import kfp
from kfp.components import InputPath, create_component_from_func

from config import LOAD_DATA_IMAGE, LOAD_DATA_COM_FILE

def download_dataset(gs_secret : dict,
                     cfg_path: InputPath("dict")):
    
    import json
    import os
    from pipeline_taeuk4958.configs.config import load_config_in_pipeline
    from pipeline_taeuk4958.cloud.gs import set_gs_credentials
    from google.cloud import storage
    

    def download_dataset(cfg):
        storage_client = storage.Client()
        bucket = storage_client.get_bucket(cfg.gs.recoded_dataset_bucket_name)
        
        train_dataset_in_gs = f'{cfg.dataset.dataset_version}/{cfg.dataset.train_file_name}' 
        val_dataset_in_gs = f'{cfg.dataset.dataset_version}/{cfg.dataset.val_file_name}'
        train_dataset_path = os.path.join(os.getcwd(), cfg.dataset.train_file_name)
        val_dataset_path = os.path.join(os.getcwd(), cfg.dataset.val_file_name)
        
        train_blob = bucket.blob(train_dataset_in_gs)
        val_blob = bucket.blob(val_dataset_in_gs)
        
        train_blob.download_to_filename(train_dataset_path)
        val_blob.download_to_filename(val_dataset_path)
        
    
    if __name__=="__main__":
        cfg = load_config_in_pipeline(cfg_path)
        set_gs_credentials(cfg.gs.client_secrets, gs_secret)
                           
        download_dataset(cfg)
        print(f"\n now : {os.listdir(os.getcwd())}")
        
        train_dataset_path = os.path.join(os.getcwd(), cfg.dataset.train_file_name)
        with open(train_dataset_path, "r", encoding='utf-8') as f:
            train_dataset = json.load(f)
        print(f"train_dataset : \n{train_dataset}")
        
    
  
download_dataset_op = create_component_from_func(func = download_dataset,
                                        base_image = LOAD_DATA_IMAGE,
                                        output_component_file= LOAD_DATA_COM_FILE)
```

