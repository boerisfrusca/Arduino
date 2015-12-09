/**
 * \file T6713.h
 * \brief  T6713 is a class to handle an I2C Co2 meter.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef T6713_H_
#define T6713_H_

#include <interfaces/i2cinterface.h>
  
 namespace smrtobj
{
  
  namespace i2c
  {
  
    /**
     * Class T6713 models the ....
     *
     */
    class T6713: public I2CInterface, public smrtobj::io::Sensor
    {
      public:
        /**
         * Command addresses
         */
        enum _cmd_address{
          //! Read
          FUNCTION_READ = 0x04,

          //! Get firmware version
          FIRMWARE = 0x1389,

          //! Get status
          STATUS = 0x138A,

          //! Read contration
          GAS_PPM = 0x138B,

        };

        /**
         * Status values
         */
        enum _status
        {
          //! Generic rrror
          ERROR = 0x0001,

          //! Flash error
          FLASH_ERROR = 0x0002,

          //! Calibration error
          CALIBRATION_ERROR = 0x0004,

          /// RS-232
          RS232 = 0x0100,

          /// RS-285
          RS485 = 0x0200,

          //! I2C
          I2C = 0x0400,

          //! Sensor is in warm-up mode
          WARMUP_MODE = 0x0800,

          //! Single point calibration
          SINGLE_POINT_CALIBRATION = 0x8000,

        };
        //! Device address used by default
        static const uint8_t DEVICE_ADDRESS = 0x15;
  
        /**
         * Default Constructor.
         *
         */
        T6713();
  
        /**
         * Copy Constructor.
         *
         * \param[in] d i2c device object
         */
        T6713(const T6713 &d);
  
        /**
         * Destructor.
         */
        virtual ~T6713();
  
        /**
         * Override operator =
         *
         * \param[in] d source device object
         *
         * \return destination device reference
         */
        T6713 & operator=(const T6713 &d);
  
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
         * Read status.
         *
         * \return true for success, or false if any error occurs.
         */
        bool readStatus();
  
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
        uint16_t rgstr() { return m_register; }

      protected:

        /**
         * Read a register of a specific command.
         *
         * \param[in] cmd command register value.
         *
         * \return true for success, or false if any error occurs.
         */
        bool read(uint16_t cmd);

        /**
         * Set internal register to a specific value.
         *
         * \param[in] value value to write in to the internal register.
         */
        void setRgstr(uint16_t value) { m_register = value; }

      private:
        //! Last value read
        uint16_t m_register;
    };
  
  } /* namespace i2c */
  
} /* namespace smrtobj */
  
  #endif /* ADS1100_H_ */
  
