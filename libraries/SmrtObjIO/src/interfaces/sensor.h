/**
 * \file sensor.h
 * \brief  Sensor is an interface to model an input signal connected to a sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef SENSOR_H_
#define SENSOR_H_

namespace smrtobj
{

  /**
   * The Sensor class defines the standard interface of a sensor. This is a virtual class and defines
   * a virtual method "measure" to read the sensor.
   */
  class Sensor
  {
    public:
      /**
       * Default Constructor.
       *
       */
      Sensor();

      /**
       * Copy Constructor.
       *
       * \param[in] s source sensor object
       */
      Sensor(const Sensor &s);

      /**
       * Destructor.
       */
      virtual ~Sensor();

      /**
       * Override operator =
       *
       * \param[in] s source sensor object
       *
       * \return reference of the destination sensor
       */
      Sensor & operator=(const Sensor &s);

      /**
       * Reads sensor and returns the current measurement.
       *
       * \return value of the measurement
       *
       */
      virtual float measure() = 0;

    protected:
      //! Warm up time (in millis). This is the time to wait for having a valid value.
      static unsigned long TWARMUP;
  };


} /* namespace smrtobj */

#endif /* SENSOR_H_ */
