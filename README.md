Arduino Bluetooth example 2
===========================
This is **not** a standalone repo. Please refer to my [first example repo](https://github.com/TravelingTechGuy/Arduino-Bluetooth2) for the sketch, components, and details.

This is a necessary step on the road to understanding spoken commands. The Arduino can now respond to the following commands over Bluetooth:

+ Red On/Off - toggle red LED
+ Green On/Off - toggle green LED
+ Both On/Off - toggle both LEDs
+ Status - show indvidual LED status
+ ?/help - this help

Commands are case insensitive. Error handling is minimal (I'm plannining to handle it on the client side).

Next step
---------
I'm working on an Android client app, that will receive spoken commands, convert them to the command mentioned above, and will allow voice control of the LEDs.

After that, I can connect more complex stuff to the Arduino (I have a quad copter lying around somewhere :)).
