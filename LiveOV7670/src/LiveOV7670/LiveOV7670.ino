

/*
 Connections for Arduino Mega
OV7670 connections:

VSYNC - PIN2
XCLCK - PIN9 (must be level shifted from 5V -> 3.3V)
PCLCK - PIN12
SIOD - PIN20-SDA (I2C data) - 10K resistor to 3.3V
SIOC - PIN21-SCL (I2C clock) - 10K resistor to 3.3V
D0..D7 - PIN22..PIN29 (pixel data bits 0..7)
3.3V - 3.3V
RESET - 3.3V
GND - GND
PWDN - GND
 */


// change setup.h to switch between buffered and pixel-by-pixel processing
#include "setup.h"



void setup() {
  // This is not necessary and has no effect for ATMEGA based Arduinos.
  // WAVGAT Nano has slower clock rate by default. We want to reset it to maximum speed
  CLKPR = 0x80; // enter clock rate change mode
  CLKPR = 0; // set prescaler to 0. WAVGAT MCU has it 3 by default.

  initializeScreenAndCamera();
}


void loop() {
  processFrame();
}
