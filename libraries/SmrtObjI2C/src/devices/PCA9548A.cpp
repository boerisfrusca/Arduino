/*
 * PCA9548A.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: boeris
 */

#include "PCA9548A.h"

namespace smrtobj
{
  namespace i2c
  {

    PCA9548A::PCA9548A() : I2CInterface(DEVICE_ADDRESS), m_ctrl_reg(0)
    {

    }

    PCA9548A::PCA9548A(uint8_t addr):  m_ctrl_reg(0)
    {
      if (addr < 0x70 || addr > 0x77)
      {
        addr = DEVICE_ADDRESS;
        setDeviceAddress(addr);
      }

      setDeviceAddress(addr);
    }

    PCA9548A::PCA9548A(const PCA9548A &d): I2CInterface(d)
    {
      m_ctrl_reg = d.m_ctrl_reg;
    }

    PCA9548A::~PCA9548A()
    {

    }

    PCA9548A & PCA9548A::operator=(const PCA9548A &d)
    {
      I2CInterface::operator=(d);
      m_ctrl_reg = d.m_ctrl_reg;

      return (*this);
    }

    bool PCA9548A::initialize()
    {
      return true;
    }

    bool PCA9548A::isConnected()
    {
      return read();
    }

    bool PCA9548A::read()
    {
      return ( readAllBytes(address(), 1, &m_ctrl_reg, 0) > 0 );
    }

    bool PCA9548A::write ()
    {
      return ( writeAllBytes(address(), 1, &m_ctrl_reg, 0) > 0 );
    }

    bool PCA9548A::setChannel(uint8_t n, bool en)
    {
      if (n > 0x08)
        return false;

      uint8_t mask = 1;

      mask <<= n;

      if (en)
        m_ctrl_reg |= mask;
      else
        m_ctrl_reg &= ~(mask);

      //Serial.print( " mask .. " );
      //Serial.println( mask , HEX );

      return write();
    }

   bool PCA9548A::select(uint8_t n)
    {
      if ( !disableAll() )
        return false;

      return setChannel(n, 1);
    }

  } /* namespace i2c */

} /* namespace smrtobj */
