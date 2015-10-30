/**
 * \file TCS34725.h
 * \brief  TCS34725 is a class to handle a TAOS TCS34725 color light-to-digital converter with IR filter.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef TCS34725_H_
#define TCS34725_H_

#include <interfaces/i2cinterface.h>

namespace smrtobj
{

  namespace i2c
  {

    /**
     * Class TCS34725 models the TAOS TCS34725 color light-to-digital converter with IR filter.
     * The TCS3472 device provides a digital return of red, green, blue (RGB), and clear light sensing values.
     * An IR blocking filter, integrated on-chip and localized to the color sensing photodiodes, minimizes
     * the IR spectral component of the incoming light and allows color measurements to be made accurately.
     *
     * The TCS3472 is controlled and monitored by data registers and a command register accessed through the
     * serial interface. These registers provide for a variety of control functions and can be read to determine
     * results of the ADC conversions.
     */
    class TCS34725 : public I2CInterface, public Sensor
    {
      public:
        /// Device address (slave)
        static const uint8_t DEVICE_ADDRESS = 0x29;
  
        /**
         * Register addresses
         */
        enum _address {
          //! Specifies register address: 7th bit to 1 for command and 6th and 5th bits to 01  for auto-increment protocol transaction
          CMD_BITS = 0xA0,
  
          //! Enables states and interrupts
          ENABLE_ADDR  = 0x00,
  
          //! RGBC time
          ATIME_ADDR   = 0x01,
  
          //! Wait time
          WTIME_ADDR   = 0x03,
  
          //! Configuration
          CONFIG_ADDR  = 0x0D,
  
          //! Control
          CONTROL_ADDR = 0x0F,
  
          //! Device ID
          ID_ADDR      = 0x12,
  
          //! Color address
          COLOR_ADDR   = 0x14,
        };
  
        /**
         * Command values
         */
        enum _values {
          //! Enable: sets PON (bit 0) and AEN (bit 1) to 1 enable wait, WEN (bit 3) to 1 disable interrupt, AIEN (bit 4) to 0
          ENABLE_VALUE  = 0x0B,
  
          //! Control: 0x00 :  1 x gain,  0x01 :  4 x gain, 0x10 : 16 x gain, 0x11 : 60 x gain
          CONTROL_VALUE = 0x01,
  
          //! RGBC time: 256 - roundTowardsZero( itime / 2.4 ); 0xFF : 2.4 ms,  0xF6 :  24 ms, 0xD5 : 101 ms, 0xC0 : 154 ms, 0x00 : 700 ms
          ATIME_VALUE   = 0xC0,
  
          //! Wait time: T=5s : 256 - roundTowardsZero( 5000 / 28.8 ) = 0x53; T=1s : 256 - roundTowardsZero( 5000 / 28.8 ) = 0xDD;
          WAIT_TIME_VALUE  = 0x53,
  
          //! Coefficient for red component to convert in LUX with gain = 1, atime = 154
          R_COEFF = 136,
  
          //! Coefficient for green component to convert in LUX with gain = 1, atime = 154
          G_COEFF = 1000,
  
          //! Coefficient for blie component to convert in LUX with gain = 1, atime = 154
          B_COEFF = -444,
  
          //! Coefficient to convert in LUX with gain = 1, atime = 154
          CPL    = 497,
        };
  
        /**
         * Default Constructor.
         * Sets the device address.
         *
         */
        TCS34725();
  
        /**
         * Copy Constructor.
         *
         * \param[in] s i2c sensor object
         */
        TCS34725(const TCS34725 &s);
  
        /**
         * Destructor.
         */
        virtual ~TCS34725();
  
        /**
         * Override operator =
         *
         * \param[in] s source signal object
         *
         * \return destination signal reference
         */
        TCS34725 & operator=(const TCS34725 &s);
  
        /**
         * Tests if the device is connected.
         * Make sure the device is connected and responds as expected.
         *
         * \return true if connection is valid, false otherwise
         */
        virtual bool isConnected();
  
  
        /**
         * Initializes the i2c device: power on and prepare for general usage.
         * This function sets up the \e ATIME, \e WTIME, \e Gain Control and \e ADs \e and \e oscillator values defined in 
         * smrtobj::i2c::TCS34725::_values.
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool initialize();
  
        /**
         * Reads data from the i2c device. This function read 8 byte:
         *   - 1st byte clear component, (Byte0) is the less significant byte
         *   - 2nd byte clear component, (Byte1) is the most significant byte
         *   - 3rd byte red component, (Byte0) is the less significant byte
         *   - 4th byte red component, (Byte1) is the most significant byte
         *   - 5th byte green component, (Byte0) is the less significant byte
         *   - 6th byte green component, (Byte1) is the most significant byte
         *   - 7th byte blue component, (Byte0) is the less significant byte
         *   - 8th byte blue component, (Byte1) is the most significant byte
         *
         * Data is calculate as:
         *
         * \code{.cpp}
         *   value = (Byte1] << 8) | Byte0;
         * \endcode
         *
         * The value read is stored into the internal buffer \e m_value.
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool read();
  
        /**
         * Converts components in Lux value.
         *
         * \code{.cpp}
         * float ir = ( ( red + green + blue - clear ) / 2 );
         * float lux = ( R_COEFF * ( red - ir) + G_COEFF * ( green - ir) + B_COEFF * ( blue - ir) ) / CPL;
         * \endcode
         *
         * \return value in Lux
         */
        virtual float measure();
  
        /**
         * Returns the clear component of the last sensor reading.
         *
         * \return clear component
         */
        uint16_t clear_color() { return m_clear; };
  
        /**
         * Returns the red component of the last sensor reading.
         *
         * \return red component
         */
        uint16_t red_color()   { return m_red; };
  
        /**
         * Returns the green component of the last sensor reading.
         *
         * \return green component
         */
        uint16_t green_color() { return m_green; };
  
        /**
         * Returns the blue component of the last sensor reading.
         *
         * \return blue component
         */
        uint16_t blue_color()  { return m_blue; };
  
      private:
        /**
         * Creates code of a command as Register + Command_Mask
         *
         * \param[in]value register value
         *
         * \return command
         */
        uint8_t create_command(uint8_t value);
  
        //! Clear component
        unsigned int m_clear;
  
        //! Red component
        unsigned int m_red;
  
        //! Green component
        unsigned int m_green;
  
        //! Blue component
        unsigned int m_blue;
  
    };
    
  } /* namespace i2c */

} /* namespace smrtobj */

#endif /* TCS34725_H_ */
