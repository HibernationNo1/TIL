from sqlalchemy.orm import Session
from typing import List

from api_utils.dto import *
from api_utils.database import User, Item
from repository.web import WebRepository

from handlers.exceptions import *
from api_utils.jwt_manager import jwt_encode
import json

class DemoService:
    def __init__(self, repository:WebRepository) -> None:
        self.repository = repository
        pass

    def open_json(self):
        '''
        static/product_list.json에서\\
        기본 item list를 읽어 반환 
        '''
        with open('static/product_list.json', 'r') as f:
            data = json.load(f)
        
        return data
    def check(self, db: Session, username: str):
        '''
        db에서 username이 있는지 확인하여\\
        존재할 때 ValidationExcetpion을 발생시킴
        '''
        if self.repository.check_username(db, username):
            raise ValidationException(451, f'Username '{username}' already exists')
        
    def sort_item(self, sort_item_dto:SortItemDto, user_id:int, db:Session):
        '''
        product_id: int
        sort_num: int
        ctgr: str와\\
        user_id을 받아 db에서\\
        product_id에 해당하는 item객체 가져와\\
        sort_num이 옮기려는 위치와 옮기려는 item객체의 sort_num\\
        사이에 위치한 item들의 sort_num을 조정
        '''
        product_id = sort_item_dto.product_id
        sort_num = sort_item_dto.sort_num
        ctgr = sort_item_dto.ctgr
        
        product = self.repository.get_item(db, product_id)

        origin_sort_num = product.sort_num
        start_sort_num = min(origin_sort_num, sort_num)
        stop_sort_num = max(origin_sort_num, sort_num)
        value = 1 if origin_sort_num > sort_num else -1

        item_objects = self.repository.get_item_list_by_sort_num(db, user_id, start_sort_num, stop_sort_num, ctgr)
        item_objects.update({'sort_num':Item.sort_num+value})
        product.sort_num = sort_num
        self.repository.commit(db)
            
    def login(self, login_dto: LoginDTO, db: Session)-> User:
        '''
        username과 password가 일치하는\\
        user 객체를 찾아 반환
        '''
        user = self.repository.login_user(db, login_dto.username, login_dto.password)
        if not user:
            raise ValidationException('not matched')
        return user
    
    def generate_access_token(self, user:User) -> str:
        '''
        user 객체를 받아\\
        jwt_manager의 jwt_encode함수로\\
        access_token 생성하여 반환
        '''
        token = jwt_encode(user)
        return token
    
    def get_item_list(self, user_id:int, db:Session) -> List[Item]:
        '''
        db에서 user_id에 해당하는\\
        item들을 카테고리별로 sort_num으로 정렬하여\\
        Item객체 리스트를 반환
        '''
        return self.repository.get_item_list(db, user_id)
    
    def signup(self, signup_dto: SignupDTO, db: Session):
        '''
        username과 password를 받아\\
        db에서 username의 중복을 확인하고\\
        user 객체를 생성\\
        기본 item_list를 받아 db에 item 생성\\
        (기본 item들을 정렬할 수 있게 하기 위함)
        '''
        self.check(db, signup_dto.username)
        user = self.repository.create_user(db, signup_dto.username, signup_dto.password)
        default_data = self.open_json()
        self.repository.create_default_items(db, user.id, default_data)
    
    def serialize_data(self, item_list:List[Item]) -> dict:
        '''
        item 객체들의 요소 중에서\\
        필요한 값들만 뽑아 직렬화 함
        '''
        data = {}
        for item in item_list:
            if item.ctgr not in data:
                data[item.ctgr] = []
            data[item.ctgr].append({'id':item.id, 'product':item.product})
        return data