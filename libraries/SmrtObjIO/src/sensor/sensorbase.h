/**
 * \file PPD42NS.h
 * \brief  PPD42NS is a class to handle an particolate sensor, using and I2C interface implemeted by a PIC.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef SensorBase_H_
#define SensorBase_H_
 
#include "interfaces/sensor.h"
 
namespace smrtobj
{
  
  namespace io
  {
  
    /**
     * Class SensorBase models the ...
     *
     */
    class SensorBase: public smrtobj::io::Sensor
    {
      public: 
        /**
         * Default Constructor.
         *
         */
        SensorBase();
  
        /**
         * Copy Constructor.
         *
         */
        SensorBase(const SensorBase &s);
  
        /**
         * Destructor.
         */
        virtual ~SensorBase();
  
        /**
         * Override operator =
         *
         * \param[in] d source device object
         *
         * \return destination device reference
         */
        SensorBase & operator=(const SensorBase &s);

        /**
         * Returns always 0
         *
         * \return last data read as voltage level.
         */
        virtual float measure();
    };
  
  } /* namespace io */
  
} /* namespace smrtobj */
  
  #endif /* SensorBase_H_ */
  