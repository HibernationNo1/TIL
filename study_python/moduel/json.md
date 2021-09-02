# json





### save file as json

```python
import json

path_save_result_dataset = os.path.join(os.getcwd() , 'result_dataset') # instance for save of distinguish image 
os.makedirs(path_save_result_dataset, exist_ok=True)

annotation = [
		{
			"class_id": 0,
			"class_name" : "left_lung",
			"segmentation": segmentation_left_lung,
			"area" : area_left_lung, # ROI의 pixel의 개수
			"bbox" : [x_min_l, y_max_l, x_max_l, y_min_l], # 좌측 하단, 우측 상단
			"height" : y_max_l - y_min_l,
			"width" : x_max_l - x_min_l
		},

		{
			"class_id": 1,
			"class_name" : "right_lung",
			"segmentation": segmentation_right_lung,
			"area" : area_right_lung, # ROI의 pixel의 개수
			"bbox" : [x_min_r, y_max_r, x_max_r, y_min_r], # 좌측 하단, 우측 상단
			"height" : y_max_r - y_min_r,
			"width" : x_max_r - x_min_r		
		}
	]

image = {
			"image_index" : iter, # 추가
			"width" : IMAGE_SIZE[1],
			"height" :	IMAGE_SIZE[0],
			"file_name" : str(iter) + ".jpg",
			"original_image" : resized_img, 
			"mask_image" : mask_img
	}

data_image = {
			"annotation" : annotation,
			"image" : image
	}

with open(path_save_result_dataset + '\dataset.json', 'w', encoding='utf-8') as make_file:
		json.dump(data_image, make_file, indent="\t")
```







```
TypeError: Object of type int64 is not JSON serializable
```

위와 같은 에러는 json이 numpy의 dtype을 인식하지 못한 경우임

```python
class NpEncoder(json.JSONEncoder):
    def default(self, obj):
        if isinstance(obj, np.integer):
            return int(obj)
        elif isinstance(obj, np.floating):
            return float(obj)
        elif isinstance(obj, np.ndarray):
            return obj.tolist()
        else:
            return super(NpEncoder, self).default(obj)

# code
data = json.dumps(data, cls = NpEncoder)
```

