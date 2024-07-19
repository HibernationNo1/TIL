from fastapi import APIRouter, Request, Depends
from fastapi.templating import Jinja2Templates
from sqlalchemy.orm import Sessio

class WebController:
    def __init__(self, router:APIRouter, templates: Jinja2Templates, service: DemoService) -> None:
        self.router = router
        self.templates = templates
        self.service = service

        self.router.add_api_route('', self.get_demo_page, methods=['GET'])
        self.router.add_api_route('/token_valid', self.validiation_check, methods=['GET'])
        self.router.add_api_route('/check', self.check, methods=['GET'])
        self.router.add_api_route('/sort', self.sort_item, methods=['POST'], status_code=201)
        self.router.add_api_route('/signup', self.signup, methods=['POST'], status_code=201)
        self.router.add_api_route('/login', self.login, methods=['POST'], status_code=201)