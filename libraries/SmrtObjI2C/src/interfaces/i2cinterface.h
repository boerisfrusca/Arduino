/**
 * \file i2cinterface.h
 * \brief  I2CInterface is an interface to model an I2C device.
 * \brief  This I2C device library is using (and submitted as a part of) Jeff Rowberg's I2Cdevlib library.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef I2CINTERFACE_H_
#define I2CINTERFACE_H_

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

#include <smrtobjio.h>
#include <I2Cdev.h>

namespace smrtobj
{


  namespace i2c
  {

    /**
     * The I2CInterface class defines the standard interface of an I2C device sensor. An I2C device is identified by
     * a address of one byte.  This is a virtual class and defines four virtual method:
     *   - initialize : initializes the device (if it is required by the datasheet specifics).
     *   - isConnected : verifies if the device is connected. It can be done trying to read a value from the device and testing if operation is successfully done.
     *   - read : read values from device
     *   - measure : calculate a measure or specific value from the all data read.
     *
     */
    class I2CInterface : public Signal
    {
      public:
        /**
         * Default Constructor.
         * Sets the default address to 0x00 and communication type as bidirectional (according to 
         * smrtobj::io::Signal::_type enum).
         *
         */
        I2CInterface();
  
        /**
         * Constructor.
         * Sets the device address and communication type as bidirectional (according to 
          * smrtobj::io::Signal::_type enum).
        *
         * \param[in] addr device address
         */
        I2CInterface(uint8_t addr);
  
        /**
         * Copy Constructor.
         *
         * \param[in] d i2c device object
         */
        I2CInterface(const I2CInterface &d);
  
        /**
         * Destructor.
         */
        virtual ~I2CInterface();
  
        /**
         * Returns the device address.
         *
         * \return device address
         */
        uint8_t address() { return m_device_addr; }
  
        /**
         * Gets the type of the interface according to smrtobj::io::Signal::_type enum
         *
         * \return type of the interface
         */
        byte type() {return m_type; }
  
        /**
         * Override operator =
         *
         * \param[in] d source device object
         *
         * \return destination signal reference
         */
        I2CInterface & operator=(const I2CInterface &d);
  
        /**
         * Initializes the i2c device: power on and prepare for general usage.
         * Virtual function, inheriting classes must define it.
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool initialize() = 0;
  
        /**
         * Tests if the device is connected.
         * Make sure the device is connected and responds as expected.
         * Virtual function, inheriting classes must define it.
         *
         * \return true if connection is valid, false otherwise
         */
        virtual bool isConnected() = 0;
  
        /**
         * Reads data from the i2c device.
         *
         * \return true if connection is valid, false otherwise
         */
        virtual bool read() = 0;
  
      protected:
        /**
         * Converts a number (1 byte) from decimal to BCD
         *
         * \param[in] num decimal number
         *
         * \return BCD number
         */
        static uint8_t dec2bcd(uint8_t num);
  
        /**
         * Converts a number (1 byte) from BCD to decimal
         *
         * \param[in] num BCD number
         *
         * \return BCD decimal
         */
        static uint8_t bcd2dec(uint8_t num);
  
        /**
         * Sets the device address. This function must be called only by constructors.
         *
         * \param[in] addr device address
         */
        void setDeviceAddress(uint8_t addr)
        {
          m_device_addr = addr;
        }
  
        /** Reads a word (2 byte) from i2c device.
         *
         * \param[out] value data read
         * \param[in] MSB true if data is in format Most Significant Byte, false if it is Less Significat Byte
         *
         * \return false in case of errors, true otherwise
         */
        bool read_word(uint16_t &value, bool MSB = true);
  
        /**  
         * Reads bytes from a slave device.
         * This is a "stripped-down" version of the standard Jeff Rowberg's I2Cdev::readBytes method,
         * which apparently does not support setting of an address pointer to indicate from which position
         * is to start read from.
         *
         * \param[in] devAddr Address of the slave device to read bytes from
         * \param[in] length Number of bytes to read
         * \param[out] data Buffer to store read data in
         * \param[in] timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
         *
         * \return Number of bytes read (0 indicates failure)
         */
        int8_t readAllBytes(uint8_t devAddr, uint8_t length, uint8_t *data, uint16_t timeout=I2Cdev::readTimeout);
  
        /**  
         * Writes bytes to a slave device.
         * This is a "stripped-down" version of the standard Jeff Rowberg's I2Cdev::writeBytes method,
         * which apparently does not support setting of an address pointer to indicate from which position
         * is to start read from.
         *
         * \param[in] devAddr Address of the slave device to write bytes to
         * \param[in] length Number of bytes to write
         * \param[in] data Buffer with data to write
         * \param[in] timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
         *
         * \return false in case of errors, true otherwise
         */
        bool writeAllBytes(uint8_t devAddr, uint8_t length, uint8_t *data, uint16_t timeout=I2Cdev::readTimeout);
  
      private:
        // Device address
        uint8_t m_device_addr;
    };
  
  } /* namespace i2c */

} /* namespace smrtobj */

#endif /* I2CINTERFACE_H_ */
