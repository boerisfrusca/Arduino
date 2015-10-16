/**
 * \file i2cinterface.cpp
 * \brief  I2CInterface is an interface to model an I2C device.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "interfaces/i2cinterface.h"

namespace smrtobj
{

  I2CInterface::I2CInterface() : m_device_addr(0)
  {
    m_type = TYPE_BIDIRECTIONAL;
  }

  I2CInterface::I2CInterface(uint8_t addr) : m_device_addr(addr)
  {
    m_type = TYPE_BIDIRECTIONAL;
  }

  I2CInterface::I2CInterface(const I2CInterface &d)
  {
    m_type = d.m_type;
    m_device_addr = d.m_device_addr;
  }

  I2CInterface::~I2CInterface()
  {
  }

  I2CInterface & I2CInterface::operator=(const I2CInterface &d)
  {
    Signal::operator=(d);
    m_type = d.m_type;
    m_device_addr = d.m_device_addr;

    return (*this);
  }


   int8_t I2CInterface::readAllBytes(uint8_t devAddr, uint8_t length, uint8_t *data, uint16_t timeout) {
   #ifdef I2CDEV_SERIAL_DEBUG
       Serial.print( F(" I2C (0x") );
       Serial.print(devAddr, HEX);
       Serial.print( F(") reading ") );
       Serial.print(length, DEC);
       Serial.print( F(" bytes...") );
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
       Serial.print( F(". Done (") );
       Serial.print(count, DEC);
       Serial.println( F(" read)." ) );
   #endif

       return count;
   }

   bool I2CInterface::read_word(uint16_t &value, bool MSB) {
     uint8_t buffer[2] = {0};
     // read bytes from the DATA1 AND DATA2 registers and bit-shifting them into a 16-bit value
     uint8_t rb = readAllBytes(m_device_addr, 2, buffer);
     if (MSB)
       value = (buffer[0] << 8) | buffer[1];
     else
       value = (buffer[1] << 8) | buffer[0];

     return rb > 0;
   }

} /* namespace smrtobj */
