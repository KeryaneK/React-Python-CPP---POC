from flask import Flask, jsonify, request
import subprocess

app = Flask(__name__)

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

@app.route('/')
def index():
    return '404';

@app.route('/addUser')
def add_user():
    login = request.args.get('login')
    password = request.args.get('password')
    if (login and password):

        if is_invalid_login(login):
            return 'FORBIDDEN_LOGIN'
        
        if is_invalid_password(password):
            return  'FORBIDDEN_PASSWORD'

        try:
            return subprocess.run(['./addUser.exe', login, password], capture_output=True, text=True, check=True).stdout
        except subprocess.CalledProcessError as e:
            return 'ERROR'

    return 'ERROR'

@app.route('/checkUser')
def check_user():
    pass

@app.route('/addPost')
def add_post():
    pass

@app.route('/deletePost')
def delete_post():
    pass

@app.route('/getPosts')
def get_posts():
    pass

if __name__ == '__main__':
    app.run(debug=True)
 