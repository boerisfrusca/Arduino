/**
 * \file measure.cpp
 * \brief Arduino library to model a generic measurement. It is identified by a value (as a float), a time and a GPS position.
 *
 * \author Marco Boeris Frusca
 *
 */

#include "measure.h"

Measure::Measure() :
  m_value(0),
  m_timestamp(0.0)

{
  memset(m_buffer, 0, BUFFER_SIZE);

}

Measure::Measure(const Measure &m)
{
  m_value = m.m_value;
  m_timestamp = m.m_timestamp;
  memcpy(m_buffer, m.m_buffer, BUFFER_SIZE);
  m_position = m.m_position;
}

Measure::~Measure()
{
}

const char* Measure::timestamp(byte format)
{
  switch (format)
  {
    case IOT : {
      snprintf ( m_buffer, BUFFER_SIZE, "%02d/%02d/%04d %02d:%02d", month(m_timestamp), day(m_timestamp), year(m_timestamp), hour(m_timestamp), minute(m_timestamp));
    } break;
    case DEFAULT_TS : {
      snprintf ( m_buffer, BUFFER_SIZE, "%02d/%02d/%04d %02d:%02d:%02d", day(m_timestamp), month(m_timestamp), year(m_timestamp), hour(m_timestamp), minute(m_timestamp), second(m_timestamp));
    }
    default : {
    }break;
  }

  return m_buffer;
}

int Measure::setPosition(char* latitude, char* longitude, char* altitude, byte &coord)
{
  coord = 1;

  int err = m_position.setLatitude(latitude);

  if (err == 1)
  {

    coord = 2;
    err = m_position.setLongitude(longitude);

    if (err == 1)
    {

      coord = 3;
      err = m_position.setAltitude(altitude);

    }
  }

  if (err == 1)
  {
    coord = 0;
  }
  return err;
}
