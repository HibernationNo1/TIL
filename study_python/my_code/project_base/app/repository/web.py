from sqlalchemy.orm import Session

from api_utils.database import User, Item

class WebRepository:
    def __init__(self) -> None:
        pass

    def create_user(self, db:Session, username:str, password:str):
        '''
        username, password로 user생성
        '''
        user = User(username=username, password=password)
        db.add(user)
        db.commit()
        db.refresh(user)
        return user

    def check_username(self, db:Session, username:str):
        '''
        username에 해당하는 user객체 반환
        '''
        return db.query(User).filter(User.username==username).first()

    def login_user(self, db:Session, username:str, password:str):
        '''
        username과 password에 해당하는 user객체 반환
        '''
        return db.query(User).filter(User.username==username, User.password==password).first()

    def create_item(self, db:Session, user_id:int, ctgr:str, product:str, sort_num:int):
        '''
        user_id, item의 카테고리, 업로드한 상품의 url,\\
        user_id와 카테고리에 해당하는 상품에서 가장 마지막 sort_num+1을 받아 item생성 및 반환
        '''
        item = Item(user_id=user_id, ctgr=ctgr, product=product, sort_num=sort_num)
        db.add(item)
        db.commit()
        db.refresh(item)
        return item
    
    def create_default_items(self, db:Session, user_id:int, default_data:dict):
        '''
        user_id와 기본 item를 받아\\
        item 생성
        '''
        item_list = []
        for ctgr in default_data:
            for i, product in enumerate(default_data[ctgr]):
                item = Item(user_id=user_id, ctgr=ctgr, product=product['product'], sort_num=i)
                item_list.append(item)
        db.bulk_save_objects(item_list)
        db.commit()

    def get_item(self, db:Session, item_id:int) -> Item:
        '''
        item_id에 해당하는 item 객체 반환
        '''
        return db.query(Item).filter(Item.id==item_id).first()
    
    def get_item_list(self, db:Session, user_id:int):
        '''
        user_id의 item들을 카테고리와 sort_num으로 정렬하여 반환
        '''
        return db.query(Item).filter(Item.user_id==user_id).order_by(Item.ctgr, Item.sort_num).all()

    def get_item_list_by_sort_num(self, db:Session, user_id:int, start_sort_num:int, stop_sort_num:int, ctgr:str):
        '''
        user_id와 ctgr에 해당하는 item 중 \\
        sort_num이 start_sort_num과 stop_sort_num 사이에\\
        존재하는 item들을 반환
        '''
        return db.query(Item).filter(Item.user_id==user_id, Item.ctgr==ctgr, Item.sort_num>=start_sort_num, Item.sort_num<=stop_sort_num)
    
    def get_last_item_by_ctgr(self, db:Session, user_id:int, ctgr:str):
        '''
        user_id와 ctgr에 해당하는 item의 sort_num이 가장 마지막인 item 반환
        '''
        return db.query(Item).filter(Item.user_id==user_id, Item.ctgr==ctgr).order_by(Item.sort_num.desc()).first()

    def commit(self, db:Session):
        ''''
        repository외에서 commit이 필요할 때
        '''
        db.commit()    
    
    def delete_item_by_id_and_user_id(self, db:Session, user_id:int, product_id:int):
        '''
        product_id와 user_id에 해당하는 item을 삭제
        '''
        item = db.query(Item).filter(Item.id==product_id, Item.user_id==user_id).first()
        db.delete(item)
        db.commit()
