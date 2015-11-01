/**
 * \file ledarray.cpp
 * \brief  LEDarray is an interface to model an array of LEDs.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "ledarray.h"

namespace smrtobj
{

  namespace io
  {
  
    LEDArray::LEDArray() :
        m_state(0)
    {
    }
  
    LEDArray::LEDArray(const LEDArray &l)
    {
      m_state = l.m_state;
    }
  
    LEDArray::~LEDArray()
    {
    }
  
    bool LEDArray::check(smrtobj::io::DigitalActuator** ledsArray, byte size)
    {
      for (byte cycle = 0; cycle < 3; cycle++)
      {
        for (byte i = 0; i < size; i++)
        {
          if (cycle == 2 && i == 0)
          {
            delay(CHECK_TIME);
          }
          switch (cycle)
          {
            case 0:
            {
              if (ledsArray[i])
              {
                ledsArray[i]->off();
              }
            }
              break;
  
            case 1:
            {
              if (ledsArray[i])
              {
                ledsArray[i]->on();
              }
            }
              break;
            case 2:
            {
              if (ledsArray[i])
              {
                ledsArray[i]->off();
              }
            }
              break;
          }
        }
      }
  
      return true;
    }
  
  } /* namespace io */
  
} /* namespace smrtobj */
