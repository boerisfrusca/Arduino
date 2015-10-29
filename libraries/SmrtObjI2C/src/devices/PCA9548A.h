/**
 * \file PCA9548A.h
 * \brief  PCA9548A is a class to handle the PCA9548A Low Voltage 8-Channel I 2 C Switch.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef PCA9548A_H_
#define PCA9548A_H_


#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

#include <interfaces/i2cinterface.h>

namespace smrtobj
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
       *
       */
      PCA9548A();

      /**
       * Constructor.
       * Sets the device address. It must be between 0x70 and 0x77. If value is not in this range, default value
       * it is used.
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
       * Gets last value of read of the control register
       */
      uint8_t registerCtrl() { return m_ctrl_reg;};

      virtual bool initialize();

      virtual bool isConnected();

      virtual bool read();

      /**
       * Disables all channels
       *
       * \return false if error
       */
      bool disableAll() {m_ctrl_reg = 0x00; return write ();};

      /**
       * Enable all channels
       *
       * \return false if error
       */
      bool enableAll() {m_ctrl_reg = 0xFF; return write ();};

      bool setChannel(uint8_t n, bool en);

      bool select(uint8_t n);
    protected:
      bool write ();

    private:
      uint8_t m_ctrl_reg;
  };

} /* namespace smrtobj */

#endif /* PCA9548A_H_ */
