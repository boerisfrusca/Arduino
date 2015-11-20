/*
 * IAQ2000.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: boeris
 */
/**
 * \file IAQ2000.cpp
 * \brief  IAQ2000 is a class to handle an iAQ-2000 Indoor Air Quality (VOC) Sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "IAQ2000.h"

namespace smrtobj
{

  namespace i2c
  {
   
    IAQ2000::IAQ2000() : m_value(0), m_status(0), m_resistance(0), m_tvoc(0)
    {
      setDeviceAddress(DEVICE_ADDRESS);
    }
  
    IAQ2000::IAQ2000(const IAQ2000 &s) : I2CInterface(s), Sensor(s)
    {
      m_value = s.m_value;
      m_status = s.m_status;
      m_resistance = s.m_resistance;
      m_tvoc = s.m_tvoc;
    }
  
    IAQ2000::~IAQ2000()
    {
    }
  
    IAQ2000 & IAQ2000::operator=(const IAQ2000 &s)
    {
      I2CInterface::operator=(s);
      Sensor::operator=(s);
  
      m_value = s.m_value;
      m_status = s.m_status;
      m_resistance = s.m_resistance;
      m_tvoc = s.m_tvoc;

      return (*this);
    }
  
    bool IAQ2000::initialize() {
        // Nothing is required, but
        // the method should exist anyway.
      return true;
    }
  
    bool IAQ2000::isConnected()
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
  
    bool IAQ2000::read() {
      uint8_t buf[9] = {0};

       if ( readAllBytes(address(), 9, buf, 0) != 9 )
         return false;

       bool valid = true;
       m_value = 0;
       m_resistance = 0;
       m_tvoc = 0;


       for (uint8_t index = 0; index < 9; index++)
       {
         switch (index)
         {
           case 0 :
           case 1 : {
             m_value <<= 8;
             m_value |= buf[index];
           }
           break;

           case 2 : {
             m_status = buf[index];
           }
           break;

           case 3 :
           case 4 :
           case 5 :
           case 6 : {
             m_resistance <<= 8;
             m_resistance |= buf[index];
           }
           break;

           case 7 :
           case 8 : {
             m_tvoc <<= 8;
             m_tvoc |= buf[index];
           }
           break;
         }
         /*
         Serial.print( F( "[" ) );
         Serial.print( index );
         Serial.print( F( "] : " ) );
         Serial.println( buf[index] , HEX );
         */
       }
       /*
       Serial.print( F("PPM : ") );
       Serial.println( m_value );

       Serial.print( F("Status : ") );
       Serial.println( m_status);

       Serial.print( F("Resistance : ") );
       Serial.println( m_resistance );

       Serial.print( F("tvoc : ") );
       Serial.println( m_tvoc );
       */
       return true;
      //return read_word(m_value);
    }
  
    float IAQ2000::measure()
    {
     return (float) m_value;
    }

  } /* namespace i2c */

} /* namespace smrtobj */
