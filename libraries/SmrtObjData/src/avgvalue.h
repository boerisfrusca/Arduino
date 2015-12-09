/**
 * \file avgvalue.h
 * \brief Arduino library to calculate cumulative average.
 *
 * \author Marco Boeris Frusca
 *
 */

#ifndef AVGVALUE_H_
#define AVGVALUE_H_


#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif


namespace smrtobj
{

  namespace data
  {
  
    /**
     * The AvgValue class implements a moving average using a cululative moving average formula.
     * In a cumulative moving average, the data arrive in an ordered datum stream, and it is possible to get the average of all of the data up until the current datum point. 
     * 
     * \f$
     * CMA(n+1) = CMA(n) + \frac{x(n+1) + CMA(n)}{n + 1}
     * \f$
     * 
     */
    class AvgValue
    {
        //! Index of cumulative average
        unsigned int m_i;
  
        //! Value
        float m_value;
  
      public:
        /**
         * Default Constructor
         */
        AvgValue();
  
        /**
         * Copy Constructor
         *
         * \param[in] v Average
         *
         */
        AvgValue(const AvgValue& v);
  
        /**
         * Destructor
         */
        virtual ~AvgValue();
  
        /**
         * Resets cumulative average
         *
         */
        void reset() { m_i = 0, m_value = 0.0; };
  
        /**
         * Gets average value
         *
         * \return current average value
         */
      float value() const { return m_value; };
  
        /**
         * Checks if average is valid (not 0 elements)
         *
         * \return true if is valid, false otherwise
         */
        bool isValid() const { return (m_i > 0); };

        /**
         * Adds value to the cumulativaaverage
         *
         * \param value value to add
         *
         * \return new average value
         */
        float push(float value);

        /**
         * Adds value to the total value
         *
         * \param value value to add
         *
         * \return new average value
         */
        float add(float value);
  
        /**
         * Returns the current index.
         *
         * \return index.
         */
        unsigned int index() { return m_i; }

    };
  
  } /* namespace data */
  
} /* namespace smrtobj */

#endif /* AVGVALUE_H_ */
