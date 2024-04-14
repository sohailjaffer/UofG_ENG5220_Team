import sys
from PyQt5.QtWidgets import QApplication, QWidget, QVBoxLayout, QPushButton, QLabel
from PyQt5.QtCore import Qt
import socket

class RobotControlApp(QWidget):
    def __init__(self):
        super().__init__()

        self.init_ui()

        self.host = '192.168.1.185'  # Replace with the IP address of your Raspberry Pi
        self.port = 12345  # Make sure this port matches the port used in the Raspberry Pi code

        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((self.host, self.port))

        self.keys_pressed = set()  # Set to store currently pressed keys

    def init_ui(self):
        self.setWindowTitle('Robot Control')

        # Create buttons
        forward_button = QPushButton('Forward', self)
        backward_button = QPushButton('Backward', self)
        left_button = QPushButton('Left', self)
        right_button = QPushButton('Right', self)
        terminate_button = QPushButton('Terminate Connection', self)
        start_Rec_button = QPushButton('Start Recording', self)
        autoRevert_button = QPushButton('AutoRevert', self)

        # Connect button signals to functions
        forward_button.clicked.connect(self.send_forward_command)
        backward_button.clicked.connect(self.send_backward_command)
        left_button.clicked.connect(self.send_left_command)
        right_button.clicked.connect(self.send_right_command)
        terminate_button.clicked.connect(self.terminate_connection)
        start_Rec_button.clicked.connect(self.send_record_command)
        autoRevert_button.clicked.connect(self.send_autoRevert_command)

        self.status_label = QLabel('Connection Status: Connected', self)

        # Set up the layout
        layout = QVBoxLayout()
        layout.addWidget(forward_button)
        layout.addWidget(backward_button)
        layout.addWidget(left_button)
        layout.addWidget(right_button)
        layout.addWidget(terminate_button)
        layout.addWidget(start_Rec_button)
        layout.addWidget(autoRevert_button)
        layout.addWidget(self.status_label)

        self.setLayout(layout)

    def send_command(self, command):
        self.client_socket.send(command.encode('utf-8'))

    def send_forward_command(self):
        self.send_command('$1')

    def send_backward_command(self):
        self.send_command('$2')

    def send_left_command(self):
        self.send_command('$3')

    def send_right_command(self):
        self.send_command('$4')


    def terminate_connection(self):
        self.client_socket.close()
        self.status_label.setText('Connection Status: Terminated')

    def keyPressEvent(self, event):
        # Add the pressed key to the set
        self.keys_pressed.add(event.key())
        self.handle_key_presses()

    def keyReleaseEvent(self, event):
        # Remove the released key from the set
        self.keys_pressed.remove(event.key())
        self.handle_key_presses()

    def handle_key_presses(self):
        # Check for combination of keys and send appropriate commands
        if Qt.Key_Up in self.keys_pressed:
            if Qt.Key_Left in self.keys_pressed:
                self.send_command('$6')  # Forward Left
            elif Qt.Key_Right in self.keys_pressed:
                self.send_command('$5')  # Forward Right
            else:
                self.send_forward_command()
        elif Qt.Key_Down in self.keys_pressed:
            if Qt.Key_Left in self.keys_pressed:
                self.send_command('$8')  # Backward Left
            elif Qt.Key_Right in self.keys_pressed:
                self.send_command('$7')  # Backward Right
            else:
                self.send_backward_command()
        elif Qt.Key_Left in self.keys_pressed:
            self.send_left_command()
        elif Qt.Key_Right in self.keys_pressed:
            self.send_right_command()
    def send_record_command(self):
        self.send_command('$9')
    def send_autoRevert_command(self):
        self.send_command('$10')


if __name__ == '__main__':
    app = QApplication(sys.argv)
    robot_control_app = RobotControlApp()
    robot_control_app.show()
    sys.exit(app.exec_())
    