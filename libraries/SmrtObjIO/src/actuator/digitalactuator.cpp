/**
 * \file digitalactuator.cpp
 * \brief  DigitalActuator models a generic digital actuator. It can assume two different state: on or off.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "digitalactuator.h"

namespace smrtobj
{

  DigitalActuator::DigitalActuator() : m_negate(false)
  {
  }

  DigitalActuator::DigitalActuator(const DigitalActuator &a) :OutputDevice (a), DigitalOutput(a)
  {
    m_negate = a.m_negate;
  }

  DigitalActuator::~DigitalActuator()
  {
  }

  DigitalActuator & DigitalActuator::operator=(const DigitalActuator &a)
  {
    OutputDevice::operator=(a);
    DigitalOutput::operator=(a);
    m_negate = a.m_negate;

    return (*this);
  }

  bool DigitalActuator::init(byte pin, bool negate)
  {
    DigitalOutput::init(pin);

    m_negate = negate;
    off();

    return true;
  }

  bool  DigitalActuator::on()
  {
    if (!isOpen())
    {
      return false;
    }

    write((!m_negate)?HIGH:LOW);
    m_state = ON;

    return true;
  }

  bool  DigitalActuator::off()
  {
    if (!isOpen())
    {
      return false;
    }

    write((!m_negate)?LOW:HIGH);
    m_state = OFF;

    return true;
  }

} /* namespace smrtobj */
