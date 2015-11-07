/**
 * Demo program for MAX17043 Battery Gauge
 * 
 * Based on the demo program of Luca Dentella (http://www.lucadentella.it):
 * https://github.com/lucadentella/ArduinoLib_MAX17043.git
 * 
 * Needed a quick setup to evaluate the MAX17043. Used the Sparkfun TOL-10617 breakout:
 * https://www.sparkfun.com/products/10617 
 *
 * I modified the breakout to be usable by cutting a track to disconnect the VCC from the cell voltage,
 * creating two different power domains. The VCC is connected to the Arduino 3V3.
 * The I2C bus is connected to the A4 (SDA) and A5 (SCL) ports. As these are open collector there is
 * no problem regarding the 5V on the Mega328.
 * 
 * Also added sleep() function to the library.
 *
 * Date   : 05-11-2015
 * Author : Roland van Straten, roland@van-straten.org
 *
 */

#define ARDUINO_UNO

#include <MAX17043.h>
#include "Wire.h"

const int LED = 13;

// variables
//
MAX17043 batteryMonitor;

float cellVoltage;
float stateOfCharge;


/**
 *
 */
void setup() {
  pinMode(LED, OUTPUT);   // set the LED

  Wire.begin();           // I2C
  Serial.begin(9600);     // UART
  Serial.println("Fuel Gauge MAX17043 test program.");

  batteryMonitor.reset();
  batteryMonitor.quickStart();
  delay(1000);            // give it time to think

  Serial.print("Version:\t\t");               Serial.println(batteryMonitor.getVersion());
  Serial.print("Compensate value:\t0x");      Serial.println(batteryMonitor.getCompensateValue(), HEX);
  Serial.print("Alert treshold:\t\t");        Serial.print(batteryMonitor.getAlertThreshold()); Serial.println("%");
  Serial.print("Default alert treshold:\t");  Serial.print(batteryMonitor.getAlertThreshold()); Serial.println("%");

  batteryMonitor.setAlertThreshold(25);
  Serial.print("Actual alert treshold:\t");   Serial.print(batteryMonitor.getAlertThreshold()); Serial.println("%");

  gaugeMenu();
  
} // setup()


/**
 *  Display menu
 */
void gaugeMenu(void) {
  Serial.println();
  Serial.println("Please select function:");
  Serial.println(" s - Sleep");
  Serial.println(" w - Wakeup");
  Serial.println(" v - Show Cell Voltage");
  Serial.println(" c - Show State of Charge");
  Serial.println(" a - Show Alert Level");
  Serial.println(" A - Set Alert Level");
  Serial.println(" p - Show Compensation Value");
  Serial.println(" P - Set Compensation Value");
  Serial.println(" l - Start Logging");
  Serial.println(" r - Reset Gauge");
  Serial.println(" i - Blink");
}


/**
 *  main event loop - nothn gfancy, just something to do a quick evaluation
 */
void loop() {

  // read from the serial input
  if (Serial.available() > 0) {
    // get a command
    int inByte = Serial.read();
    switch (inByte) {

      
      case 's':
        batteryMonitor.setSleep();
        Serial.println("Put the chip into sleepmode.");
    break;
      case 'w':
       batteryMonitor.setSleep();
       Serial.println("Put the chip into sleepmode.");
      break;
      case 'v': // Cell Voltage
        cellVoltage = batteryMonitor.getVCell();
        Serial.print("Voltage:\t\t"); Serial.print(cellVoltage, 4); Serial.println("V");
        break;

      case 'c': // SOC
        stateOfCharge = batteryMonitor.getSoC();
        Serial.print("State of charge:\t"); Serial.print(stateOfCharge); Serial.println("%");
        break;

      case 'a': // alert threshold
        Serial.print("Alert threshold level:\t"); Serial.print(batteryMonitor.getAlertThreshold()); Serial.println("%");
        break;

      case 'A': // set alert level
        Serial.println("Not implemented.");
        break;

      case 'p': // show compensation value
        Serial.print("Compensation value:\t"); Serial.println(batteryMonitor.getCompensateValue());
        break;

      case 'P': // set compensation value
        Serial.println("Not implemented.");
        break;

      case 'l': // logging
        Serial.println("Starting logging, enter any key to exit.");
        
        while( !Serial.available() ) {
          Serial.print(batteryMonitor.getVCell(), 3);   Serial.print("V;");
          Serial.print(batteryMonitor.getSoC(), 0);     Serial.println("%");
          delay(2000);
        }
        break;

      case 'r': // reset the gauge
        batteryMonitor.reset();
        batteryMonitor.quickStart();
        Serial.println("Reset the gauge.");
        break;

      case 'i': // blink the LED
        digitalWrite(LED, HIGH);
        delay(100);
        digitalWrite(LED, LOW);
        break;

      default:
        gaugeMenu();
        break;
    } //switch
  }
}

