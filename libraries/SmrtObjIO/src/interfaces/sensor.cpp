/**
 * \file sensor.cpp
 * \brief  Sensor is an interface to model an input signal connected to a sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "sensor.h"

namespace smrtobj
{
  /***************************************************************************
   * Sensor
   ***************************************************************************/
  unsigned long Sensor::TWARMUP = 0;

  // Default constructor
  Sensor::Sensor()
  {
  }


  // Copy constructor
  Sensor::Sensor(const Sensor &s)
  {
  }

  // Default destructor
  Sensor::~Sensor()
  {

  }

  Sensor & Sensor::operator=(const Sensor &s)
  {
    return (*this);
  }

} /* namespace smrtobj */




