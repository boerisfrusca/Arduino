/**
 * \file avgvalue.cpp
 * \brief Arduino library to calculate cumulative average.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "avgvalue.h"

namespace smrtobj
{

  namespace data
  {
    /**********************************************************************************
     * AvgValue
     **********************************************************************************/	
    AvgValue::AvgValue() :
     m_i(0),
     m_value(0.0)
    {
    }
    AvgValue::AvgValue(const AvgValue& v)
    {
      m_i = v.m_i;
      m_value = v.m_value;
    }
  
    AvgValue::~AvgValue()
    {
    }

    float AvgValue::push(float value)
    {
      m_value += (value - m_value) / ( ++m_i );
  
      return m_value;
    }

    float AvgValue::add(float value)
    {
      //Serial.println(m_value);
      m_value += value;
      //Serial.println(m_value);
      ++m_i;
      //Serial.println(m_i);
  
      return m_value;
    }
  
  } /* namespace data */

}/* namespace smrtobj */
