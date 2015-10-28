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
#include <I2Cdev.h>

namespace smrtobj
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

  class IAQ2000 : public I2CInterface, public Sensor
  {
    public:
      //! Device address used by default
      static const uint8_t DEVICE_ADDRESS = 0x5A;


      /**
       * Default Constructor.
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
       * \return true if no errors
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
       * \return true if no errors
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

    private:
      //! Last value read
      uint16_t m_value;
  };

} /* namespace smrtobj */

#endif /* IAQ2000_H_ */
