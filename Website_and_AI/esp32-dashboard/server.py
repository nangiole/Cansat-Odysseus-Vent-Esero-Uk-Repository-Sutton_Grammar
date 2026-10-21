from flask import Flask, render_template
import serial 
import time
import threading

app = Flask(__name__)

data = []


def generate_data():
    ser = serial.Serial('COM3', 115200, timeout=1)
    while True:
        d1= ser.readline().decode('utf-8', errors='replace').strip()
        if d1:
            data.append(d1)
            time.sleep(0.1)
            
threading.Thread(target=generate_data, daemon=True).start()

@app.route("/")
def home():
    return render_template("index.html")

@app.route("/data")
def get_data():
    return data
    

app.run(debug=True)