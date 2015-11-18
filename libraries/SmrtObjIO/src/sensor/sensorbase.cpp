/**
 * \file SensorBase.cpp
 * \brief  SensorBase is a class to handle a generic empty sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
 #include "sensorbase.h"
 
 namespace smrtobj
{
  
  namespace io
  {
  
    SensorBase::SensorBase()
    {
      
    }
  
    SensorBase::SensorBase(const SensorBase &s) : Sensor(s)
    {
    }
  
    SensorBase::~SensorBase()
    {

    }
  
    SensorBase & SensorBase::operator=(const SensorBase &s)
    {
      Sensor::operator=(s);

  
      return (*this);
    }
    
    float SensorBase::measure()
    {
      return 0;
    }
  
  } /* namespace io */

} /* namespace smrtobj */
  