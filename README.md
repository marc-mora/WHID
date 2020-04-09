# WHID
Wireless Keyboard &amp; Mouse usb

Requirements:
* Arduino or atmega 32u4.
* ESP12

Based on the operation of ruberducky of injection of code through a usb, wifi has been added to use it as a mouse and keyboard in physical usb format and writing via wifi.

The esp-whid code will go on the esp12 device and the arduino-whid code on the arduino or atmega device.

Communication between the two devices is through a serial port.
ESP12 -> Arduino -> HostPC.

Once the esp12 is connected, it will create a wifi ap called WHID and with the password "Keyboard" we can connect from a mobile phone or any wifi device that can visit a web page.

At the address 192.168.4.1 we will get the interface to send the keyboard and mouse functions.

To compile the esp program the following libraries will be necessary:
* ESP8266WiFi.h
* WiFiClient.h
* ESP8266WebServer.h
* WebSocketsServer.h  https://github.com/Links2004/arduinoWebSockets
* ESP8266mDNS.h

The following libraries will be necessary for the atmega program:
* Keyboard.h
* Mouse.h

Keep in mind that since it is a project that uses the Keyboard.h library and is intended in Spanish, we must add the layouts for that language.
These are available in the keyboard / src folder.

Steps to follow for installation on a CactusWhid device:

1-Load with the Arduino IDE the program called ESP_Programmer located in the tools folder.
2.Once the programmer is loaded we can generate a binary of the ESP-WHID program or use the one that exists in the tools folder. We will load it using the ESP8266Flasher.exe tool.
3-Once the previous step has been successfully carried out, we can directly load the arduino_WHID program through the Arduino IDE.

Contact
Please file bug reports and feature requests at https://github.com/marc-mora/whid/issues

In case of Pull Requests, please make sure to submit them to a develop branch of this repository.
