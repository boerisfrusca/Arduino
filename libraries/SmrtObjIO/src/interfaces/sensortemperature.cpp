/**
 * \file sensortemperature.h
 * \brief  SensorTemperature is an interface to model a generic sensor temperature.
 *
 * \author Marco Boeris Frusca
 *
 */

#include "sensortemperature.h"

namespace smrtobj
{
  /***************************************************************************
   * SensorTemperature
   ***************************************************************************/
  SensorTemperature::SensorTemperature()
  {
    // TODO Auto-generated constructor stub

  }

  SensorTemperature::~SensorTemperature()
  {
    // TODO Auto-generated destructor stub
  }

  float SensorTemperature::celsius2farenheit(float degree)
  {
    //  F = (C × 9/5) + 32
    degree *= 9;
    degree /=5;
    degree += 32;
    return degree;
  }

  float SensorTemperature::farenheit2celsius(float degree)
  {
    // C = (F − 32) x 5/9
    degree -= 32;
    degree *= 5;
    degree /= 9;

    return degree;
  }

  float SensorTemperature::celsius2kelvin(float degree)
  {
    // K = C + 273.15
    degree += 273.15;
    return degree;
  }

  float SensorTemperature::kelvin2celsius(float degree)
  {
    // C = K - 273.15
    degree -= 273.15;
    return degree;
  }

  float SensorTemperature::farenheit2kelvin(float degree)
  {
    float value = farenheit2celsius(degree);
    return celsius2kelvin(value);
  }

  float SensorTemperature::kelvin2farenheit(float degree)
  {
    float value = kelvin2celsius(degree);
    return celsius2farenheit(value);
  }

} /* namespace smrtobj */
