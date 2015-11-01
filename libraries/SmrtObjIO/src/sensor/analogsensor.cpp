/**
 * \file analogsensor.cpp
 * \brief AnalogSensor is a class to model a generic analog sensor. It measures the voltage on a analog input of Arduino.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "analogsensor.h"

namespace smrtobj
{

  namespace io
  {
  
    /***************************************************************************
     * AnalogSensor
     ***************************************************************************/
    // Default constructor
    AnalogSensor::AnalogSensor() :
      m_measure(0)
    {
  
    }
  
    // Copy constructor
    AnalogSensor::AnalogSensor(const AnalogSensor &s) : Sensor(s), AnalogInput(s)
    {
      m_measure = s.m_measure;
    }
  
    // Default destructor
    AnalogSensor::~AnalogSensor()
    {
  
    }
  
    AnalogSensor & AnalogSensor::operator=(const AnalogSensor &s)
    {
      Sensor::operator=(s);
      m_measure = s.m_measure;
  
      return (*this);
    }
  
    float AnalogSensor::read()
    {
      unsigned long value = AnalogInput::read();
  
      m_measure = inputVoltage();
  
      return m_measure;
    }
  
  } /* namespace io */
  
} /* namespace smrtobj */
