/**
 * \file TCS34725.cpp
 * \brief  TCS34725 is a class to handle an TAOS TCS34725 color light-to.digital converter with IR filter.
 *
 * \author Marco Boeris Frusca
 *
 */

#include "TCS34725.h"

namespace smrtobj
{

  namespace i2c
  {
  
    TCS34725::TCS34725() : m_clear(0), m_red(0), m_green(0), m_blue(0)
    {
    }
  
    TCS34725::~TCS34725()
    {
    }
  
    TCS34725::TCS34725(const TCS34725 &s) : I2CInterface(s), Sensor(s)
    {
      m_clear = s.m_clear;
      m_red   = s.m_red;
      m_green = s.m_green;
      m_blue  = s.m_blue;
    }
  
    TCS34725 & TCS34725::operator=(const TCS34725 &s)
    {
      I2CInterface::operator=(s);
      Sensor::operator=(s);
  
      m_clear = s.m_clear;
      m_red   = s.m_red;
      m_green = s.m_green;
      m_blue  = s.m_blue;
  
      return (*this);
    }
  
    uint8_t TCS34725::create_command(uint8_t value)
    {
      return value | CMD_BITS;
    }
  
    bool TCS34725::initialize()
    {
      bool ret = true;
  
      for (uint8_t i = 0; i < 4; i++)
      {
        switch (i)
        {
          // RGBC timing is 256 - contents x 2.4mS =
          case 0 : ret = I2Cdev::writeByte(DEVICE_ADDRESS, create_command(ATIME_ADDR), ATIME_VALUE); break;
  
          // Can be used to change the wait time
          case 1 : {
            ret = I2Cdev::writeByte( DEVICE_ADDRESS, create_command(CONFIG_ADDR), 2 ); // sets WLONG to 1
            if ( ret )
            {
              ret = I2Cdev::writeByte(DEVICE_ADDRESS, create_command(WTIME_ADDR), WAIT_TIME_VALUE);
            }
            //ret = I2Cdev::writeByte(DEVICE_ADDRESS, WTIME_ADDR, WAIT_TIME_VALUE);
          }
            break;
  
          // RGBC gain control
          case 2 : ret = I2Cdev::writeByte(DEVICE_ADDRESS, create_command(CONTROL_ADDR), CONTROL_VALUE); break;
  
          // enable ADs and oscillator for sensor
          case 3 : ret = I2Cdev::writeByte(DEVICE_ADDRESS, create_command(ENABLE_ADDR), ENABLE_VALUE); break;
        }
  
        if (!ret)
        {
          return false;
          m_open = false;
        }
      }
  
      m_open = true;
  
      return true;
    }
  
  
    bool TCS34725::isConnected()
    {
      uint8_t r_register = 0;
  
      if ( !I2Cdev::readByte(DEVICE_ADDRESS, create_command(ID_ADDR), &r_register) )
        return false;
  
      if ( r_register == 0x44 )
      {
        return true;
      }
  
      return false;
    }
  
    bool TCS34725::read()
    {
      uint8_t buf[8] = {0};
  
      if ( ! I2Cdev::readBytes(DEVICE_ADDRESS,  create_command(COLOR_ADDR), 8, buf) )
        return false;
  
      m_clear = (uint16_t)(buf[1]<<8) + (uint16_t)buf[0];
      m_red   = (uint16_t)(buf[3]<<8) + (uint16_t)buf[2];
      m_green = (uint16_t)(buf[5]<<8) + (uint16_t)buf[4];
      m_blue  = (uint16_t)(buf[7]<<8) + (uint16_t)buf[6];
  
      return true;
    }
  
    float TCS34725::measure()
    {
  
      float lux = 0;
      float IR = 0;
  
      if (m_clear > 65000)
      {
          lux = 25000;
      }
      else
      {
          IR  = m_red;
          IR += m_green;
          IR += m_blue;
          IR -= m_clear;
          IR /=2;
  
          lux  = R_COEFF*(m_red - IR);
          lux += G_COEFF*(m_green - IR);
          lux += B_COEFF*(m_blue - IR);
          lux /= CPL;
      }
  
      if((lux < 0) && (m_clear < 50)) lux = 0;
  
      return lux;
    };
  
  } /* namespace i2c */
  
} /* namespace smrtobj */
