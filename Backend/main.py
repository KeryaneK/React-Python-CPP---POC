from flask import Flask, jsonify, request
from flask_cors import CORS
import subprocess

app = Flask(__name__)
CORS(app)

def is_invalid_login(input_string):
    valid_characters = set("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_")

    for char in input_string:
        if char not in valid_characters:
            return True
    
    return False

def is_invalid_password(password):
    if ' ' in password:
        return True
    return False

@app.route('/api/addUser')
def add_user():
    login = request.args.get('login')
    password = request.args.get('password')

    if (login and password):

        if is_invalid_login(login):
            return 'FORBIDDEN_LOGIN'
        
        if is_invalid_password(password):
            return  'FORBIDDEN_PASSWORD'

        try:
            return subprocess.run(['./addUser', login, password], capture_output=True, text=True, check=True).stdout
        except subprocess.CalledProcessError as e:
            return 'ERROR'

    return 'ERROR'

@app.route('/api/checkUser')
def check_user():
    login = request.args.get('login')
    password = request.args.get('password')
    
    if (login and password):

        if is_invalid_login(login):
            return 'FORBIDDEN_LOGIN'
        
        if is_invalid_password(password):
            return  'FORBIDDEN_PASSWORD'

        try:
            return subprocess.run(['./checkUser', login, password], capture_output=True, text=True, check=True).stdout
        except subprocess.CalledProcessError as e:
            return 'ERROR'
    
    return 'ERROR'

@app.route('/api/addPost')
def add_post():
    title = request.args.get('title')
    content = request.args.get('content')
    user_id = request.args.get('userId')

    if (title and content and user_id):
        try:
            return subprocess.run(['./addPost', title, content, user_id], capture_output=True, text=True, check=True).stdout
        except subprocess.CalledProcessError as e:
            return 'ERROR'

    return 'ERROR'

@app.route('/api/deletePost')
def delete_post():
    user_id = request.args.get('userId')
    post_id = request.args.get('postId')

    if user_id and post_id:
        try:
            return subprocess.run(['./deletePost', user_id, post_id], capture_output=True, text=True, check=True).stdout
        except subprocess.CalledProcessError as e:
            return 'ERROR'
    else:
        return 'ERROR'


@app.route('/api/getPosts')
def get_posts():
    user_id = request.args.get('userId')

    if (user_id):
        try:
            return jsonify(subprocess.run(['./getPosts', user_id], capture_output=True, text=True, check=True).stdout)
        except subprocess.CalledProcessError as e:
            return 'ERROR'
    
    return 'ERROR'

if __name__ == '__main__':
    app.run(debug=True)
 