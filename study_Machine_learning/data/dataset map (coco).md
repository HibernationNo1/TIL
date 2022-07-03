

{:toc}



# coco

# {



## 'info' : 

## {

### description : str



### url : str



### version : str



### year : int



### contributor : str



### deta_created : str



### 



## }

## 'licenses' :

## [

### {

#### url : str

#### id : int

#### name : str

### }

## ]

```
[
	{'url': 'http://creativecommons.org/licenses/by-nc-sa/2.0/', 'id': 1, 'name': 'Attribution-NonCommercial-ShareAlike License'},
	{'url': 'http://creativecommons.org/licenses/by-nc/2.0/', 'id': 2, 'name': 'Attribution-NonCommercial License'},
	{'url': 'http://creativecommons.org/licenses/by-nc-nd/2.0/', 'id': 3, 'name': 'Attribution-NonCommercial-NoDerivs License'},
	{'url': 'http://creativecommons.org/licenses/by/2.0/', 'id': 4, 'name': 'Attribution License'},
	{'url': 'http://creativecommons.org/licenses/by-sa/2.0/', 'id': 5, 'name': 'Attribution-ShareAlike License'},
	{'url': 'http://creativecommons.org/licenses/by-nd/2.0/', 'id': 6, 'name': 'Attribution-NoDerivs License'},
	{'url': 'http://flickr.com/commons/usage/', 'id': 7, 'name': 'No known copyright restrictions'},
	{'url': 'http://www.usa.gov/copyright.shtml', 'id': 8, 'name': 'United States Government Work'}
]

```





## 'images' :

## [

### images[0] 

### {

#### 'license': 2	int

#### 'file_name': '000000428067.jpg'	  str

#### 'coco_url': str

> 'http://images.cocodataset.org/train2017/000000428067.jpg'

#### 'height': 480		int

#### 'width': 640		 int

#### 'date_captured': 	str

> '2013-11-16 21:16:59'	

#### 'flickr_url': str

> 'http://farm9.staticflickr.com/8427/7597636002_d24610e0e8_z.jpg'

#### 'id': 428067		int(unique)

### }

### ... ,

### images[N]



## ]

## 'annotations' :

## [

### annotations[0]

###  {

#### 'segmentation': [[x_1, y_1, x_2, y_2, ..., x_n, y_n]], 	[[float, ..., float]]

#### 'area':  float

#### 'iscrowd': 0  int

#### 'image_id':  int 

> images의 id에 대응되는 값

#### 'bbox': [x_min, y_min, a, b]  	[float, float, float, float]

> x_min + a = x_max, 		y_min + b = y_max

#### 'category_id':   int

> categories의 id에 대응되는 값

#### 'id': int(unique)

### }

### ... ,

### annotations[N]

## ]

## 'categories' :

## [

### categories[0]

### {

#### 'supercategory': str

> 'person'

#### 'id':  int

#### 'name':	str

>  'person'

### }

### ... ,

### categories[N]

## ]

# }