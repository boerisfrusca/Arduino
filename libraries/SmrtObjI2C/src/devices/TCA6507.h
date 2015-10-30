/**
 * \file TCA6507.h
 * \brief  TCA6507 is a class to handle an TCA6507 LED driver using I2C protocol.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef TCA6507_H_
#define TCA6507_H_


#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

#include <interfaces/i2cinterface.h>

namespace smrtobj
{

  namespace i2c
  {

    /**
     * Class TCA6507 models the TCA6507 LED driver using I2C protocol.
     * This 7-bit LED dimmer for the two-line bidirectional bus (I2C) is designed to control (or dim) LEDs
     * via the I2C interface. Without this device, the microprocessor or microcontroller must be actively
     * involved in turning on and off the LEDs (per the required dimming rate), which uses valuable processor
     * time and the overloads I2C bus.
     * The TCA6507 alleviates this issue by limiting the number of operations required by the processor in
     * blinking LEDs and, thus, helps to create a more efficient system.
     *
     */
    class TCA6507 : public I2CInterface
    {
      public:
        //! Device address used by default
        static const uint8_t DEVICE_ADDRESS = 0x45;

        /**
         * Command byte for Control Register.
         * Following the successful acknowledgment of the address byte, the bus master sends a command byte,
         * which is stored in the control register. The last four bits (B0, B1, B2 and B3) of this command
         * byte determine the internal registers (Select0, Select1, Select2, Fade-On Time, Fully-On Time,
         * Fade-Off Time, First Fully-Off Time, Second Fully-Off Time, Maximum Intensity and Initialization)
         * that are affected. The command byte is sent only during a write transmission.
         * After the command byte is received, the I2C master starts sending data bytes.
         * For more information read data sheet http://www.ti.com/lit/ds/symlink/tca6507.pdf
         */
        enum _cmd_control_register
        {
          //! 'Command Select0'
          SELECT0 = 0x00,

          //! Command 'Select1'
          SELECT1 = 0x01,

          //! Command 'Select2'
          SELECT2 = 0x02,

          //! Command 'Fade-On Time'
          FADE_ON_TIME = 0x03,

          //! Command 'Fully-On Time'
          FULLY_ON_TIME = 0x04,

          //! Command 'Fade-Off Time'
          FADE_OFF_TIME = 0x05,

          //! Command 'First Fully-Off Time'
          FIRST_FULLY_OFF_TIME = 0x06,

          //! Command 'First Fully-Off Time'
          SECOND_FULLY_OFF_TIME = 0x07,

          //! Command 'Maximum Intensity'
          MAXIMUM_INTENSITY = 0x08,

          //! Command 'One Shot / Master Intensity'
          ONE_SHOT = 0x09,

          //! Command 'initialization'
          INITIALIZATION = 0x10,
        };

        /**
         * Register Descriptions.
         * The Select0 register (register 0),
         * Select1 (register 1), and Select2 register (register 2) configure the state of each of the
         * outputs
         */
        enum _register_description
        {
          //! LED off (High impedence)
          LED_OFF = 0x00,

          //! LED on steadily with maximum intensity value of PWM0 (ALD value or BRIGHT_F0 value)
          LED_ON_PWM0 = 0x02,

          //! LED on steadily with maximum intensity value of PWM1 (ALD value or BRIGHT_F1 value)
          LED_ON_PWM1 = 0x03,

          //! LED fully on (output low). Can be used as general-purpose output
          LED_ON = 0x04,

          //! LED on at brightness set by One Shot /  Master Intensity register
          LED_ON_ONE_SHOT = 0x05,

          //! LED blinking with intensity characteristics of BANK0 (PWM0)
          LED_BLINK_BANK0 = 0x06,

          //! LED blinking with intensity characteristics of BANK1 (PWM1)
          LED_BLINK_BANK1 = 0x07,
        };

        /**
         * Output pin.
         */
        enum _output_pin
        {
          //! Output pin number 0
          P0 = 0x00,

          //! Output pin number 1
          P1 = 0x01,

          //! Output pin number 2
          P2 = 0x02,

          //! Output pin number 3
          P3 = 0x03,

          //! Output pin number 4
          P4 = 0x04,

          //! Output pin number 5
          P5 = 0x05,

          //! Output pin number 6
          P6 = 0x06,
        };

        /**
         * Value for the time parameter.
         */
        enum _time_parameter
        {
          //! 0 ms
          TMS0 = 0x00,

          //! 64 ms
          TMS64 = 0x01,

          //! 128 ms
          TMS128 = 0x02,

          //! 192 ms
          TMS192 = 0x03,

          //! 256 ms (default value)
          TMS256 = 0x04,

          //! 384 ms
          TMS384 = 0x05,

          //! 512 ms
          TMS512 = 0x06,

          //! 768 ms
          TMS768 = 0x07,

          //! 1024 ms
          TMS1024 = 0x08,

          //! 1536 ms
          TMS1536 = 0x09,

          //! 2048 ms
          TMS2048 = 0x0A,

          //! 3072 ms
          TMS3072 = 0x0B,

          //! 4096 ms
          TMS4096 = 0x0C,

          //! 5760 ms
          TMS5760 = 0x0D,

          //! 8128 ms
          TMS8128 = 0x0E,

          //! 16320 ms
          TMS16320 = 0x0F,

        };

        /**
         * Basic bank number.
         */
        enum _basic_bank_number
        {
          //! Bank 0
          BANK0 = 0x00,

          //! Bank 1
          BANK1 = 0x01,
        };

        /**
         * Default Constructor.
         * It sets the reset pin to 0 (\e P0).
         */
        TCA6507();

        /**
         * Constructor.
         * It sets the reset pin to a specific value. Reset pin can be any analog or digital pin on Arduino.
         *
         * \param[in] r_pin number of the reset pin
         */
        TCA6507(uint8_t r_pin);

        /**
         * Copy Constructor.
         *
         * \param[in] d device object
         */
        TCA6507(const TCA6507 &d);

        /**
         * Destructor.
         */
        virtual ~TCA6507();

        /**
         * Override operator =
         *
         * \param[in] d source device object
         *
         * \return destination obiect reference
         */
        TCA6507 & operator=(const TCA6507 &d);

        /**
         * Starts I2C communications, and puts device in shutdown mode.
         *
         * \return always true
         */
        virtual bool initialize();

        /**
         * Powers IC from shutdown mode
         */
        void start();

        /**
         *  Resets registers and puts IC in shutdown mode.
         */
        void stop();

        /**
         * Reads data from the i2c device. This function is empty and returns always true.
         *
         * \return true if no errors
         */
        virtual bool read() { return true; };

        /**
         * Tests if the device is connected.
         * Make sure the device is connected and responds when you try to read a register.
         *
         * \return true if connection is valid, false otherwise
         */
        virtual bool isConnected();

        /**
         *  RAW Select Registers Drive for setting all pins at the same time by using auto-increment mode.
         *  Function RAW Select Registers Drive for setting all pins at the same time by using auto-increment
         *  mode. Useful when need switch multiple pins at the same time, can be used for binary.
         *  To use a P port as a general-purpose output, Select1 and Select0 registers must be set low (or 0),
         *  then the inverse of the data written to the Select2 bit appears on the open-drain output.
         *
         *  Example turns on (sets low) all outputs, then turns off outputs 1 and 7 (sets high impedance).
         *
         * \code{.cpp}
         *  smrtobj::i2c::TCA6507 tca6507;
         *
         *  // Enable IC for communications
         *  tca6507.initialize();
         *  tca6507.start();  
         *
         *  ...
         *
         *  tca6507.RAWSelRegsDrv(0x00, 0x00, 0x7F);
         *  tca6507.RAWSelRegsDrv(0x00, 0x00, 0x3E);
         * \endcode
         *
         * \param[in] s0 Select0 register
         * \param[in] s1 Select1 register
         * \param[in] s2 Select2 register
         *
         * \return true for success, or false if any error occurs.
         */
        bool RAWSelRegsDrv(uint8_t s0, uint8_t s1, uint8_t s2);

       /**
         * RAW Registry Drive Function for advanced users and can be used to set state one of registers.
         * To be used with registers 3 thru 10.
         * Example below sets intensity of bank 1 to 8 and bank 0 to 15(max).
         *
         * \code{.cpp}
         *  smrtobj::i2c::TCA6507 tca6507;
         *
         *  // Enable IC for communications
         *  tca6507.initialize();
         *  tca6507.start();  
         *
         *  ...
         *
         * tca6507.RAWRegDrv(maxinten, 0x8F);
         * \endcode
         *
         * Available registers:
         *    - 0x03 : Time it takes for the LED to fade to fully on state (FADE_ON_TIME).
         *    - 0x04 : Time LED stays in fully on state after fading or switching on (FULLY_ON_TIME).
         *    - 0x05 : Time it takes for the LED to fade to fully off state (FADE_OFF_TIME).
         *    - 0x06 : First time LED stays in fully off state after fading or switching off (FIRST_FULLY_OFF_TIME).
         *    - 0x07 : Second time LED stays in fully off state after fading or switching off (SECOND_FULLY_OFF_TIME).
         *    - 0x08 : Maximum intensity register both banks set to 15(maximum) by default (MAXIMUM_INTENSITY).
         *    - 0x09 : One shot or master intensity register (ONE_SHOT).
         *    - 0x0A : Initialization register.
         *
         *  \param[in] reg register to set
         *  \param[in] val value to write into register
         *
         *  \return true for success, or false if any error occurs.
         */
        bool RAWRegDrv(uint8_t reg, uint8_t val);

        /**
         * RAW Registry read.
         * Reading entire register (both memory banks) using Read Registry function. Example reads LED
         * fully on time register and returns single value for two memory banks.
         *
         * \code{.cpp}
         * int x = 0;
         * smrtobj::i2c::TCA6507 tca6507;
         *
         * // Enable IC for communications
         * tca6507.initialize();
         * tca6507.start();  
         *
         * ...
         * 
         * x = tca6507.Rreg(FULLY_ON_TIME);
         * \endcode
         *
         * \param[in] reg register to read
         *
         * \return register value
         */
        uint8_t readReg(uint8_t reg);

        /**
         * Getting current pin state using Current Pin State.
         *
         * Pin States (according to smrtobj::i2c::TCA6507::_register_description):
         *    - 0 : Off (LED_OFF).
         *    - 2 : On with intensity of PWM0 (LED_ON_PWM0).
         *    - 3 : On with intensity of PWM1 (LED_ON_PWM1).
         *    - 4 : On (LED_ON).
         *    - 5 : On at intensity set by One Shot or Master Intensity (LED_ON_ONE_SHOT).
         *    - 6 : Flash or fade with intensity of PWM0 (LED_BLINK_BANK0).
         *    - 7 : Flash or fade with intensity of PWM1 (LED_BLINK_BANK0).
         *    - 16 : Read error occurred.
         *
         * \param[in] pin selected pin
         *
         * \return pin state 0, 2-7, if reading error occurs function returns 16.
         */
        uint8_t pinState(uint8_t pin);

        /**
         * Setting single output to specified state using Pin Set State function.
         * Example sets output pin 5 to on state without changing state of any other pin.
         * State values are descriped in enum smrtobj::i2c::TCA6507::_register_description.
         *
         * \code{.cpp}
         * smrtobj::i2c::TCA6507 tca6507;
         *
         * // Enable IC for communications
         * tca6507.initialize();
         * tca6507.start();  
         *
         * ...
         * 
         * tca6507.pinSetState(P5, LED_ON);
         * \endcode
         *
         * \param[in] pin pin number
         * \param[in] state new state to set
         */
        void pinSetState(uint8_t pin, uint8_t state);

        /**
         * Setups single banks timing parameters using Basic Bank Setup function.
         * Example sets bank 0 timing for flashing or fading.
         *
         * tca6507.basicBankSetup(BANK0, TMS0, TMS256, TMS0, TMS256, TMS512);
         *
         * \param[in] nBank bank number
         * \param[in] fadeOn
         * \param[in] onTime
         * \param[in] fadeOff
         * \param[in] offTime
         * \param[in] sdOffTime
         */
        void basicBankSetup(uint8_t nBank, uint8_t fadeOn, uint8_t onTime, uint8_t fadeOff, uint8_t offTime, uint8_t sdOffTime);

        /**
         * Modifying one bank without effecting another using Registry To Bank, works with registry 3 to 8.
         * Example sets intensity of bank 1 to 4, intensity control is from 0-15.
         *
         * tca6507.registryToBank(Bbank1, maxinten, 0x04);
         *
         * \param[in] nBank bank number
         * \param[in] nReg register number
         * \param[in] val value to write into the register
         *
         */
        void registryToBank(uint8_t nBank, uint8_t nReg, uint8_t val);

      private:
        //! IC reset pin. Reset pin can be any analog or digital pin on Arduino.
        uint8_t m_reset_pin;
    };

  } /* namespace i2c */

} /* namespace smrtobj */

#endif /* TCA6507_H_ */
