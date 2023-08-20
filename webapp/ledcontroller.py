import protocol
import udp


from flask import Flask
from flask import render_template
from flask import request

from flask import Flask, redirect, url_for, request
app = Flask(__name__)

# Setup UDP Controller
IP = "239.1.1.1"
PORT = 4000
INTERFACE = "192.168.4.70"
udp_controller = udp.UDPMulticastIO(IP, PORT, INTERFACE)

@app.route('/')
def index():
    return redirect(url_for('ledcontroller'))

@app.route('/ledcontroller', methods = ['POST', 'GET'])
def ledcontroller():
    if request.method == 'POST':
        mode = protocol.parse_mode(request.form['mode'])
        color = protocol.parse_color(request.form['color'])
        rate = protocol.parse_rate(request.form['rate'])
        brightness = protocol.parse_brightness(request.form['brightness'])

        # testing
        print(mode)
        print(color)
        print(rate)
        print(brightness)

        payload = protocol.pack_payload(mode, rate, color, brightness)
        udp_controller.send(payload)

    # TODO data persistence on webpage
    return render_template('ledcontroller.html')

if __name__ == '__main__':
    app.run(debug=True, host="0.0.0.0", port=8000)