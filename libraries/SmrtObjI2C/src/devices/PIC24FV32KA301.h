/*
 * PIC24FV32KA301.h
 *
 *  Created on: Nov 2, 2015
 *      Author: boeris
 */
/**
 * \file PIC24FV32KA301.h
 * \brief  PIC24FV32KA301 is a class to handle the communication with the PIC 24FV32KA301.
 * This PIC reads PM and radiation sensors.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef PIC24FV32KA301_H_
#define PIC24FV32KA301_H_

#include <interfaces/i2cinterface.h>

namespace smrtobj
{
  namespace i2c
  {

    /**
     * PIC24 16-bit Microcontroller featuring nanoWatt XLP for eXtreme Low Power consumption. Designed for power
     * constrained and battery powered applications. Features unique peripherals like DSBOR, DSWDT and RTCC which
     * run in Deep Sleep mode for industry leading low power performance.
     *
     * This class implements a RD2014 (Solid State Nuclear Radiation) and a PPD42NS (particle) sensor reader.
     */
    class PIC24FV32KA301 : public I2CInterface
    {
      public:
        /**
         * Device address used by default.
         */
        enum _device_address
        {
          //! Default address
          DEVICE_ADDRESS = 0x10,
        };

        /**
         * Registers address.
         */
        enum _red_address
        {
          //! Radiation sensor address.
          CFG_RAD_ADDRESS = 0x00,

          //! Particulate sensor address.
          CFG_PM_ADDRESS = 0x01,
        };

        /**
         * Maximum sample time (in minutes).
         */
        enum _limits
        {
          //! Maximum time (in minutes).
          T_MAX = 0x1F,
        };

        /**
         * Sensor index.
         */
        enum _sensor
        {
          //! Radion sensor index.
          RAD = 0,

          //! Particulate sensor index.
          PM = 1,

          //! Number of sensors handled by the PIC.
          N_SENS = 2,
        };

        /**
         * Default Constructor.
         * Sets all register to 0.
         *
         */
        PIC24FV32KA301();

        /**
         * Constructor.
         * Sets the device address.
         *
         * \param[in] addr device address.
         *
         */
        PIC24FV32KA301(uint8_t addr);

        /**
         * Copy Constructor.
         *
         * \param[in] d i2c device object.
         */
        PIC24FV32KA301(const PIC24FV32KA301 &d);

        /**
         * Destructor.
         */
        virtual ~PIC24FV32KA301();

        /**
         * Override operator =
         *
         * \param[in] d device object
         *
         * \return destination device reference
         */
        PIC24FV32KA301 & operator=(const PIC24FV32KA301 &d);

        /**
         * Starts I2C communications, and puts device in shutdown mode.
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
        virtual bool isConnected();

        /**
         * Reads the current value of all registers and saves it into internal buffers.
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool read();

        /**
         * Sets configuration register for a specific sensor. This register contains the sample time:
         * it is in minutes for radiation sensor and in 30 seconds for particulate sensor.
         *
         * \param[in] code sensor code
         * \param[in] enable true if sensor is enabled
         * \param[in] t sample time (max values is 31)
         *
         * \return true for success, or false if any error occurs.
         */
        bool setCfgReg(uint8_t code, bool enable, uint8_t t = 5);

        /**
         * Gets the configuration register of a specific sensor.
         * Every read operation all internal buffers are updated.
         *
         * \param[in] code sensor code
         *
         * \return register value.
         */
        uint8_t getCfgReg(uint8_t code);

        /**
         * Gets sample time from the configuration register stored in the internal buffer.
         * Every read operation all internal buffers are updated.
         */
        uint8_t getTsample(uint8_t code);

        /**
         * Gets the state register of a specific sensor.
         * Every read operation all internal buffers are updated.
         *
         * \param[in] code sensor code
         *
         * \return register value.
         */
        uint8_t getStateReg(uint8_t code);

        /**
         * Gets the data register of a specific sensor.
         * Every read operation all internal buffers are updated.
         *
         * \param[in] code sensor code
         *
         * \return register value.
         */
        uint16_t getDataReg(uint8_t code);

        /**
         * Returns true if sensor with index \e code is enabled.
         *
         * \param[in] code sensor code.
         *
         * \return true if sensor is enabled, false otherwise.
         */
        bool isEnabled(uint8_t code);


      private:
        // Configuration registers
        uint8_t m_cfg[N_SENS];

        // Data registers
        uint16_t m_data[N_SENS];

        // State registers
        uint8_t m_state[N_SENS];

    };

  } /* namespace i2c */

} /* namespace smrtobj */

#endif /* PIC24FV32KA301_H_ */
