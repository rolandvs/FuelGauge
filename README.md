# FuelGauge
FuelGauge MAX17043

Credits were credit is due...

Forked from a library made by Luca Dentella (http://www.lucadentella.it)
https://github.com/lucadentella/ArduinoLib_MAX17043.git

Needed a quick setup to evaluate the MAX17043. Used the Sparkfun TOL-10617 breakout:
https://www.sparkfun.com/products/10617 

I modified the breakout to be usable by cutting a track to disconnect the VCC from the cell voltage, 
creating two different power domains. The VCC is connected to the Arduino 3V3.
The I2C bus is connected to the A4 (SDA) and A5 (SCL) ports. As these are open collector there is
no problem regarding the 5V on the Mega328.

Also added sleep() function to the library.

