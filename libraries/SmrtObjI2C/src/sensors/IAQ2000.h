/*
 * IAQ2000.h
 *
 *  Created on: Oct 14, 2015
 *      Author: boeris
 */

#ifndef IAQ2000_H_
#define IAQ2000_H_

#include <interfaces/i2cinterface.h>
#include <I2Cdev.h>

namespace smrtobj
{

class IAQ2000 : public I2CInterface, public Sensor
{
  public:

    static const uint8_t DEVICE_ADDRESS = 0x5A;

    static const uint8_t RA_DATA1 = 0x00;
    static const uint8_t RA_DATA2 = 0x01;

    IAQ2000();
    IAQ2000(const IAQ2000 &s);
    virtual ~IAQ2000();

    /**
     * Override operator =
     *
     * \param[in] s source signal object
     *
     * \return destination signal reference
     */
    IAQ2000 & operator=(const IAQ2000 &s);

    virtual bool testConnection();
    virtual bool initialize();
    virtual bool read();
    virtual float measure();

  private:

    /**  Read bytes from a slave device.
     * This is a "stripped-down" version of the standard Jeff Rowberg's I2Cdev::readBytes method
     * intended to provide compatibility with iAQ-2000,
     * which apparently does not support setting of an address pointer to indicate from which position is to start read from.
     * @param devAddr Address of the slave device to read bytes from
     * @param length Number of bytes to read
     * @param data Buffer to store read data in
     * @param timeout Optional read timeout in milliseconds (0 to disable, leave off to use default class value in I2Cdev::readTimeout)
     * @return Number of bytes read (0 indicates failure)
     */
    int8_t readAllBytes(uint8_t devAddr, uint8_t length, uint8_t *data, uint16_t timeout=I2Cdev::readTimeout);
    uint16_t m_value;

};

} /* namespace smrtobj */

#endif /* IAQ2000_H_ */
