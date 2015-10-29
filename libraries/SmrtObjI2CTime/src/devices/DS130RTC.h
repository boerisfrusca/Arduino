/**
 * \file DS130RTC.h
 * \brief  DS130RTC is a class to handle an DS130 RTC.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef DS130RTC_H_
#define DS130RTC_H_

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

#include <Time.h>
#include <interfaces/i2cinterface.h>

namespace smrtobj
{
  /**
   * Class DS130RTC models the DS130 RTC device.
   * The DS1307 serial real-time clock (RTC) is a low-power, full binary-coded decimal (BCD) clock/calendar
   * plus 56 bytes of NV SRAM. Address and data are transferred serially through an I2C, bidirectional bus.
   * The clock/calendar provides seconds, minutes, hours, day, date, month, and year information. The end of
   * the month date is automatically adjusted for months with fewer than 31 days, including corrections for
   * leap year. The clock operates in either the 24-hour or 12-hour format with AM/PM indicator. The DS1307
   * has a built-in power-sense circuit that detects power failures and automatically switches to the backup supply.
   * Timekeeping operation continues while the part operates from the backup supply.
   *
   */
  class DS130RTC : public I2CInterface
  {
    public:
      /**
       * Device address used by default
       */
      enum _device_address
      {
        DEVICE_ADDRESS = 0x68,
      };

      /**
       * Default Constructor.
       *
       */
      DS130RTC();

      /**
       * Copy Constructor.
       *
       * \param[in] d i2c rtc object
       */
      DS130RTC(const DS130RTC &d);

      /**
       * Destructor.
       */
      virtual ~DS130RTC();

      /**
       * Override operator =
       *
       * \param[in] d source rtc object
       *
       * \return destination obiect reference
       */
      DS130RTC & operator=(const DS130RTC &d);

      /**
       * Starts I2C communications, and check if device is present.
       *
       * \return always true
       */
      virtual bool initialize();

      /**
       * Reads data from the i2c device.
       *
       * \return true if no errors
       */
      virtual bool read();

      bool write(time_t t);

      time_t time() { return m_time; };

      /**
       * Tests if the device is connected.
       * Make sure the device is connected and responds when you try to read a register.
       *
       * \return true if connection is valid, false otherwise
       */
      virtual bool isConnected() { return true; };

    protected:
      bool write();

    private:
      //! Last time read
      time_t m_time;
  };

} /* namespace smrtobj */

#endif /* DS130RTC_H_ */
