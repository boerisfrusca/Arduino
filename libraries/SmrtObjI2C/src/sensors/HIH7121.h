/**
 * \file HIH7121.h
 * \brief  HIH7121 is a class to handle an I2C HIH7121 relative humidity/temperature sensor.
 *
 * \author Marco Boeris Frusca
 *
 */

#ifndef HIH7121_H_
#define HIH7121_H_

#include <interfaces/i2cinterface.h>

namespace smrtobj
{

  namespace i2c
  {

    /**
     * Class HIH7121 models a Honeywell HumidIcon Digital Humidity/Temperature Sensors.
     * The HIH7121 is re digital output-type relative humidity (RH) and temperature sensors combined in the
     * same package.
     *
     */
    class HIH7121 : public I2CInterface, public smrtobj::io::Sensor
    {
      public:
        //! Device address used by default
        static const uint8_t DEVICE_ADDRESS = 0x27;


        /**
         * Default Constructor.
         *
         */
        HIH7121();


        /**
         * Constructor.
         * Sets the device address.
         *
         * \param[in] addr device address
         */
        HIH7121(uint8_t addr);


        /**
         * Copy Constructor.
         *
         * \param[in] d i2c device object
         */
        HIH7121(const HIH7121 &d);

        /**
         * Destructor.
         */
        virtual ~HIH7121();

        /**
         * Override operator =
         *
         * \param[in] d source device object
         *
         * \return destination device reference
         */
        HIH7121 & operator=(const HIH7121 &d);

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
         * Reads data from the i2c device. This function read 4 byte:
         *   - 1st byte (Byte0) Status + Humidity MSB
         *   - 2nd byte (Byte1) Humidity lSB
         *   - 3nd byte (Byte1) Temperature MSB
         *   - 4nd byte (Byte1) Temperature LSB
         *
         * Honeywell digital output humidity sensors offer status bits to ensure robust system operation in
         * critical applications. The sensor status is indicated by the first two Most Significant Bits of
         * Data Byte 1. When the status bits read "01", "Stale" data is indicated. This means that the data
         * in the output buffer of the sensor has already been fetched by the master, and has not yet been
         * updated with the new data from the current measurement cycle. This can happen when the master polls
         * the data quicker than the sensor can update the output buffer. "00" means "Normal Operation",
         * valid data that has not been fetched since the last measurement cycle.
         *
         * The value read is stored in the internal buffer (\e m_value).
         *
         * \return true for success, or false if any error occurs.
         */
        virtual bool read();

        /**
         * Returns relative humidity measurement.
         *
         * \return relative humidity.
         */
        virtual float measure();

        /**
         * Returns the status of the last reading.
         * Values are :
         *
         * - 0x00 : Normal Operation, Valid Data that has not  been fetched since the last measurement cycle.
         * - 0x01 : Stale Data: Data that has already been fetched since the last measurement cycle, or data fetched before the first measurement has been completed.
         * - 0x02 : Device in Command Mode
         * - 0x03 - 0xFF : value not used.
         *
         * \return status
         */
        uint8_t status();

        /**
         * The output of the device is simply a 14 bit number representing between 0 %RH and 100 %RH:
         *
         *   - 0 %RH = 0 counts
         *   - 100% RH = 2^14 - 2 counts
         *
         * Humidity Conversion Function is :
         *
         * \code{.cpp}
         * float rh = ( rh_count / 16382 ) * 100; // 2^14 - 2 = 16382
         * \endcode
         *
         * \return relative humidity
         */
        float humidity();

        /**
         * For sensors with the optional compensated temperature output, the output of the device is simply
         * a 14 bit number representing between -40 C and 125 C :
         *   - -40 C = 0 counts
         *   - 125 C = 2^14 - 2 counts
         *
         * Temperature Conversion Function is :
         *
         * \code{.cpp}
         * float rh = ( ( t_count / 16382 ) * 165 ) - 40; // 2^14 - 2 = 16382
         * \endcode
         *
         * \return temperature
         */
        float temperature();

      private:
        uint8_t m_status;

        uint16_t m_humidity;

        uint16_t m_temperature;
    };

  } /* namespace i2c */

} /* namespace smrtobj */

#endif /* HIH7121_H_ */
