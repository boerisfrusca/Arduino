/**
 * \file T6713.cpp
 * \brief  T6713 is a class to handle an I2C Co2 meter.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "T6713.h"
  
namespace smrtobj
{
  
  namespace i2c
  {
  
    T6713::T6713() : m_register(0)
    {
      setDeviceAddress(DEVICE_ADDRESS);
    }
  
    T6713::T6713(const T6713 &d) : I2CInterface(d), Sensor(d)
    {
      m_register = d.m_register;
    }
  
    T6713::~T6713()
    {
    }
  
    T6713 & T6713::operator=(const T6713 &s)
    {
      I2CInterface::operator=(s);
      Sensor::operator=(s);
  
      m_register = s.m_register;
  
      return (*this);
    }
  
  
    bool T6713::initialize() {
        // Nothing is required, but
        // the method should exist anyway.
      return true;
    }
  
    bool T6713::isConnected()
    {
      if ( read(GAS_PPM) )
      {
        return true;
      }
      return false;
    }
  
    bool T6713::read(uint16_t cmd)
    {
      uint16_t c = cmd;

//      Serial.println(c, HEX);
      switch (cmd)
      {
        case FIRMWARE :
        case STATUS :
        case GAS_PPM : {
          uint8_t buf_in[5] = {0};
          uint8_t buf_out[4] = {0};
          buf_in[0] = FUNCTION_READ;
          buf_in[2] = c;
          buf_in[2] &= 0x0FF;
          c >>= 8;
          buf_in[1] = c;
          buf_in[1] &= 0x0FF;
          buf_in[3] = 0x00;
          buf_in[4] = 0x01;
/*
          for (uint8_t i = 0; i < 5; i++)
          {
            Serial.println(buf_in[i], HEX);
          }
*/
          if ( !writeAllBytes(address(), 5, buf_in, 0) )
            return false;

//          Serial.println( F("Read response"));
          if ( readAllBytes(address(), 4,buf_out, 0) != 4 )
            return false;
//          Serial.println( F("Process response"));

          bool valid = true;
          for (uint8_t index = 0; index < 4; index++)
          {
/*
            Serial.print( index );
            Serial.print( F(" : "));
            Serial.println( buf_out[index] );
            Serial.println( valid);
*/
            switch (index)
            {
              case 0 : {
                if ( buf_out[index] != 0x04 )
                {
                  valid = false;
                }
              } break;
              case 1 : {
                if ( buf_out[index] != 0x02 )
                {
                  valid = false;
                }
              }break;
              case 2 : { m_register = buf_out[index]; m_register <<= 8; } break;
              case 3 : { m_register += (uint16_t) (buf_out[index] & 0x0FF) ; } break;
              default :
               valid = false;
            }
          }

//          Serial.println( valid);
          if (!valid)
            return false;


        } break;
        default :
          return false;
      }
      return true;
    }

    bool T6713::read()
    {
      return read(GAS_PPM);
    }

    bool T6713::readStatus()
    {
      return read(STATUS);
    }

  
    float T6713::measure()
    {
      return (float) m_register;
    }
  
  } /* namespace i2c */

} /* namespace smrtobj */
  
