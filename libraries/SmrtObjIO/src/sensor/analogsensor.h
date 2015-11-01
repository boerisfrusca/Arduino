/**
 * \file analogsensor.h
 * \brief AnalogSensor is a class to model a generic analog sensor. It measures the voltage on a analog input of Arduino.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef ANALOGSENSOR_H_
#define ANALOGSENSOR_H_

#include <Arduino.h>
#include "interfaces/signal.h"
#include "interfaces/sensor.h"
#include "iosignal.h"


namespace smrtobj
{

  namespace io
  {
  
    /**
     * The AnalogSensor class model a generic analog sensor. It measures the voltage on a
     * analog input of the Arduino board. The input voltage (Vin) is given by the
     * following formula:
     *
     * \f[Vin= Nadc*(Vref/2^n)\f]
     *
     * Where:
     * \c Nadc is the output value of the ADC;\n
     * \c Vref is the reference voltage of the ADC;\n
     * \c n is the number of bits used for the conversion.
     *
     * Vref can be the changed the Arduino \b analogReference function and
     * smrtobj::AnalogSensor::setReference (or smrtobj::AnalogSensor::setReferenceDefault)
     * functions. This change applies to all analog inputs.
     *
     * \code{.cpp}
     *   //analogReference(DEFAULT);
     *   smrtobj::AnalogSensor::setReferenceDefault(smrtobj::AnalogSensor::V5_0);
     *
     *   analogReference(EXTERNAL);
     *   smrtobj::AnalogSensor::setReference(2.5);
     * \endcode
     *
     */
    class AnalogSensor : public Sensor, public AnalogInput
    {
      public:
        /**
         * Default Constructor.
         *
         */
        AnalogSensor();
  
        /**
         * Copy Constructor.
         *
         * \param[in] s source sensor object
         *
         */
        AnalogSensor(const AnalogSensor &s);
  
        /**
         * Destructor.
         */
        virtual ~AnalogSensor();
  
        /**
         * Override operator =
         *
         * \param[in] s source sensor object
         *
         * \return reference of the destination sensor
         */
        AnalogSensor & operator=(const AnalogSensor &s);
  
        /**
         * Reads value from the analog input
         *
         * \return value as voltage
         */
        virtual float read();
  
        /**
         * Gets the current measurement.
         *
         * \return value of the measurement
         *
         */
        virtual float measure() { return m_measure; };
  
      protected:
        //! Last value read
        float m_measure;
    };
  
  } /* namespace io */
  
} /* namespace smrtobj */

#endif /* ANALOGSENSOR_H_ */
