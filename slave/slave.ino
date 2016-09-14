/*
  Modbus-Arduino Example - Lamp (Modbus IP)
  Copyright by André Sarmento Barbosa
  http://github.com/andresarmento/modbus-arduino
*/
 
#include <SPI.h>
#include <Ethernet.h>
#include "Modbus.h"
#include "ModbusIP.h"

//Modbus Registers Offsets (0-9999)
const int LAMP1_COIL = 100;
const int LAMP2_COIL = 200; 
//Used Pins
const int ledPin1 = 8;
const int ledPin2 = 9;

//ModbusIP object
ModbusIP mb;

void setup() {
    // The media access control (ethernet hardware) address for the shield
    byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
    // The IP address for the shield
    byte ip[] = { 192, 168, 0, 200 };   
    //Config Modbus IP 
    mb.config(mac, ip);
    //Set ledPin mode
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    // Add LAMP1_COIL register - Use addCoil() for digital outputs
    mb.addCoil(LAMP1_COIL);
    mb.addCoil(LAMP2_COIL);

    mb.addCoil(101, false);
    mb.addCoil(102, false);
    mb.addCoil(103, true);
    mb.addCoil(104, true);
    mb.addCoil(105, false);
}

void loop() {
   //Call once inside loop() - all magic here
   mb.task();
   
   //Attach ledPin to LAMP1_COIL register     
   digitalWrite(ledPin1, mb.Coil(LAMP1_COIL));
   digitalWrite(ledPin2, mb.Coil(LAMP2_COIL));
}
