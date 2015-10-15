/*
 * iodevice.cpp
 *
 *  Created on: Oct 14, 2015
 *      Author: boeris
 */

#include "interfaces/i2cinterface.h"

namespace smrtobj
{

  I2CInterface::I2CInterface() : m_device_addr(0)
  {
    m_type = TYPE_BIDIRECTIONAL;
  }

  I2CInterface::I2CInterface(uint8_t addr) : m_device_addr(addr)
  {
    m_type = TYPE_BIDIRECTIONAL;
  }

  I2CInterface::I2CInterface(const I2CInterface &d)
  {
    m_type = d.m_type;
    m_device_addr = d.m_device_addr;
  }

  I2CInterface::~I2CInterface()
  {
  }

  I2CInterface & I2CInterface::operator=(const I2CInterface &d)
  {
    Signal::operator=(d);
    m_type = d.m_type;
    m_device_addr = d.m_device_addr;

    return (*this);
  }
} /* namespace smrtobj */
