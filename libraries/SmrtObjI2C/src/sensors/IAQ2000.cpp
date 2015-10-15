/*
 * IAQ2000.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: boeris
 */

#include "IAQ2000.h"

namespace smrtobj
{

  IAQ2000::IAQ2000() : m_value(0)
  {
  }

  IAQ2000::IAQ2000(const IAQ2000 &s) : I2CInterface(s)
  {
    m_value = s.m_value;
  }

  IAQ2000::~IAQ2000()
  {
  }

  IAQ2000 & IAQ2000::operator=(const IAQ2000 &s)
  {
    I2CInterface::operator=(s);

    m_value = s.m_value;

    return (*this);
  }

  /** Power on and prepare for general usage.
   */
  bool IAQ2000::initialize() {
      // Nothing is required, but
      // the method should exist anyway.
    return true;
  }

  /** Very primitive method o verify the I2C connection.
   * Make sure the device is connected and responds as expected.
   * @return True if connection is valid, false otherwise
   */
  bool IAQ2000::testConnection()
  {
    if ( read() )
    {
      if (m_value >= 450)
      {
          return true;
      }
    }
    return false;
  }


  /** Read iAQ-2000 indoor air quality sensor.
   * @return Predicted CO2 concentration based on human induced volatile organic compounds (VOC) detection (in ppm VOC + CO2 equivalents)
   */
  bool IAQ2000::read() {
    uint8_t buffer[2] = {0};
    // read bytes from the DATA1 AND DATA2 registers and bit-shifting them into a 16-bit value
    uint8_t rb = readAllBytes(DEVICE_ADDRESS, 2, buffer);
    m_value = (buffer[0] << 8) | buffer[1];
    return rb > 0;
  }

  float IAQ2000::measure()
  {
   return (float) m_value;
  }

  /**  Read bytes from a slave device.
   * This is a "stripped-down" version of the standard Jeff Rowberg's I2Cdev::readBytes method
   * intended to provide compatibility with iAQ-2000,
   * which apparently does not support setting of an address pointer to indicate from which position is to start read from.
   * @param devAddr Address of the slave device to read bytes from
   * @param length Number of bytes to read
   * @param data Buffer to store read data in
   * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
   * @return Number of bytes read (0 indicates failure)
   */
  int8_t IAQ2000::readAllBytes(uint8_t devAddr, uint8_t length, uint8_t *data, uint16_t timeout) {
  #ifdef I2CDEV_SERIAL_DEBUG
      Serial.print("I2C (0x");
      Serial.print(devAddr, HEX);
      Serial.print(") reading ");
      Serial.print(length, DEC);
      Serial.print(" bytes...");
  #endif

      int8_t count = 0;

      Wire.requestFrom(devAddr, length);

      uint32_t t1 = millis();
      for (; Wire.available() && (timeout == 0 || millis() - t1 < timeout); count++) {
  #if ((I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE && ARDUINO < 100) || I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_NBWIRE)
          data[count] = Wire.receive();
  #elif (I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE && ARDUINO >= 100)
          data[count] = Wire.read();
  #endif
  #ifdef I2CDEV_SERIAL_DEBUG
          Serial.print(data[count], HEX);
          if (count + 1 < length) Serial.print(" ");
  #endif
      }
      if (timeout > 0 && millis() - t1 >= timeout && count < length) count = -1; // timeout

  #ifdef I2CDEV_SERIAL_DEBUG
      Serial.print(". Done (");
      Serial.print(count, DEC);
      Serial.println(" read).");
  #endif

      return count;
  }

} /* namespace smrtobj */
