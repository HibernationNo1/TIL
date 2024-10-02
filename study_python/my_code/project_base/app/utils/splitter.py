import cv2
import numpy as np
import os, os.path as osp
from copy import deepcopy
from itertools import groupby
import math

from handlers.config import CONFIG_REGISTRY
from handlers.logger import LOGGER_REGISTRY
from configs.base import BASE_SERVER_LOGGER_NAME, BASE_DEBUG_LOGGER_NAME, BASE_CONFIG_NAME, BASE_FAILED_LOGGER_NAME
server_logger = LOGGER_REGISTRY[BASE_SERVER_LOGGER_NAME]['logger']
debug_logger = LOGGER_REGISTRY[BASE_DEBUG_LOGGER_NAME]['logger']
failed_logger = LOGGER_REGISTRY[BASE_FAILED_LOGGER_NAME]['logger']



cfg = CONFIG_REGISTRY[BASE_CONFIG_NAME]


class ImageSplitter(object):
    def __init__(self, Splitter_cfg):
        
        self.len_th = Splitter_cfg.len_th  
        self.cut_th = Splitter_cfg.cut_th 
        self.area_th = Splitter_cfg.area_th
        self.img_w_th, self.img_h_th = Splitter_cfg.img_w_th, Splitter_cfg.img_h_th

        self.src_img = None
        self.src_gray = None

        self.width = None
        self.height = None
        
        self.cur_img = None
        self.pre_img = None

        self.labels = None
        self.stats = []
        self.cnt_arr = []

    def find_unique_bg(self, image):
        start_idx = None
        crop_bin = []
        gray_img = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        for i, row in enumerate(gray_img[1:], start=1):

            row_, counts = np.unique(row, return_counts=True)
            most_common_value = row_[np.argmax(counts)]

            mask_row = ((row >= most_common_value - 6) & (row <= most_common_value + 6)).astype(int)

            diffs = np.diff(np.concatenate(([0], mask_row, [0])))  # 각 행의 시작과 끝에 0 추가, diffs를 같은 길이로 유지하기 위해
            indices_ones = np.where(diffs == 1)[0]  # 255의 시작 위치
            indices_zeros = np.where(diffs == -1)[0]  # 255의 끝 위치

            consecutive_len = indices_zeros - indices_ones  # 연속된 1의 길이 계산

            if np.max(consecutive_len) > gray_img.shape[1] * 0.9:
                if start_idx is None:
                    start_idx = i
            else:
                if start_idx is not None:
                    end_idx = i
                    crop_bin.append((start_idx, end_idx))
                    start_idx = None
            if i == gray_img.shape[0] - 1 and start_idx is not None:
                crop_bin.append((start_idx, i))

        # 가로로 crop
        crop_image_list = []
        for idx, row_ind in enumerate(crop_bin):
            if idx == 0 and len(image[1:row_ind[0]-1, :]) > 0:
                crop_image_list.append(image[:row_ind[0]-1, :])
            if idx == len(crop_bin) - 1 and len(image[row_ind[1]:-1, :]) > 0:
                crop_image_list.append(image[row_ind[1]:-1, :])
            elif idx != len(crop_bin) - 1 and len(image[row_ind[1]:crop_bin[idx+1][0]-1, :]) > 0:
                crop_image_list.append(image[row_ind[1]:crop_bin[idx+1][0]-1, :])
        
        return crop_image_list


    def filter_small_area(self, cnt, stats):
        # 작은 요소 삭제
        indices_to_delete = []
        for index, (w, h, area) in enumerate(stats[1:, 2 : 5]):
            # if w == self.width and h == self.height:
            #     indices_to_delete.append(index)
            if area < self.area_th or w <= self.img_w_th or h <= self.img_h_th:
                indices_to_delete.append(index)
        
        cnt_arr = np.array(range(1, cnt))
        cnt_arr = np.delete(cnt_arr, indices_to_delete, axis=0)

        return list(cnt_arr)
    
    def getComponents(self, gray_img):

        # gray_img = cv2.bitwise_not(gray_img)
        cnt, labels, stats, centroids = cv2.connectedComponentsWithStats(gray_img)
        
        # 만일 흰색 배경이거나, 객체 전체가 이미지 크기와 같다면, 이미지 반전
        for w, h in stats[1:, 2 : 4]:
            if w == gray_img.shape[1] and h == gray_img.shape[0]:
                inverted_image = cv2.bitwise_not(gray_img)
                cnt, labels, stats, centroids = cv2.connectedComponentsWithStats(inverted_image)
                break
        
        return cnt, labels, stats

    def getComponents_with_histogram(self, gray_img):

        dst_img = deepcopy(gray_img)

        hist = cv2.calcHist([dst_img], [0], None, [16], [0, 256])
        most_common_bin =np.argmax(hist)

        # 가장 많이 나온 구역의 색을 0(배경)으로 변경
        dst_img[(dst_img >= most_common_bin * 16) & (dst_img <= (most_common_bin + 1) * 16)] = 0
        
        # 연결된 요소 레이블링 적용
        cnt, labels, stats, centroids = cv2.connectedComponentsWithStats(dst_img)

        return cnt, labels, stats
    
    def find_lines_and_draw(self, image):
        """
        --------------------------------------
        엣지를 검출하고 허프 변환으로 직선을 검출하는 함수

        cv2.Canny: 엣지 검출 함수
        cv2.HoughLinesP: 허프 변환
        --------------------------------------
        """
        height, width = image.shape[1], image.shape[0]
        hor_mask = np.zeros((width, height), dtype=np.uint8)
        vel_mask = np.zeros((width, height), dtype=np.uint8)
        edges = cv2.Canny(image, 50, 100, apertureSize=3)
        
        lines = cv2.HoughLinesP(edges, 1, (np.pi / 180), threshold=100, minLineLength=100, maxLineGap=13)

        # 검출된 선분을 원본 이미지에 그리기
        if lines is not None:
            for line in lines:
                x1, y1, x2, y2 = line[0]

                # 기울기 계산
                m = (y2 - y1) / (x2 - x1) if (x2 - x1) != 0 else float('inf')

                # 수평선 또는 수직선 검출
                if m == 0:  # 수평선
                    cv2.line(hor_mask, (x1, y1), (x2, y2), 255, 4)
                elif m == float('inf'):  # 수직선
                    cv2.line(vel_mask, (x1, y1), (x2, y2), 255, 4)
                # cv2.line(line_image, (x1, y1), (x2, y2), (255, 0, 0), 4)
        
        return hor_mask, vel_mask
    
    def max_length_for_line(self, mask, len_th, cut_th):
        """ 
        ----------------------------------------------------------------
        mask에서 각 행에 대해 1이 연속으로 나오는 최대 개수를 찾고, 조건에 맞는 최대 길이 
        기준으로 내림차순으로 최대 길이와 해당 행을 return하는 함수   

        - len_th: 최대 길이가 width * len_th 보다 커야 함
        - cut_th: 자르는 위치가 height - cut_th보다 작아야 함
        ----------------------------------------------------------------
        """

        height, width = mask.shape
        column_th = int(width * len_th)

        # 각 행에서 1이 연속된 개수와 index를 저장할 딕셔너리
        consecutive_dict = {}
        
        for cut_point, row in enumerate(mask):
            # 각 행에서 1이 연속된 개수를 구함
            diffs = np.diff(np.concatenate(([0], row, [0])))  # 각 행의 시작과 끝에 0 추가, diffs를 같은 길이로 유지하기 위해
            indices_ones = np.where(diffs == 255)[0]  # 255의 시작 위치
            indices_zeros = np.where(diffs == -255)[0]  # 255의 끝 위치
            
            consecutive_len = indices_zeros - indices_ones  # 연속된 1의 길이 계산

            # consecutive lengths
            if consecutive_len.size == 0:
                consecutive_len = 0
            
            max_consecutive = np.max(consecutive_len)

            # 최대 길이가 width * threshold 보다 커야 함, 자르는 위치가 height - cut_th보다 작아야 함
            if max_consecutive > column_th and cut_point < height - cut_th and cut_point > cut_th:
                consecutive_dict[cut_point] = max_consecutive
            
        # sort_consecutive = sorted(consecutive_dict.items(), reverse=True)
        sort_consecutive =  sorted(consecutive_dict.items(), key=lambda item: item[1], reverse=True)
        
        
        return sort_consecutive
    
    def crop_by_line(self, crop_image, mask, len_th, cut_th):
        """
        ------------------------------------------------------
        mask에서 조건에 맞는 최대 길이에 의해 이미지를 두개로 crop하는 함수
        ------------------------------------------------------
        """

        hor_mask, ver_mask = mask

        row_consecutive = self.max_length_for_line(hor_mask, len_th, cut_th)
        # col_consecutive = self.max_length_for_line(ver_mask.transpose(), len_th, cut_th)

        crop_images = []

        # 가로로 crop
        row_tmp = 0
        for row_ind, _ in row_consecutive:
            if row_ind > row_tmp:
                crop_images.append(crop_image[:row_ind, :])
                crop_images.append(crop_image[row_ind:, :])
                row_tmp = row_ind + 150

        # 세로로 crop
        # col_tmp = 0
        # for col_ind, _ in col_consecutive:
        #     if col_ind > col_tmp:
        #         crop_images.append(crop_image[:, :col_ind])
        #         crop_images.append(crop_image[:, col_ind:])
        #         row_tmp = col_tmp + 150

        # 자를만한 선이 없는 경우, 그대로 저장
        # if len(row_consecutive) == 0 and len(col_consecutive) == 0:
        if len(row_consecutive) == 0:
            crop_images.append(crop_image)
        
        return crop_images

    def image_split(self, input_img, update = True):
        
        color_img = input_img
        gray_img = cv2.cvtColor(input_img, cv2.COLOR_BGR2RGB)

        # 연결된 요소 레이블링 적용 ---①
        cnt, labels, stats = self.getComponents_with_histogram(gray_img)
        cnt_arr = self.filter_small_area(cnt, stats)
        

        crop_img_list = []

        # image crop
        for index, stat in enumerate(stats[cnt_arr]):
            x, y, w, h, _ = stat
            crop_img = input_img[y : y + h, x : x + w]
            crop_img_list.append(crop_img)
        
        if update:
            self.stats = stats
            self.cnt_arr = cnt_arr
            self.labels = labels

            self.src_img = color_img
            self.src_gray = gray_img
            self.width = color_img.shape[1]
            self.height = color_img.shape[0]
        
        return crop_img_list

    def image_split_recursive(self, input_img, update = True, use_houghline = True):
        # 연결된 요소 레이블링 적용 ---①
        
        if self.pre_img is not None and self.cur_img is not None and input_img is not None:
            ph, pw, _ = self.pre_img.shape
            ch, cw, _ = self.cur_img.shape

            if ph == ch and pw == cw:
                return [input_img]

        self.pre_img = input_img
        color_img = input_img
        gray_img = cv2.cvtColor(input_img, cv2.COLOR_BGR2GRAY)
        
        cnt, labels, stats = self.getComponents_with_histogram(gray_img) # 
        cnt_arr = self.filter_small_area(cnt, stats) 

        crop_images_his = []
        crop_images_uni = []
        crop_images_hou = []
        # image crop (최소 박스)
        for stat in stats[cnt_arr]:
            x, y, w, h, _ = stat

            if h <= 3000:
                crop_img = color_img[y : y + h, x : x + w]
                crop_images_his.append(crop_img)
            else:
                crop_img = color_img[y : y + h, x : x + w]
                self.cur_img = crop_img
                crop_images_his += self.image_split_recursive(crop_img, update=False)
        
        if not update:
            return crop_images_his
        else:
            crop_images_tmp = []
            # 이미지 행에서 모두 동일한 색 영역 제거
            for idx, crop in enumerate(crop_images_his):
                crop_images_uni = self.find_unique_bg(crop)
                if len(crop_images_uni) > 0:
                    # print()
                    crop_images_tmp += crop_images_uni
                else:
                    crop_images_tmp.append(crop_images_his[idx])     

            if use_houghline:
                # 허프 변환
                for crop in crop_images_tmp:
                    mask = self.find_lines_and_draw(crop)
                    crop_images_hou += self.crop_by_line(crop, mask, self.len_th, self.cut_th)
        
            self.stats = stats
            self.cnt_arr = cnt_arr
            self.labels = labels

            self.src_img = color_img
            self.src_gray = gray_img
            self.width = color_img.shape[1]
            self.height = color_img.shape[0]

            self.pre_img = None
            self.cur_img = None

        if use_houghline:
            return crop_images_hou
        else:
            return crop_images_tmp
    
    def make_label_result(self):
        # 결과 이미지 생성
        label_img = np.zeros_like(self.src_img)

        # 레이블 갯수 만큼 순회
        for i in self.cnt_arr:
            # 레이블이 같은 영역에 랜덤한 색상 적용
            label_img[self.labels==i] = [int(j) for j in np.random.randint(0, 255, 3)]
        
        return label_img
    

