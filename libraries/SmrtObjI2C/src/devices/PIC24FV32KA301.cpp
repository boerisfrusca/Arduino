/*
 * PIC24FV32KA301.cpp
 *
 *  Created on: Nov 2, 2015
 *      Author: boeris
 */

#include "PIC24FV32KA301.h"

namespace smrtobj
{
  namespace i2c
  {
    PIC24FV32KA301::PIC24FV32KA301() : I2CInterface(DEVICE_ADDRESS)
    {
      memset(m_cfg,   0, N_SENS);
      memset(m_data,  0, N_SENS * 2);
      memset(m_state, 0, N_SENS);
    }

    PIC24FV32KA301::PIC24FV32KA301(uint8_t addr) : I2CInterface(addr)
    {
      PIC24FV32KA301();
    }

    PIC24FV32KA301::PIC24FV32KA301(const PIC24FV32KA301 &d) : I2CInterface(d)
    {
      memcpy(m_cfg,   d.m_cfg,   N_SENS);
      memcpy(m_data,  d.m_data,  N_SENS * 2);
      memcpy(m_state, d.m_state, N_SENS);
    }

    PIC24FV32KA301::~PIC24FV32KA301()
    {
    }

    PIC24FV32KA301 & PIC24FV32KA301::operator=(const PIC24FV32KA301 &d)
    {
      I2CInterface::operator=(d);

      memcpy(m_cfg,   d.m_cfg,   N_SENS);
      memcpy(m_data,  d.m_data,  N_SENS * 2);
      memcpy(m_state, d.m_state, N_SENS);

      return (*this);
    }

    bool PIC24FV32KA301::initialize()
    {
      if ( I2Cdev::writeByte(DEVICE_ADDRESS, CFG_RAD_ADDRESS, m_cfg[RAD]) )
      {
        return I2Cdev::writeByte(DEVICE_ADDRESS, CFG_PM_ADDRESS, m_cfg[PM]);
      }

      return false;
    }


    bool PIC24FV32KA301::isConnected()
    {
      return read();
    }

    bool PIC24FV32KA301::read()
    {
      uint8_t buf[4 * N_SENS] = {0};

      if ( readAllBytes(address(), 4 * N_SENS, (uint8_t*) &buf) != 4 * N_SENS )
        return false;

      uint8_t i = 0;
      for ( i = 0; i < N_SENS; i++ )
      {
        m_data[i] = (buf[(i*2)] << 8) | buf[(i*2)+1];
      }

      i*=2;

      for (uint8_t j = 0; j < N_SENS; j++ )
      {
        m_cfg[j] = buf[i+j];
      }

      i+= N_SENS;

      for (uint8_t j = 0; j < N_SENS; j++ )
      {
        m_state[j] = buf[i+j];
      }

      return true;
    }

    bool PIC24FV32KA301::setCfgReg(uint8_t code, bool enable, uint8_t t)
    {
      if ( t > T_MAX )
        return false;

      switch (code)
      {
        case RAD :
        case PM  : {
          m_cfg[code] = t;
          m_cfg[code] &= T_MAX;
          if (enable)
            m_cfg[code] |= 0x80;
          else
            m_cfg[code] &= 0x7F;
        }
        break;
        default:
          return false;
      }

      return true;
    }

    uint8_t PIC24FV32KA301::getCfgReg(uint8_t code)
    {
      switch (code)
      {
        case RAD :
        case PM  : return m_cfg[code];
      }

      return 0x00;
    }

    uint8_t PIC24FV32KA301::getStateReg(uint8_t code)
    {
      switch (code)
      {
        case RAD :
        case PM  : return m_state[code];
      }

      return 0x00;
    }


    uint16_t PIC24FV32KA301::getDataReg(uint8_t code)
    {
      switch (code)
      {
        case RAD :
        case PM  : return m_data[code];
      }

      return 0x00;
    }

    bool PIC24FV32KA301::isEnabled(uint8_t code)
    {
      switch (code)
      {
        case RAD :
        case PM  : return (m_state[code] & 0x01);
      }

      return false;
    }

    uint8_t PIC24FV32KA301::getTsample(uint8_t code)
    {

      switch (code)
      {
        case RAD :
        case PM  : return (m_cfg[code] & T_MAX);
      }

      return 0;
    }

  } /* namespace i2c */
} /* namespace smrtobj */
