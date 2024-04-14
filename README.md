Follow us on Instagram : https://www.instagram.com/autorevertx?igsh=emI1YWtha2IzMGc=

# UofG_ENG5220_Team Reverse Assist Car Project

## Team Division of work among project teams
   ### YuHsien Huang (2941001H)
   - Android studio website coding
   - UI interface settings
   - Product assembly welding
   - Overall wiki website setup
   - C++ language programming
## Sohail Jaffer (2946481j) Github - sohailjaffer
   - Embedded C++ Development for Raspberry Pi
   - Python Development for GUI using QT
   - PCB Design 
   - PCB Assembly 
   - Component sourcing

## Overview

Auto Revert X is a project featuring a remote control car outfitted with a PCB housing a Raspberry Pi 4, battery, IR sensors, and various electrical components. When directional commands (forward, left, right) are issued via software, the car moves accordingly. Upon activating the reverse button in the software, the car retraces its path in reverse, navigating the same route it initially followed.

why do we need Auto Revert X ?

1.Efficiency: It enhances the efficiency of navigation tasks by allowing the car to retrace its path in reverse, saving time and effort.

2.Safety: The inclusion of IR sensors enhances safety by detecting obstacles and avoiding collisions during operation.

3.Convenience: Remote control via software provides convenience, allowing users to maneuver the car from a distance without direct physical interaction.



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

## Build Instructions

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













## Credits

This project utilizes the following libraries and tools:

- [pigpio](https://github.com/joan2937/pigpio): A library for the Raspberry Pi GPIO interface, used for controlling GPIO pins.

