/*
 * DS130RTC.cpp
 *
 *  Created on: Oct 29, 2015
 *      Author: boeris
 */

#include "DS130RTC.h"

namespace smrtobj
{

  DS130RTC::DS130RTC() : I2CInterface(DEVICE_ADDRESS),  m_time(0)
  {

  }

  DS130RTC::DS130RTC(const DS130RTC &d)
  {
    m_time = d.m_time;
  }

  DS130RTC::~DS130RTC()
  {

  }

  DS130RTC & DS130RTC::operator=(const DS130RTC &d)
  {
    I2CInterface::operator=(d);
    m_time = d.m_time;

    return (*this);
  }

  bool DS130RTC::initialize()
  {
    return true;
  }


  bool DS130RTC::write()
  {
    uint8_t data[7] = {0};
    tmElements_t tm;
    breakTime(m_time, tm);

    data[0] = dec2bcd(tm.Second);
    data[1] = dec2bcd(tm.Minute);
    data[2] = dec2bcd(tm.Hour);
    data[3] = dec2bcd(tm.Wday);
    data[4] = dec2bcd(tm.Day);
    data[5] = dec2bcd(tm.Month);
    data[6] = dec2bcd(tmYearToY2k(tm.Year));

    return I2Cdev::writeBytes(address(), 0x00, 7,data);
  }

  bool DS130RTC::write(time_t t)
  {
    m_time = t;

    return write();
  }

  bool DS130RTC::read()
  {
    uint8_t data[7] = {0};
    tmElements_t tm;

    if ( I2Cdev::readBytes(address(), 0x00, 7, data) )
    {
      tm.Second = bcd2dec(data[0] & 0x7f);
      tm.Minute = bcd2dec(data[1] );
      tm.Hour   =   bcd2dec(data[2] & 0x3f);  // mask assumes 24hr clock
      tm.Wday   = bcd2dec(data[3] );
      tm.Day    = bcd2dec(data[4] );
      tm.Month  = bcd2dec(data[5] );
      tm.Year   = y2kYearToTm((bcd2dec(data[6])));

      m_time = makeTime(tm);

      return true;

    }
    return false;
  }

} /* namespace smrtobj */
