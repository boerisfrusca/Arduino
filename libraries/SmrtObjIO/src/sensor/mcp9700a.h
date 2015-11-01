/**
 * \file mcp9700a.h
 * \brief MCP9700A is a class to model a Linear Active Thermistor sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef MCP9700A_H_
#define MCP9700A_H_

#include <Arduino.h>
#include "interfaces/sensor.h"
#include "interfaces/sensortemperature.h"
#include "sensor/analogsensor.h"
#include "iosignal.h"

namespace smrtobj
{

  namespace io
  {
  
    /**
     * Class MCP9700A models a temperature sensor (MCP9700A).
     * Linear Active Thermistor™ ICs are sensors whose output voltage is directly
     * proportional to measured temperature. The MCP9700A can accurately measure
     * temperature from -40C to +150C. The output of the MCP9700A is calibrated to
     * a slope of 10mV/°C and has a DC offset of 500mV. The offset allows reading
     * negative temperatures without the need for a negative supply.
     *
     */
    class MCP9700A : public AnalogSensor, public SensorTemperature
    {
        //! millivolt per C. Typically is 0.10mV
        float m_mVpC;
  
        //! volts at 0C Typically is 0.50V
        float m_Vat0C;
  
      public:
        //! Voltage at 0C (VDD = 5.0V)
        static const float ZERO_C_VOLTS = 0.50000;
  
        //! millivolts per degree Celsius (VDD = 5.0V)
        static const float MV_PER_DEGREE_C = 0.01000;
  
        /**
         * Default Constructor.
         *
         */
        MCP9700A();
  
        /**
         * Copy Constructor.
         *
         * \param[in] s source sensor object
         *
         */
        MCP9700A(const MCP9700A &s);
  
        /**
         * Destructor.
         */
        virtual ~MCP9700A();
  
        /**
         * Override operator =
         *
         * \param[in] s source sensor object
         *
         * \return reference of the destination sensor
         */
        MCP9700A & operator=(const MCP9700A &s);
  
        /**
         * Gets temperature in celsius degrees
         *
         * \return celsuius degrees
         */
        virtual float celsius();
  
        /**
         * Gets temperature in kelvin degrees
         *
         * \return kelvin degrees
         */
        virtual float kelvin();
  
        /**
         * Gets temperature in farenheit degrees
         *
         * \return farenheit degrees
         */
        virtual float farenheit();
  
        /**
         * Reads value from the analog input
         *
         * \return value as voltage
         */
        float read();
  
    };
  
  } /* namespace io */
  
} /* namespace smrtobj */

#endif /* MCP9700A_H_ */
