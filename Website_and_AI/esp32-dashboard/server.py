from flask import Flask, render_template
import serial
import time
import threading

app = Flask(__name__)

data = []

def generate_data():
    
    with open("pressure_log.txt", "w") as f:
        f.write("") # Writes an empty string, wiping old data instantly
    
    try:
        # Open serial port (adjust 'COM3' to your actual port if needed)
        ser = serial.Serial('COM3', 115200, timeout=1)
    except Exception as e:
        print(f"Could not open serial port: {e}")
        return

    while True:
        line = ser.readline().decode('utf-8', errors='replace').strip()
        if line:
            data.append(line)
            
            try:
                # Assuming your CSV format is something like: Temp,Humidity,Pressure
                # Split the line by commas and extract the pressure value
                parts = line.split(',')
                
                # Change the index [2] to match whatever position pressure is in your CSV string!
                current_pressure = float(parts[2]) 
            except (IndexError, ValueError):
                # Fallback if a corrupted packet comes through
                current_pressure = 1013.25

            # Open 'pressure_log.txt' in append mode ("a") and add the real pressure value
            with open("pressure_log.txt", "a") as f:
                f.write(f"{current_pressure}\n")
                
        time.sleep(0.1)

# Start the background serial reader thread safely
threading.Thread(target=generate_data, daemon=True).start()

# FIXED: Added missing '@' symbols for Flask routes
@app.route("/")
def home():
    return render_template("index.html")

@app.route("/data")
def get_data():
    return data

if __name__ == "__main__":
    app.run(debug=True)