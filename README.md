
# UofG_ENG5220_Team Reverse Assist Car Project

## Team Division of work among project teams

   ### Sohail Jaffer (2946481J) Github - [sohailjaffer](https://github.com/sohailjaffer)
   - Embedded C++ Development for Raspberry Pi
     - GPIO integration
     - Network socket communication
     - Multithreading using pthreads
     - Interrupts and Callbacks
     - Blocking I/O
     - Thread synchronization
     - Server and Client
     - Stub handler for Server and Client
   - Python Development for GUI using QT
   - Design and prototype the hardware components, including selecting appropriate sensors
   - Checking the hardware components to ensure they meet specifications
   - develop a project plan with clear milestones and deadlines.
   - Allocate resources and assign tasks to team members based on their skills and expertise.
   - PCB Design 
   - PCB Assembly 
   - Component sourcing
   - Github maintenance
   - debugging and troubleshooting issues related to hardware-software integration and real-time constraints.
     
     
   ### Muhammed Zeeshan Arif Mistry (2880044m) - [ ZeeshanMistry](https://github.com/ZeeshanMistry)
   - Implement multithreading functionalities to handle concurrent tasks.
   - Integrate interrupt handling mechanisms to respond to external events, such as obstacle detection.
   - Conduct unit testing and debugging to ensure software reliability and real-time responsiveness.
   - Developed Android App
   - Design UI interface
   - Manage Social media pages
   - Manage Github 
   - Develop test plans and test cases
     
   ### YuHsien Huang (2941001H) - [YuhsienHuang](https://github.com/TWKevinHaung)
   - Android App Development 
   - UI interface settings
   - PCB assembly including soldering 
   - Overall wiki website setup
   - C++ Development
   - Manage Github
   - Confirmation of parts and search for materials
   - Parts assembly testing

   ### Ignatius Idro Opi (2805170o) - [ignatiusopi](https://github.com/ignatiusopi)
   - Electronic Schematic Development
   - PCB Design and Fabrication
   - Component Assembly and Testing
   - Multithreading testing
   - Sensor initialisation & configuration



## Overview

Auto Revert X is a project featuring a remote control car outfitted with a PCB housing a Raspberry Pi 3B, battery, IR sensors, and various electrical components. When directional commands (forward, left, right) are issued via software, the car moves accordingly. Upon activating the reverse button in the software, the car retraces its path in reverse, navigating the same route it initially followed.

why do we need Auto Revert X ?

1.Efficiency: It enhances the efficiency of navigation tasks by allowing the car to retrace its path in reverse, saving time and effort.

2.Safety: The inclusion of IR sensors enhances safety by detecting obstacles and avoiding collisions during operation.

3.Convenience: Remote control via software provides convenience, allowing users to maneuver the car from a distance without direct physical interaction.

or some people are just bad at reversing  
Auto Revert X help users who may struggle with the task of reversing a vehicle manually. By automating this process, the project simplifies car navigation for individuals of all skill levels, making it accessible and user-friendly.


The "Auto Revert X" project offers ease of control, enhanced safety with obstacle detection, efficient navigation with the ability to follow a path in reverse


