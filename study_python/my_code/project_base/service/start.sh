#!/bin/bash
gunicorn --config 'configs/gunicorn.py' ocr_api:app