/**
 * \file HIH7121.cpp
 * \brief  HIH7121 is a class to handle an I2C HIH7121 relative humidity/temperature sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "HIH7121.h"

namespace smrtobj
{

  namespace i2c
  {

    HIH7121::HIH7121() : m_status(0), m_humidity(0), m_temperature(0)
    {
      setDeviceAddress(DEVICE_ADDRESS);
    }

    HIH7121::HIH7121(uint8_t addr) : m_status(0), m_humidity(0), m_temperature(0)
    {
      setDeviceAddress(addr);
    }

    HIH7121::HIH7121(const HIH7121 &d) : I2CInterface(d), Sensor(d)
    {
      m_status = d.m_status;
      m_humidity = d.m_humidity;
      m_temperature = d.m_temperature;

    }

    HIH7121::~HIH7121()
    {
    }

    HIH7121 & HIH7121::operator=(const HIH7121 &d)
    {
      I2CInterface::operator=(d);
      Sensor::operator=(d);

      m_status = d.m_status;
      m_humidity = d.m_humidity;
      m_temperature = d.m_temperature;

      return (*this);
    }

    bool HIH7121::initialize()
    {
        // Nothing is required, but
        // the method should exist anyway.
      return true;
    }

    bool HIH7121::isConnected()
    {
      if ( read() )
      {
        return true;
      }
      return false;
    }

    bool HIH7121::read()
    {
      uint8_t buf[4] = {0};

      if ( readAllBytes(address(), 4, buf, 0) != 4 )
        return false;

      bool valid = true;

      for (uint8_t index = 0; index < 4; index++)
      {

        switch (index)
        {
          case 0 : {
            uint8_t m_status = buf[index] >> 6;
            m_status &=0x03;

            m_humidity = buf[index];
            m_humidity &=0x3F;
            m_humidity <<=8;
            m_humidity &= 0xFF00;
          } break;

          case 1 : {
            m_humidity |= buf[index];

          } break;

          case 2 : {
            m_temperature = buf[index];
            m_temperature <<=8;
            m_temperature &= 0xFF00;
          } break;

          case 3 : {
            m_temperature |= buf[index];
            m_temperature >>= 2;
            m_temperature &= 0x3FFF;

          } break;

          default :
           valid = false;
        }
      }

      if ( !valid )
        return false;

      return true;
    }

    uint8_t HIH7121::status()
    {
      return m_status;
    }

    float  HIH7121::humidity()
    {
      float value = m_humidity;
      value /= 16382;
      value *= 100;

      return value;
    }

    float  HIH7121::temperature()
    {
      float value = m_temperature;
      value /=16382;
      value *= 165;
      value -= 40;

      return value;
    }

    float HIH7121::measure()
    {
      return humidity();
    }
  } /* namespace i2c */

} /* namespace smrtobj */
