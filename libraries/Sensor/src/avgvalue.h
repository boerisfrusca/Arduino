/**
 * \file avgvalue.h
 * \brief Arduino library to calculate cumulative average.
 *
 * \author Marco Boeris Frusca
 *
 */

#ifndef AVGVALUE_H_
#define AVGVALUE_H_

#include "Arduino.h"

class avgValue
{
    //! Index of cumulative average
    unsigned int m_i;

    //! Value
    float m_value;

  public:
    /**
     * Default Constructor
     */
    avgValue();

    /**
     * Copy Constructor
     *
     */
    avgValue(const avgValue& v);

    /**
     * Destructor
     */
    virtual ~avgValue();

    /*
     * Resets cumulative average
     *
     */
    void reset() { m_i = 0, m_value = 0.0; };

    /*
     * Gets average value
     *
     * \return current average value
     */
    float value() const { return m_value; };

    /*
     * Checks if average is valid (not 0 elements)
     *
     * \return true if is valid, false otherwise
     */
    bool isValid() const { return (m_i > 0); };

    /*
     * Adds value to the average
     *
     * \param value value to add
     *
     * \return new average value
     */
    float add(float value);

};

#endif /* AVGVALUE_H_ */
