/**
 * \file PCA9548A.h
 * \brief  PCA9548A is a class to handle the PCA9548A Low Voltage 8-Channel I 2 C Switch.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef PCA9548A_H_
#define PCA9548A_H_

#include <interfaces/i2cinterface.h>

namespace smrtobj
{
  namespace i2c
  {

    /**
     * The PCA9548A has eight bidirectional translating switches that can be controlled via the I2C bus. The
     * SCL/SDA upstream pair fans out to eight downstream pairs, or channels. Any individual SCx/SDx channel
     * or combination of channels can be selected, determined by the contents of the programmable control register.
     * The system master can reset the PCA9548A in the event of a timeout or other improper operation by asserting
     * a low in the RESET input. Similarly, the power-on reset deselects all channels and initializes the I2C/SMBus
     * state machine. Asserting RESET causes the same reset/initialization to occur without powering down the part.
     */
    class PCA9548A  : public I2CInterface
    {
      public:
        /**
         * Device address used by default
         */
        enum _device_address
        {
          DEVICE_ADDRESS = 0x70,
        };

        /**
         * Default Constructor.
         * The \e DEVICE_ADDRESS value of smrtobj::i2c::PCA9548A::_device_address is used as default address of the device.
         */
        PCA9548A();

        /**
         * Constructor.
         * Sets the device address. It must be between 0x70 and 0x77. If value is not in this range, default value
         * it is used (\e DEVICE_ADDRESS value of smrtobj::i2c::PCA9548A::_device_address).
         *
         * \param[in] addr device address
         *
         */
        PCA9548A(uint8_t addr);

        /**
         * Copy Constructor.
         *
         * \param[in] d device object
         */
        PCA9548A(const PCA9548A &d);

        /**
         * Destructor.
         */
        virtual ~PCA9548A();

        /**
         * Override operator =
         *
         * \param[in] d source device object
         *
         * \return destination obiect reference
         */
        PCA9548A & operator=(const PCA9548A &d);

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
        virtual bool isConnected();

        /**
         * Reads the current value of the control register and saves it into internal buffer. To get the read time use
         * function smrtobj::i2c::PCA9548A::registerCtrl.
         *
         * \code{.cpp}
         * smrtobj::i2c::PCA9548A i2c_mux;
         *
         * if ( i2c_mux.read() )
         * {
         *   uint8_t reg = i2c_mux.time();
         *   ...
         * } 
         * \endcode
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool read();

        /**
         * Gets the last value read of the control register.
         *
         * \return last value read.
         */
        uint8_t registerCtrl() { return m_ctrl_reg;};

       /**
        * Disables all channels. This function writes into control register value 0x00.
         *
         * \return true for success, or false if any error occurs. 
         */
        bool disableAll() {m_ctrl_reg = 0x00; return write ();};

        /**
         * Enables all channels. This function writes into control register value 0xFF.
         *
         * \return true for success, or false if any error occurs. 
         */
        bool enableAll() {m_ctrl_reg = 0xFF; return write ();};

        /**
         * Sets the state (enable/disable) of a channel. 
         *
         * \param[in] n channel number
         * \param[in] en 0 to disable, 1 to enable
         *
         * \return true for success, or false if any error occurs. 
         */
        bool setChannel(uint8_t n, bool en);

        /**
         * Selects only a specific channel. 
         *
         * \param[in] n channel number
         *
         * \return true for success, or false if any error occurs. 
         */
        bool select(uint8_t n);

      protected:
        /**
         * Writes the control register, using value saved into a internal buffer.
         * 
         * \return true for success, or false if any error occurs. 
         */
        bool write ();

      private:
        //! Control register
        uint8_t m_ctrl_reg;
    };

  } /* namespace i2c */

} /* namespace smrtobj */

#endif /* PCA9548A_H_ */