splitter_instance = ImageSplitter(cfg.splitter.split)
from multiprocessing import Pool

def image_split(img_save_path, use_houghline):
    # image splitW
    try:
        # 제대로 image를 read하는지 확인
        input_image = cv2.imread(img_save_path)
        input_image.shape
    except:
        failed_logger.info(f"Splitter Error: faild load image from '{img_save_path}'")
        return []
    img_list = splitter_instance.image_split_recursive(input_img = input_image, 
                                                       use_houghline = use_houghline)
    return img_list
    

def image_split_with_multiprocessing(args):
    img_save_path, use_houghline, logger = args
    # image splitW
    try:
        # 제대로 image를 read하는지 확인
        input_image = cv2.imread(img_save_path)
        input_image.shape
    except:
        logger.info(f"Splitter Error: faild load image from '{img_save_path}'")
        return []
    img_list = splitter_instance.image_split_recursive(input_img = input_image, 
                                                       use_houghline = use_houghline)
    # debug_logger.info(f"img_list; {img_list}")
    return img_list

def get_splited_images_interval(separate_cfg, num_images):
    if num_images >= separate_cfg.min_threshold_url:
        using_num = int(separate_cfg.url_ratio_weight*math.log(num_images**5))        # 전체 image url 중 사용할 url의 개수 계산 
        if using_num > num_images:      # 계산된 url의 개수가 받은 url의 개수보다 큰 경우
            using_ratio = 1             # 받은 url을 전부 사용
        elif using_num < separate_cfg.min_threshold_url:            # 계산된 url의 개수가 최소 필요조건 url의 개수보다 적은 경우
            using_ratio = using_num/separate_cfg.min_threshold_url  # 최소 필요조건 url의 개수만큼 사용
        else:
            using_ratio = using_num/num_images                  # 전체 image url 중 사용하는 url의 비율
    else:
        using_ratio = 1

    num_to_using =  int(num_images*using_ratio) 
    interval = 1
    if num_to_using < num_images:
        # 버릴 url이 있는 경우
        # image를 몇 간격으로 건너뛰며 사용할것인지 상수 결정
        # interval == 1 인 경우 전부 사용하며
        # interval == 2 인 경우 2개중에 1개는 버린다.
        # interval == 3 인 경우 3개중에 2개는 버린다.
        interval = num_images // (num_to_using)
    return interval


