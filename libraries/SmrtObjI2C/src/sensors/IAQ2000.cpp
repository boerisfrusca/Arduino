/*
 * IAQ2000.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: boeris
 */
/**
 * \file IAQ2000.cpp
 * \brief  IAQ2000 is a class to handle an iAQ-2000 Indoor Air Quality (VOC) Sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "IAQ2000.h"

namespace smrtobj
{

  IAQ2000::IAQ2000() : m_value(0)
  {
    set_dev_address(DEVICE_ADDRESS);
  }

  IAQ2000::IAQ2000(const IAQ2000 &s) : I2CInterface(s), Sensor(s)
  {
    m_value = s.m_value;
  }

  IAQ2000::~IAQ2000()
  {
  }

  IAQ2000 & IAQ2000::operator=(const IAQ2000 &s)
  {
    I2CInterface::operator=(s);
    Sensor::operator=(s);

    m_value = s.m_value;

    return (*this);
  }

  bool IAQ2000::initialize() {
      // Nothing is required, but
      // the method should exist anyway.
    return true;
  }

  bool IAQ2000::isConnected()
  {
    if ( read() )
    {
      if (m_value >= 450)
      {
          return true;
      }
    }
    return false;
  }

  bool IAQ2000::read() {
    return read_word(m_value);
  }

  float IAQ2000::measure()
  {
   return (float) m_value;
  }

} /* namespace smrtobj */
