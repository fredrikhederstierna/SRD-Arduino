/*
 * SRD.cpp - Short Range Devce (SRD) radio module driver - Version 0.1
 *
 * Original library        (0.1)   by Fredrik Hederstierna.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Arduino.h"
#include "SRD.h"
#include <SPI.h>

/*
 * two-wire constructor.
 * Sets which wires should control the motor.
 */
SRD::SRD(int cs_pin)
{
  // Arduino pins for the radio module control connection:
  this->cs_pin = cs_pin;

  // setup the pins on the microcontroller:
  pinMode(this->cs_pin, OUTPUT);

  //SPI initialize
  SPI.begin();
  SPI.setBitOrder(MSBFIRST);
  SPI.setDataMode(SPI_MODE0);
  //That divides the Arduino speed of 16Mhz by 4 to yield 4Mhz for SPI
  SPI.setClockDivider(SPI_CLOCK_DIV4);
}

void SRD::reset(void)
{
  // send reset pulse on CS
  digitalWrite(this->cs_pin, LOW);
  delay(10);
  digitalWrite(this->cs_pin, HIGH);

  // send SRES
  writeRegister(CC1101_SRES | WRITE_SINGLE, 0);
}

//Read from or write to register on SPI
unsigned int SRD::readRegister(unsigned char thisRegister, int bytesToRead)
{
  unsigned char inByte = 0;           // incoming byte from the SPI
  unsigned int result = 0;   // result to return
 
  unsigned char dataToSend = thisRegister;
  
  // take the chip select low to select the device:
  digitalWrite(this->cs_pin, LOW);

  // send the device the register you want to read:
  SPI.transfer(dataToSend);

  // send a value of 0 to read the first byte returned:
  result = SPI.transfer(0x00);
  // decrement the number of bytes left to read:
  bytesToRead--;
  // if you still have another byte to read:
  if (bytesToRead > 0) {
    // shift the first byte left, then get the second byte:
    result = result << 8;
    inByte = SPI.transfer(0x00);
    // combine the byte you just got with the previous one:
    result = result | inByte;
    // decrement the number of bytes left to read:
    bytesToRead--;
  }
  
  // take the chip select high to de-select:
  digitalWrite(this->cs_pin, HIGH);
  
  // return the result:
  return(result);
}

//Sends a write command on SPI
void SRD::writeRegister(unsigned char thisRegister, unsigned char thisValue)
{
  unsigned char dataToSend = thisRegister;
  
  // take the chip select low to select the device:
  digitalWrite(this->cs_pin, LOW);

  SPI.transfer(dataToSend); //Send register location
  SPI.transfer(thisValue);  //Send value to record into register

  // take the chip select high to de-select:
  digitalWrite(this->cs_pin, HIGH);
}

/*
  version() returns the version of the library:
*/
int SRD::version(void)
{
  return 1;
}
