# esp32-rc-car

## Overview
The **esp32-rc-car** is a custom-built RC car controlled via Bluetooth Low Energy (BLE) using an ESP32 microcontroller. The vehicle is operated from a smartphone through the Dabble app, which provides a virtual game controller interface. The project combines embedded programming, custom PCB design, motor control, and hardware debugging.

---

## Project Media
<p align="center">
  <img src="media/esp32_rc_car_front_view.png" height="400" />
  <img src="media/esp32_rc_car_top_view.png" height="400" />
</p>
▶ Watch the ESP32 RC Car features showcase: https://youtube.com/shorts/to-kIwxq354?si=jSNwVrnpMwx3RoQd 

▶ Watch the full demo video of the ESP32 RC Car: https://youtube.com/shorts/JepBfLC0xiw?si=qRIe9IqqiM_V_Yjg

---

## Features
- BLE-based wireless control using the ESP32
- Smartphone control via the Dabble app game controller
- Start/Stop system similar to a real car ignition
- DC motor for forward and reverse motion
- Servo motor for left and right steering
- Front headlights and rear taillights
- Direction-based lighting:
  - Front LEDs activate when moving forward
  - Rear LEDs activate when reversing
- Turn signals and hazard lights with dedicated controls
- Horn functionality using a speaker
- Visual feedback (LED blinking) when starting/stopping the car

---

## Control System
- The ESP32 uses its built-in **Bluetooth Low Energy (BLE)** to communicate with a smartphone.
- The **Dabble mobile app** provides a game controller interface.
- Button presses in the app are mapped in the Arduino IDE to ESP32 GPIO pins.
- GPIO pins control:
  - DC motor
  - Servo motor
  - LEDs
  - Speaker (horn)

---

## Hardware Components
- ESP32 development board
- DC motor (rear-wheel drive)
- Servo motor (front-wheel steering)
- DRV8833 motor driver
- Speaker (horn)
- 4 LEDs:
  - 2 front headlights
  - 2 rear taillights
- Custom-designed PCB
- Power switch
- 3.7V 1100mAh Li-Po battery
- 6V 2400mAh Ni-MH battery pack

---

## Power Architecture
- **Dual power supply design**:
  - **Li-Po battery** powers the ESP32
    - Includes a physical switch to turn the system on/off
  - **Ni-MH battery pack** powers:
    - DC motor
    - Servo motor
    - LEDs
    - Speaker
- Power distribution for peripherals is handled directly on the custom PCB.

---

## PCB Design
- Custom PCB designed using **Autodesk Eagle**
- Fully **through-hole components**
- ESP32 is mounted using **headers** (not soldered directly)
- Designed for easy debugging, modification, and component replacement
- Initial motor driver (L293D) was replaced with a **DRV8833** after testing revealed insufficient motor drive strength

---

## Software & Tools
- Arduino IDE (ESP32 programming)
- Dabble mobile app (BLE controller interface)
- Autodesk Eagle (PCB design)
- Tinkercad (circuit simulation and early testing)
- Multimeter (circuit testing and debugging)

---

## Development & Debugging
- The circuit was first simulated and tested in **Tinkercad** to verify connections, motor control, and LED functionality before creating the custom PCB.  
- Multiple iterations were required to validate motor control and power delivery.  
- Problems encountered and solved:
  - Motor driver (L293D) was too weak → replaced with DRV8833
  - Front wheels initially had too much friction → wrapped tires in tape to reduce friction and allow smooth steering
  - Servo motor was not strong enough initially → adjustments made to wheel friction for smooth turning  
- Circuit simulation, real-world testing, and incremental debugging ensured reliable operation.

---

## Skills Demonstrated
- ESP32 programming and BLE integration
- Custom PCB design and layout
- Through-hole soldering and hardware assembly
- Motor driver integration and control
- Dual power supply management
- Circuit testing and debugging
- Embedded system troubleshooting
- Hardware problem solving and iterative design improvements

## Future Improvements
- Integrate motor driver directly onto PCB
- Add battery voltage monitoring
- better cable management and enclosed design