![WhatsApp Image 2024-04-14 at 9 30 25 PM](https://github.com/sohailjaffer/UofG_ENG5220_Team/assets/157168096/4381e930-c2af-47e7-abad-e128019e4615) Follow **[autorevertx](https://www.instagram.com/autorevertx?igsh=c2dwams5d3dtMXIx)** on Instagram for updates and behind-the-scenes content.


## Features
- **Proximity Sensors:** Proximity sensors detect objects by emitting and sensing infrared radiation.
- **Rotary Encoder:** Precise measurement of wheel speed for effective control.
- **Data Logging:** Record and analyze user inputs and wheel speed during forward movement.
- **Reverse Assistance Algorithm:** Intelligent algorithm for safe and reliable reverse navigation.
- **Safety Features:** Collision prevention mechanisms, emergency stops, and obstacle detection.
- **Raspberry Pi Control:** Utilize the Raspberry Pi for overall control and coordination.


## Setup Instructions

### Hardware Requirements

- Raspberry Pi
- Ultrasonic sensors
- Rotary encoder
- Motor control components
- Android smartphone

### Software Requirements

- C++ for Raspberry Pi control
- Android Studio for Java code
- Python 3.7 or above

### Installation Steps

---

## Build Instructions for Raspberry Pi

1. **Clone the repository to your local machine:**
   ```bash
   git clone https://github.com/sohailjaffer/UofG_ENG5220_Team.git
   ```

2. **Navigate to the Project Directory:**
   ```
   cd UofG_ENG5220_Team
   ```

3. **Create a Build Directory:**
   ```
   mkdir build
   cd build
   ```

4. **Configure the Build:**
   ```
   cmake ..
   ```

5. **Build the Project:**
   ```
   make
   ```

6. **Run the Executable:**
   ```
   ./RevAsst_Exec
   ```

---

## Build Instructions for Python Software

To build the software and run the Robot Control application from the provided GitHub repository, follow these instructions:

1. **Clone the Repository:**
   You can clone the repository using the following command:
   ```
   git clone https://github.com/sohailjaffer/UofG_ENG5220_Team.git
   ```

2. **Navigate to the Project Directory:**
   ```
   cd UofG_ENG5220_Team/PC_App
   ```

3. **Install Dependencies:**
   Ensure that you have all the necessary dependencies installed. For Python-based applications, you may need to install PyQt5. You can install it using pip:
   ```
   pip install PyQt5
   ```

4. **Run the Application:**
   Execute the Python script to run the Robot Control application:
   ```
   python3 robot_control.py
   ```
5. **Insert IP address**   To insert the IP address into the code, you need to replace the placeholder `'192.168.1.185'` with the actual IP address of your Raspberry Pi. Here's the command to do that using a text editor like `sed`:

```bash
sed -i 's/192.168.1.185/YOUR_IP_ADDRESS_HERE/g' robot_control.py
```

Replace `YOUR_IP_ADDRESS_HERE` with the actual IP address of your Raspberry Pi. This command will replace all occurrences of `'192.168.1.185'` in the `robot_control.py` file with your specified IP address.

6. **Interact with the Application:**
   Once the application window opens, you can use the buttons to control the robot. Press the buttons for Forward, Backward, Left, Right, Terminate Connection, Start Recording, and AutoRevert to send commands to the robot via the established socket connection.

7. **Terminate the Connection:**
   To terminate the connection with the robot, click the "Terminate Connection" button.

8. **Close the Application:**
   Close the application window when finished controlling the robot.


Ensure that you have Python installed on your system, along with the necessary libraries mentioned in the `robot_control.py` script.


## Connect with us

- Instagram: [AutoRevertX](https://www.instagram.com/autorevertx?igsh=emI1YWtha2IzMGc=)
- Notion: [Project Documentation](https://www.notion.so/5d96ad462e65456998ebed42c4b62a22?v=ffb782b28924440680d9ac9bcb223597&pvs=4)
- Youtube: [Explanation](https://www.youtube.com/channel/UCore7Hp1O_CoWI1DSHmuozg)



## Credits

This project utilizes the following libraries and tools:

- [realtime_cpp_coding](https://github.com/berndporr/realtime_cpp_coding) repository by Bernd Porr. The repository provides valuable resources for real-time C++ programming.

- [pigpio](https://github.com/joan2937/pigpio): A library for the Raspberry Pi GPIO interface, used for controlling GPIO pins.

- [sockets-ccpp-rpi](https://github.com/Mad-Scientist-Monkey/sockets-ccpp-rpi) repository by Mad-Scientist-Monkey for socket communication between C++ programs on Raspberry Pi 3B.

