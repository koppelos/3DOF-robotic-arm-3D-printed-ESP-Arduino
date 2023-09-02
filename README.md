The subject of the project is a robotic arm made using 3D printing technology.

The project involves modelling the components of the robotic arm in the chosen CAD environment with a .stl extension. They are then printed and assembled. The robot is controlled using an ESP32 microcontroller, and control tasks were broadcast to the microcontroller via USB to UART communication, using a CP210x controller and Arduino IDE programming software. In the structure of the whole application, the following were used to perform the displacement: -28BYJ-48 stepper motors -Servo-mechanism SG90 (which operates the gripper) -WK621 limit switches Communication of the electronic components is carried out via connection cables. The power supply operating the robot is a 230V mains supply.

The underlying assumption of the project is to be able to simulate the operation of an arm with 3 degrees of freedom. So that by observing a smaller scale system, a larger scale application could be realised. In the case of robot control, two types of arm control were realised. These are manual and software control. In the case of manual control, the ESP32's built-in Bluetooth module was used to allow the platform to communicate with an external controller with a Bluetooth module - in this case the DualShock3. In order for communication to be established and individual tasks to be assigned to specific controller buttons, it is necessary to use the dedicated Ps3Controller library. Bluetooth communication is established based on the MAC address of the DualShock3 device. Discovering or changing the physical address of the device is possible using the SixAxisPairTool software.

In the case of software control, the movement of the arm to the selected position was realised using an inverse kinematics task. As part of the application development, a simple kinematics task was also tested. Both straight and inverse kinematics tasks were solved using a geometrical method based on the actual dimensions of the printed arms.

The robot was placed on a stable platform and which exceeded the reach of its total workspace in size, this was necessary in order to correctly perform arm movements. The robot application is equipped with a controlled gripper that allows the handling of low-weight objects. A programme was therefore written to move the given object from its initial position (POS1) to its final position (POS2). The description of the object in space was realised by defining the position of the object in Cartesian space operating on three space vectors (x,y,z). The calculation of the inverse kinematics tasks for the given values required starting the displacement according to the defined start position to the given positions. For this purpose, limit switches were used, which are responsible for correcting the arm alignment to this start position.

The arm movements were realised using stepper motors; the corresponding values calculated by the kinematics tasks were transformed into the selected number of steps and the direction of the motor shaft travel. The AccelStepper and Stepper libraries were used to implement these tasks. The servo is controlled via the standard Servo library.

In order to test the scope of the workspace, a visualisation script was realised in Matlab, showing possible displacement configurations in both 2D and 3D planes.

![image](https://github.com/koppelos/3DOF-robotic-arm-3D-printed-ESP-Arduino/assets/48089897/038ef9a7-d98c-44e9-8a94-3e424606ad71)
Electronic modules connection scheme


![image](https://github.com/koppelos/3DOF-robotic-arm-3D-printed-ESP-Arduino/assets/48089897/20842ebe-4304-46fe-b895-7d75f704a5c2)
3D workspace of manipulator - Matlab R2023 simulation

