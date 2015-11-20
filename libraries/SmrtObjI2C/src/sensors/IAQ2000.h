/**
 * \file IAQ2000.h
 * \brief  IAQ2000 is a class to handle an iAQ-2000 Indoor Air Quality (VOC) Sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef IAQ2000_H_
#define IAQ2000_H_

#include <interfaces/i2cinterface.h>

namespace smrtobj
{

  namespace i2c
  {

    /**
     * Class IAQ2000 models the I2C iAQ2000 sensor.
     * The iAQ2000 is designed to sense the level of volatile organic compounds (VOCs) such as smoke, cooking odors,
     * bio-effluence and pollutants.
     * This sensor gives a direct and reliable correlation to CO2 levels: output in ppm (parts-per-million):
     * predicted CO2 concentration based on human induced volatile organic compounds (VOC) detection
     * (in ppm VOC + CO2 equivalents)
     *
     */
  
    class IAQ2000 : public I2CInterface, public smrtobj::io::Sensor
    {
      public:
        //! Device address used by default
        static const uint8_t DEVICE_ADDRESS = 0x5A;
  
        /**
         * Default Constructor.
         * Sets the device address.
         * 
         */
        IAQ2000();
  
        /**
         * Copy Constructor.
         *
         * \param[in] s i2c sensor object
         */
        IAQ2000(const IAQ2000 &s);
  
        /**
         * Destructor.
         */
        virtual ~IAQ2000();
  
        /**
         * Override operator =
         *
         * \param[in] s source signal object
         *
         * \return destination signal reference
         */
        IAQ2000 & operator=(const IAQ2000 &s);
  
        /**
         * Initializes the i2c device: power on and prepare for general usage.
         * Nothing is required by this device.
         *
         * \return true for success, or false if any error occurs.
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
         * Data is calculate as:
         *   value = (Byte0] << 8) | Byte1;
         * The value read is stored in m_value.
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool read();
  
        /**
         * Returns last data read as a floating point number.
         *
         * \return last data read
         */
        virtual float measure();
  
        /**
         * Returns last value read as unsigned integer of 16 bits.
         *
         * \return last value read
         */
        uint16_t value() { return m_value; }

        /**
         * Returns status of the last reading:
         *
         *   - 0x00 : OK
         *   - 0x01 : BUSY (re-read multi byte data!)
         *   - 0x10 : RUNIN (module in warm up phase)
         *   - 0x80 : ERROR (if constant: replace sensor)
         *
         * \return status
         */
        uint8_t status() { return m_status; };

        /**
         * Returns the resistance value:
         *
         * \return resistance value
         */
        uint32_t resistance() { return m_resistance; };

        /**
         * Returns the tVOC value:
         *
         * \return resistance value
         */
        uint16_t tVOC() { return m_tvoc; };

      private:
        //! Last value read
        uint16_t m_value;

        //! status
        uint8_t m_status;

        //! status
        uint32_t m_resistance;

        //! status
        uint16_t m_tvoc;

    };
  
  } /* namespace i2c */

} /* namespace smrtobj */

#endif /* IAQ2000_H_ */
