from flask import Flask
from flask import render_template
from flask import request

from flask import Flask, redirect, url_for, request
app = Flask(__name__)

@app.route('/')
def index():
    return redirect(url_for('login'))

@app.route('/dashboard/<name>')
def dashboard(name):
    return f"welcome {name}"

@app.route('/login', methods = ['POST', 'GET'])
def login():
    if request.method == 'POST':
        user = request.form['name']
        return redirect(url_for('dashboard', name = user))
    else: # GET
        user = request.args.get('name')
        return render_template('login.html')
    
if __name__ == '__main__':
    app.run(debug=True, host="0.0.0.0", port=8000)