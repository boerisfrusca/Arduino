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
  namespace i2c
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
     * The contents of the time and calendar registers are in the BCD format. The day-of-week register increments at 
     * midnight. Values that correspond to the day of week are user defined but must be sequential (i.e., if 1 equals 
     * Sunday, then 2 equals Monday, and so on.) 
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
         * \param[in] d I2C device object
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
         * Starts I2C communications. For this device, this function does nothing.
         *
         * \return always true
         */
        virtual bool initialize();

        /**
         * Tests if the device is connected.
         * This function makes sure the device is connected and responds when you try to read a register.
         *
         * \return true if connection is valid, false otherwise
         */
        virtual bool isConnected() { return read(); };

        /**
         * Reads the current date and time and saves them as a 32 bit "time_t" number into internal buffer
         * (See the Time library for more details). To get the read time use  function smrtobj::i2c::DS130RTC::time.
         *
         * \code{.cpp}
         * smrtobj::i2c::DS130RTC rtc;
         *
         * if ( rtc.read() )
         * {
         *   time_t t = rtc.time();
         *   ...
         * } 
         * \endcode
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool read();

        /**
         * Writes the date & time, using a 32 bit "time_t" number. (See the Time library for more details).
         * 
         * \param[in] t time to set
         * 
         * \return true for success, or false if any error occurs. 
         */
        bool write(time_t t);

        /**
         * Returns the last time read or written as a 32 bit "time_t" number. (See the Time library for more details).
         *
         * \return last time value read or written 
         */
        time_t time() { return m_time; };

      private:
        /**
         * Writes the date and time, using value saved into a internal buffer. This is a 32 bit "time_t" number.
         * 
         * \return true for success, or false if any error occurs. 
         */
        bool write();

        //! Internal buffer where last time read or written is stored.
        time_t m_time;
    };

  } /* namespace i2c */

} /* namespace smrtobj */

#endif /* DS130RTC_H_ */
