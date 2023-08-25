import protocol
import udp
import threading
import time

from flask import Flask
from flask import render_template
from flask import request

from flask import Flask, redirect, url_for, request
app = Flask(__name__)

# TODO make this based off the enum
MODE_LABELS = [
    "off",
    "solid",
    "breathe",
    "cycle",
    "breathe_cycle",
    "chaser"
]

# Setup UDP Controller
IP = "239.1.1.1"
PORT = 4000
INTERFACE = "192.168.4.70"
udp_controller = udp.UDPMulticastIO(IP, PORT, INTERFACE)
payload = None

@app.route('/')
def index():
    return redirect(url_for('ledcontroller'))

@app.route('/ledcontroller', methods = ['POST', 'GET'])
def ledcontroller():
    if request.method == 'POST':
        mode = request.form['mode']
        color = request.form['color']
        rate = request.form['rate']
        brightness = request.form['brightness']

        # Transmit UDP packet to the LED Controller(s)
        global payload
        payload = protocol.pack_payload(
            protocol.parse_mode(mode),
            protocol.parse_rate(rate),
            protocol.parse_color(color),
            protocol.parse_brightness(brightness))
        udp_controller.send(payload)
    else:
        # Default values
        mode = "solid"
        color = "#ff0000"
        rate = 0xFF
        brightness = 128

    return render_template('ledcontroller.html',
                            modes=MODE_LABELS,
                            current_mode=mode,
                            color=color,
                            rate=rate,
                            brightness=brightness)

def udp_tx_thread():
    # periodically send UDP messages over time
    # to synchronize mulitple controllers 
    while True:
        global payload
        if payload is not None:
            udp_controller.send(payload)
            time.sleep(60 * 60) # 60 secs x 60 minutes = 1 hour

if __name__ == '__main__':
    tx_thread = threading.Thread(target=udp_tx_thread, daemon=True)
    tx_thread.start()
    app.run(debug=True, host="0.0.0.0", port=8000)