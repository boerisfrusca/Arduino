/**
 * \file ADS1100.h
 * \brief  ADS1100 is a class to handle an I2C ADC ADS1100.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef ADS1100_H_
#define ADS1100_H_

#include <interfaces/i2cinterface.h>
  
 namespace smrtobj
{
  
  namespace i2c
  {
  
    /**
     * Class ADS1100 models the Analog-to-Digital (A/D) converter TI ADS1100.
     * The ADS1100 is a precision, continuously self-calibrating ADC with differential inputs and up to 16 bits
     * of resolution in a small SOT23-6 package. Conversions are performed ratiometrically, using the power supply
     * as the reference voltage. The ADS1100 uses an I2C-compatible serial interface and operates from a single
     * power supply ranging from 2.7V to 5.5V.
     *
     */
    class ADS1100: public I2CInterface, public smrtobj::io::Sensor
    {
      public:
        //! Device address used by default
        static const uint8_t DEVICE_ADDRESS = 0x48;
  
        /**
         * Default Constructor.
         *
         */
        ADS1100();
  
        /**
         * Constructor.
         * Sets the device address.
         *
         * \param[in] addr device address
         */
        ADS1100(uint8_t addr);
  
        /**
         * Copy Constructor.
         *
         * \param[in] d i2c device object
         */
        ADS1100(const ADS1100 &d);
  
        /**
         * Destructor.
         */
        virtual ~ADS1100();
  
        /**
         * Override operator =
         *
         * \param[in] d source device object
         *
         * \return destination device reference
         */
        ADS1100 & operator=(const ADS1100 &d);
  
        /**
         * Initializes the i2c device: power on and prepare for general usage.
         * Nothing is required by this device, it returns always true
         *
         * \return always true.
         */
        virtual bool initialize();
  
        /**
         * Tests if the device is connected.
         * Make sure the device is connected and responds as expected.
         *
         * \return true if connection is valid, false otherwise
         */
        virtual bool isConnected();
  
        /**
         * Reads data from the i2c device. This function read 2 byte:
         *   - 1st byte (Byte0) is the most significant byte
         *   - 2nd byte (Byte1) is the less significant byte
         *
         * Data is calculate as:
         *
         * \code{.cpp}
         *   value = (Byte0] << 8) | Byte1;
         * \endcode
         *
         * The value read is stored in the internal buffer (\e m_value).
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool read();
  
        /**
         * Converts data read (saved in \e m_value variable) in voltage.
         * Note: To be changed!! now it use the formula of ADS1110. Example:
         *
         * \code{.cpp}
         * smrtobj::i2c::ASD1100 adc(0x48);
         * 
         * // Test if device is connected 
         * if( adc.isConnected() )
         * {
         *   if ( adc.read() )
         *   {
         *     float voltage = adc.measure();
         *     ...
         *   }
         * }
         * \endcode
         *
         * \return last data read as voltage level.
         */
        virtual float measure();
  
        /**
         * Returns last ADC value read. Example:
         *
         * \code{.cpp}
         * smrtobj::i2c::ASD1100 adc(0x48);
         * 
         * // Test if device is connected 
         * if( adc.isConnected() )
         * {
         *   if ( adc.read() )
         *   {
         *     uint16_t adc_value = adc.value();
         *     ...
         *   }
         * }
         * \endcode
         * 
         * \return last value read
         */
        uint16_t value() { return m_value; }
  
      private:
        //! Last value read
        uint16_t m_value;
    };
  
  } /* namespace i2c */
  
} /* namespace smrtobj */
  
  #endif /* ADS1100_H_ */
  