def save_splited_images(split_cfg, total_api_data, splitter_path, splited_images_list, input_image_path_list, interval, max_required):
    # split_file_list:: crop image의 저장 path
    split_file_list = []    # model API에서 file에 접근할 때 사용할 list(file_name.ext 를 담게 된다.)
    image_count = 1         # 탐색하는 image 개수
    for crop_image_list, img_save_path  in zip(splited_images_list, input_image_path_list):
        # file 이름과 확장자 추출
        file_name = osp.basename(img_save_path)
        total_api_data['image_url'][file_name]['splited_image'] = list()
        

        raw_file_name, file_ext = osp.splitext(file_name)
        if file_ext != '.jpg': continue 
        
        for idx, crop_image in enumerate(crop_image_list):
            # 저장할 path 설정
            splitter_file_name = f"{raw_file_name}_{idx+1}{file_ext}"
            splitter_image_path = osp.join(splitter_path, splitter_file_name)

            if crop_image.shape[0] > split_cfg.img_w_th and crop_image.shape[1] > split_cfg.img_h_th:
                # 해당 조건이 만족하는 image만 저장
                if image_count == 1:
                    # 첫 번째 이미지는 반드시 저장
                    try:
                        cv2.imwrite(splitter_image_path, crop_image)
                        split_file_list.append(splitter_file_name)
                        total_api_data['image_url'][file_name]['splited_image'].append(splitter_file_name)      
                    except Exception as e:
                        failed_logger.info(f"Failed save splitter image. path: '{splitter_image_path}', Error: {e} ")
                        continue
                else:
                    # interval(간격)에 따라 image저장 (그 외는 버린다.)
                    if image_count % interval == 0:
                        try:
                            cv2.imwrite(splitter_image_path, crop_image)
                            split_file_list.append(splitter_file_name)
                            total_api_data['image_url'][file_name]['splited_image'].append(splitter_file_name)
                            if max_required <= len(split_file_list):
                                return total_api_data, split_file_list
                        except:
                            failed_logger.info(f"Failed save splitter image. path: '{splitter_image_path}',      image type: '{type(crop_image)}' ")
                            continue
                
                image_count +=1

    return total_api_data, split_file_list


