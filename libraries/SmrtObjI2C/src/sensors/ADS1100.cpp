/**
 * \file ADS1100.cpp
 * \brief  ADS1100 is a class to handle an I2C ADC ADS1100.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "ADS1100.h"

namespace smrtobj
{

  ADS1100::ADS1100() : m_value(0)
  {
    set_dev_address(DEVICE_ADDRESS);
  }

  ADS1100::ADS1100(uint8_t addredd) : m_value(0)
  {
    set_dev_address(DEVICE_ADDRESS);
  }

  ADS1100::ADS1100(const ADS1100 &d) : I2CInterface(d)
  {
    m_value = d.m_value;
  }

  ADS1100::~ADS1100()
  {
  }

  ADS1100 & ADS1100::operator=(const ADS1100 &s)
  {
    I2CInterface::operator=(s);

    m_value = s.m_value;

    return (*this);
  }


  bool ADS1100::initialize() {
      // Nothing is required, but
      // the method should exist anyway.
    return true;
  }

  bool ADS1100::isConnected()
  {
    if ( read() )
    {
      return true;
    }
    return false;
  }


  bool ADS1100::read()
  {
    return read_word(m_value);
  }

  float ADS1100::measure()
  {
    float voltage = m_value * 2.048 ;
    voltage = voltage / 32768.0;

    return (float) voltage;
  }

} /* namespace smrtobj */
