import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QLabel, QTextEdit, QVBoxLayout, QWidget
import serial
import socket
import json

def create_control_message(command, value):
    return json.dumps({"command": command, "value": value})

def parse_feedback_message(message):
    return json.loads(message)

def get_control_data(self):
    # 获取Control的数据
    if self.serial_port:
        data = self.serial_port.readline().decode('utf-8').strip()
    elif self.socket:
        data = self.socket.recv(1024).decode('utf-8').strip()
    else:
        data = "No connection"
    self.data_log.append(f"Control Data: {data}")
    return parse_feedback_message(data)

def send_feedback_data(self, data):
    # 发送Feedback的数据
    message = create_control_message("feedback", data)
    if self.serial_port:
        self.serial_port.write(message.encode('utf-8'))
    elif self.socket:
        self.socket.send(message.encode('utf-8'))
    self.data_log.append(f"Feedback Data Sent: {message}")

def connect(self):
    # 配置串口或以太网连接
    try:
        self.serial_port = serial.Serial('COM1', 9600, timeout=1)
        self.status_label.setText("Status: Connected via Serial")
        self.running_log.append("Connected via Serial")
    except serial.SerialException:
        try:
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.socket.connect(('192.168.1.100', 8080))
            self.status_label.setText("Status: Connected via Ethernet")
            self.running_log.append("Connected via Ethernet")
        except socket.error:
            self.status_label.setText("Status: Connection Failed")
            self.running_log.append("Connection Failed")

    self.running_log.append("Attempted to connect")



class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        self.setWindowTitle("Control and Feedback System")
        self.setGeometry(100, 100, 600, 400)

        self.layout = QVBoxLayout()

        self.connect_button = QPushButton("Connect")
        self.connect_button.clicked.connect(self.connect)
        self.layout.addWidget(self.connect_button)

        self.status_label = QLabel("Status: Disconnected")
        self.layout.addWidget(self.status_label)

        self.data_log = QTextEdit()
        self.data_log.setReadOnly(True)
        self.layout.addWidget(self.data_log)

        self.running_log = QTextEdit()
        self.running_log.setReadOnly(True)
        self.layout.addWidget(self.running_log)

        container = QWidget()
        container.setLayout(self.layout)
        self.setCentralWidget(container)

        self.serial_port = None
        self.socket = None

    def connect(self):
        # 配置串口或以太网连接
        try:
            self.serial_port = serial.Serial('COM1', 9600, timeout=1)
            self.status_label.setText("Status: Connected via Serial")
        except serial.SerialException:
            try:
                self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
                self.socket.connect(('192.168.1.100', 8080))
                self.status_label.setText("Status: Connected via Ethernet")
            except socket.error:
                self.status_label.setText("Status: Connection Failed")

        self.running_log.append("Attempted to connect")

    def get_control_data(self):
        # 获取Control的数据
        if self.serial_port:
            data = self.serial_port.readline().decode('utf-8').strip()
        elif self.socket:
            data = self.socket.recv(1024).decode('utf-8').strip()
        else:
            data = "No connection"
        self.data_log.append(f"Control Data: {data}")
        return data

    def send_feedback_data(self, data):
        # 发送Feedback的数据
        if self.serial_port:
            self.serial_port.write(data.encode('utf-8'))
        elif self.socket:
            self.socket.send(data.encode('utf-8'))
        self.data_log.append(f"Feedback Data Sent: {data}")

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())