def run_splitter(run_splitter_cfg, splitter_path, input_image_path_list, total_api_data):
    ## input_image로부터 crop image 및 배경제거 (splitter)
    # multiprocessing을 사용
    if run_splitter_cfg.use:
        num_workers = min(int(os.cpu_count() / 2), cfg.num_workers.min)
        pool = Pool(processes=num_workers)
        image_split_args = [(img_save_path, run_splitter_cfg.use_houghline, failed_logger) 
                            for img_save_path in input_image_path_list]
        splited_images_list = pool.map(image_split_with_multiprocessing, image_split_args)  
    else:
        splited_images_list = list()
        for img_save_path in input_image_path_list:
            splited_images = image_split(img_save_path = img_save_path,
                    use_houghline = run_splitter_cfg.use_houghline)
            splited_images_list.append(splited_images)

    ## splited_images의 전체 개수 계산
    num_splited_images = 0
    for crop_image_list in splited_images_list:
        for crop_image in crop_image_list:
            if crop_image.shape[0] > run_splitter_cfg.split.img_w_th and crop_image.shape[1] > run_splitter_cfg.split.img_h_th:
                    num_splited_images += 1

    ## splited_images의 전체 개수가 model inference를 진행할 만큼 유효한지 판단.
    if not run_splitter_cfg.min_required < num_splited_images :
        # 최소한으로 사용할 image의 개수가 부족한 경우 
        # 유효하지 않은 curl이라고 판단 
        message = (f"product page dose not have sufficient number of image  "
                    f"number of minimum required: '{run_splitter_cfg.min_required}' but got '{num_splited_images}'")
        server_logger.error(message)
        return False, message, None, None
    ## splited_images의 개수가 많은 경우 일부분은 버리기 위한 interval값 계산
    # interval==1 :: 버리는것 없이 사용
    # interval==N :: N개중에 1개 버린다,
    if run_splitter_cfg.separate.use:
        interval = get_splited_images_interval(separate_cfg = run_splitter_cfg.separate, 
                                            num_images = num_splited_images)
    else: interval = 1
    
    ## image저장
    total_api_data, split_file_list = save_splited_images(split_cfg = run_splitter_cfg.split,
                                          total_api_data = total_api_data,                  # 전체 동작 과정에서 사용되는 date를 기록하는 dict
                                          splitter_path = splitter_path,                    # 저장할 dir path
                                          splited_images_list = splited_images_list,        # splited_image가 저장된 list(numpy)
                                          input_image_path_list = input_image_path_list,      # image_url로부터 저장한 input image의 path list
                                          interval = interval,                               # image저장시 몇 번째 간격마다 저장할지 결정하는 계수
                                          max_required = run_splitter_cfg.max_required)      # splited image의 최대 개수 허용 조건
    
    
    debug_logger.info(f"Get {num_splited_images} images from {len(input_image_path_list)} 'image_urls' and useing {len(split_file_list)}")
    return True, split_file_list, num_splited_images, total_api_data