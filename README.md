# IoT Smart Kitchen
  A smart kitchen is defined as an area composed of kitchen equipment that is connected via Wi-Fi or Bluetooth. The equipment found in smart kitchens connects to other tech such as your phone or tablet, allowing you to control appliances remotely.
  
## Sensors Used
  - Arduino (NodeMCU32): NodeMCU is a low-cost open source IoT platform. It initially included firmware which runs on the ESP8266 Wi-Fi SoC from Espressif Systems, and hardware which was based on the ESP-12 module. Later, support for the ESP32 32-bit MCU was added.
    <br> <img src="https://user-images.githubusercontent.com/72027411/211216615-cd1a5596-9174-443e-8753-99af3d9abbe0.jpg" width="110" height="100">
  - PIR Motion Sensor: Passive infrared (PIR) sensors use a pair of pyroelectric sensors to detect heat energy in the surrounding environment. These two sensors sit beside each other, and when the signal differential between the two sensors changes, the sensor will engage.
    <br> <img src="https://user-images.githubusercontent.com/72027411/211212471-50341164-56c7-491c-8ea1-309f7e1d93a6.jpg" width="110" height="100">
  - Bulb: Lights on and off.
    <br> <img src="https://user-images.githubusercontent.com/72027411/211212492-8c49b6f3-6a92-4798-b2bd-b7157ad147d5.jpg" width="110" height="100">
  - Air Quality Sensor (MQ-135): The gas sensor module consists of a steel exoskeleton under which a sensing element is housed. This sensing element is subjected to    current through connecting leads. This current is known as heating current through it, the gases coming close to the sensing element get ionized and are absorbed by the sensing element. 
    <br> <img src="https://user-images.githubusercontent.com/72027411/211212487-d883dd8d-f80c-4902-8985-c293630f2153.jpg" width="110" height="100">
  - Buzzer: The flexible ferromagnetic disk is attracted to the coil when the magnetic field is activated, then returns to rest when the magnetic field is off. By oscillating the signal through the coil, the buzzer produces a fluctuating magnetic field, which vibrates the disk. This movement makes the buzzer sound.
    <br> <img src="https://user-images.githubusercontent.com/72027411/211212502-3d92abbe-0f13-42a0-acff-27a8c9bad98c.jpg" width="110" height="100">   
  - Temperature & Humidity Sensor: Humidity sensors work by detecting changes that alter electrical currents or temperature in the air. There are three basic types of humidity sensors: capacitive, resistive and thermal. All three types will monitor minute changes in the atmosphere in order to calculate the humidity in the air.
    <br> <img src="https://user-images.githubusercontent.com/72027411/211212473-0d4b7ab9-c83b-475b-9664-1e1d45b2b85f.png" width="110" height="100">
    
## Working
  - Temperature and Humidity sensor is used to display to the current temperature and humidity of the surrounding. 
  - The PIR Motion sensor is used to sense the entry of someone and turn on the lights.
  - MQ-135 sensor detect the leakage of LPG and warns the residents by turning on the buzzer.
