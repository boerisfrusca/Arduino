/**
 * \file i2cinterface.h
 * \brief Classes to model I2C device.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef I2CINTERFACE_H_
#define I2CINTERFACE_H_

#include <smrtobjio.h>
#include <I2Cdev.h>

namespace smrtobj
{

  class I2CInterface : public Signal
  {
    public:
      I2CInterface();
      I2CInterface(uint8_t addr);
      I2CInterface(const I2CInterface &d);
      virtual ~I2CInterface();

      uint8_t address() { return m_device_addr; }

      /**
       * Gets the type of the interface according to #smrtobj::Signal::_type enum
       *
       * \return type of the interface
       */
      byte type() {return m_type; }

      /**
       * Override operator =
       *
       * \param[in] s source signal object
       *
       * \return destination signal reference
       */
      I2CInterface & operator=(const I2CInterface &s);

      virtual bool testConnection() = 0;
      virtual bool initialize() = 0;
      virtual bool read() = 0;

    private:
      uint8_t m_device_addr;
  };

} /* namespace smrtobj */

#endif /* I2CINTERFACE_H_ */
