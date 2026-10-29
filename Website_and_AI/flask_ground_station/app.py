
from flask import Flask

app = Flask(__name__)

@app.route("/")
def home():
    return """
    <html>
        <head>
            <title>CanSat Ground Station</title>
        </head>
        <body style="font-family: Arial; text-align: center; background: #101827; color: white; padding: 50px;">
            <h1>CanSat Ground Station</h1>
            <h2>System Online</h2>
            <p>Your dashboard is running!</p>
            <p>Camera: Waiting for connection</p>
            <p>Sensors: Waiting for connection</p>
        </body>
    </html>
    """

if __name__ == "__main__":
    app.run(debug=True)

