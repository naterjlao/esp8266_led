from flask import Flask
from flask import render_template
from flask import request

from flask import Flask, redirect, url_for, request
app = Flask(__name__)

@app.route('/')
def index():
    return redirect(url_for('ledcontroller'))

@app.route('/ledcontroller', methods = ['POST', 'GET'])
def ledcontroller():
    if request.method == 'POST':
        mode = request.form['mode']
        color = request.form['color']
        speed = request.form['speed']
        brightness = request.form['brightness']

        # testing
        print(mode)
        print(color)
        print(speed)
        print(brightness)
    return render_template('ledcontroller.html')
    
if __name__ == '__main__':
    app.run(debug=True, host="0.0.0.0", port=8000)