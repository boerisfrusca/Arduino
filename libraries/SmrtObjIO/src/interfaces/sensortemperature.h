/**
 * \file sensortemperature.h
 * \brief  SensorTemperature is an interface to model a generic sensor temperature.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef SENSORINTERFACE_H_
#define SENSORINTERFACE_H_

#include <Arduino.h>

namespace smrtobj
{

  namespace io
  {
  
    /**
     * SensorTemperature is an interface to model a generic sensor temperature.
     * It defines the main functions to convert the measurement from a unit to
     * an other. The units supported are: Celsius, Farenheit and kelvin degrees.
     */
    class SensorTemperature
    {
      public:
        /**
         * Converts from celsius to farenheit degrees.
         *
         * \param[in] degree temperature in celsius degrees
         *
         * \return farenheit degrees
         */
        static float celsius2farenheit(float degree);
  
        /**
         * Converts from farenheit to celsius degrees.
         *
         * \param[in] degree temperature in farenheit degrees
         *
         * \return celsius degrees
         */
        static float farenheit2celsius(float degree);
  
        /**
         * Converts from celsius to kelvin degrees.
         *
         * \param[in] degree temperature in celsius degrees
         *
         * \return kelvin degrees
         */
        static float celsius2kelvin(float degree);
  
        /**
         * Converts from kelvin to celsius degrees.
         *
         * \param[in] degree temperature in kelvin degrees
         *
         * \return celsius degrees
         */
        static float kelvin2celsius(float degree);
  
  
        /**
         * Converts from farenheit to kelvin degrees.
         *
         * \param[in] degree temperature in farenheit degrees
         *
         * \return kelvin degrees
         */
        static float farenheit2kelvin(float degree);
  
  
        /**
         * Converts from kelvin to farenheit degrees.
         *
         * \param[in] degree temperature in kelvin degrees
         *
         * \return farenheit degrees
         */
        static float kelvin2farenheit(float degree);
  
        /**
         * Default Constructor.
         *
         */
        SensorTemperature();
  
        /**
         * Destructor.
         */
        virtual ~SensorTemperature();
  
        /**
         * Gets temperature in celsius degrees
         *
         * \return celsuius degrees
         */
        virtual float celsius() = 0;
  
        /**
         * Gets temperature in kelvin degrees
         *
         * \return kelvin degrees
         */
        virtual float kelvin() = 0;
  
        /**
         * Gets temperature in farenheit degrees
         *
         * \return farenheit degrees
         */
        virtual float farenheit() = 0;
    };
  
  } /* namespace io */
  
} /* namespace smrtobj */

#endif /* SENSORINTERFACE_H_ */
