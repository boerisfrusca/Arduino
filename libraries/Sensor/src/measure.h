/**
 * \file measure.h
 * \brief Arduino library to model a generic measurement. It is identified by a value (as a float), a time and a GPS position.
 *
 * \author Marco Boeris Frusca
 *
 */

#ifndef MEASURE_H_
#define MEASURE_H_

#include "Arduino.h"
#include "gpsposition.h"
#include <Time.h>
/**
 * A measurement is composed by a value (real number) a time and optionally a GPS position.
 */
class Measure
{
  public:
    //! size of the internal buffer
    static const byte BUFFER_SIZE = 20;

    enum _time_format {
      //! Default format DD/MM/YYYY hh:mm:ss
      DEFAULT_TS,
      //! IoT format MM/DD/YYYY hh:mm
      IOT
    };

    /**
     * Default Constructor
     *
     */
    Measure();

    /**
     * Copy Constructor
     *
     */
    Measure(const Measure &m);

    /**
     * Destructor
     */
    virtual ~Measure();

    /**
     * Sets the value of the measurement
     *
     * \param[in] value value of the measurement
     *
     */
    void setValue(float value);

    /**
     * Sets the acquisition time of the measurement. It has to be in epoch format.
     *
     * \param[in] time timestamp of the measurement (Epoch format)
     *
     */
    void setTimestamp(unsigned long time);

    /**
     * Sets the GPS position where the measurement is acquired (it can be the position of the sensor).
     *
     * \param[in] latitude latitude coordinate in decimal degree
     * \param[in] longitude longitude coordinate in decimal degree
     * \param[in] latitude altitude coordinate in meters
     * \param[out] coord invalid coordinate index  (0 if no errors)
     *
     * \return 1 if no errors, error code otherwise (according to gpsposition enum _error)
     */
    int setPosition(char* latitude, char* longitude, char* altitude, byte &coord);

    /**
     * Gets the measurement value
     *
     * \return value of the measurement as float
     */
    float value();

    /**
     *  Gets the acquisition time of measurement.
     *
     * \return timestamp of the measurement as number of seconds from 1st of January 1970
     */
    unsigned long timestamp();

    /**
     * Gets the acquisition time of measurement.
     *
     * \return timestamp of the measurement as string in UTC format
     */
    const char* timestamp(byte format);

    /**
     * Gets the GPS position of measurement.
     *
     * \return GPS position of measurement
     */
    const GPSPosition& position() const;

  private:
    //! Measure value (ad float)
    float m_value;

    //! timestamp in epoch format
    unsigned long m_timestamp;

    //! GPS position
    GPSPosition m_position;

    //! buffer used to get timestamp as string format
    char m_buffer[BUFFER_SIZE];

};

inline float Measure::value()
{
  return m_value;
}

inline unsigned long Measure::timestamp()
{
  return m_timestamp;
}

inline const GPSPosition& Measure::position() const
{
  return m_position;
}

inline void Measure::setValue(float value)
{
  m_value = value;
}

inline void Measure::setTimestamp(unsigned long time)
{
  m_timestamp = time;
}

#endif /* MEASURE_H_ */
