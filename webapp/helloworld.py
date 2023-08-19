from flask import Flask
from flask import render_template

# https://pythonbasics.org/flask-tutorial-hello-world/

app = Flask(__name__)

@app.route('/')
@app.route('/index')
def index():
    return render_template('index.html', title="Test Title", foo="test label")

app.run(host="0.0.0.0", port=8000)