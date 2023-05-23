# LEDs-motion-sensor-light

In this tutorial I am going to teach you with 2 simple steps, to create an intelligent system that detects the presence to turn on LED lights and turns off automatically with the detection of ambient light or with a timer, all configurable by the user.

## Hardware 
It has been used:
1. 1 LEDs (6m in this case)
2. 1 Arduino Mega 2560 board
3. 2 photoresistors
4. 1 PIR sensor
5. 2 10k ohm resistors
6. 1 IR receiver
7. 1 IR transmitter

## Pinouts
1. Photoresistors for measuring light intensity
![alt text](https://github.com/mksoz/LEDs-motion-sensor-light/blob/main/pngs/photores_pinout.png?raw=true)
2. PIR sensor for motion detection
![alt text](https://github.com/mksoz/LEDs-motion-sensor-light/blob/main/pngs/pir_pinout.png?raw=true)
3. IR transmitter for switching LEDs on and off
![alt text](https://github.com/mksoz/LEDs-motion-sensor-light/blob/main/pngs/transm_pinout.png?raw=true)
4. IR receiver to record code for transmission
![alt text](https://github.com/mksoz/LEDs-motion-sensor-light/blob/main/pngs/rec_pinout.png?raw=true)
## Software editor
Arduino (https://support.arduino.cc/hc/en-us/articles/360019833020-Download-and-install-Arduino-IDE) in this case, but could be others. 

## 1º IR receiver
First, copy and paste the code that captures the LED lights. 
1. Configure the pinout (4) corresponding to the IR receiver.  
2. Set the pin number corresponding to the IRreceiver.ino file to the same pin number you connect to the arduino board.
3. With the remote control of the LED lights, once the code (IRreceiver.ino) is running on the board, press the on/off button of the lights.
4. In the Arduino editor monitor, check the output that prints on the screen. COPY the line that says "this line to transmit IR". This sentence is the one needed by the IR transmitter.

## 2º LEDs state machine
1. Perform pinout (1,2,3) on the same board, taking into account that there are two photoresistors so pinout 1 has to be performed twice. Orient one photoresistor upwards to capture the ambient light and the other one directly to the LED lights to capture their light intensity to monitor their status (on/off).

2. As before, configure in the leds_stateMachine.ino file the pin configuration corresponding to the connections to the Arduino board. Once you have checked all the pins you can reconfigure the LIGHT_MAX and TIMEOUT variables to customise both the minimum light required to detect movement and turn the lights on and the timer to turn them off automatically.

3. PASTE the line from step 1.4 into the sendIR() function.

## Functionality
When the measurement of the photoresistor that detects the ambient light is lower than the maximum light (for the LEDs to light up), the system will detect whether there is any kind of presence or not.
If there is presence, the LEDs will turn on until the timer expires or it detects a light rise above the maximum.

   <img src="https://github.com/mksoz/LEDs-motion-sensor-light/blob/main/pngs/demo1.gif" width="250" height="250"/><img src="https://github.com/mksoz/LEDs-motion-sensor-light/blob/main/pngs/demo2.gif" width="250" height="250"/>


