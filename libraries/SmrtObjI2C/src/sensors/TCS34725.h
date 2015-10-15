/*
 * TCS34725.h
 *
 *  Created on: Oct 14, 2015
 *      Author: boeris
 */

#ifndef TCS34725_H_
#define TCS34725_H_

#include <interfaces/i2cinterface.h>
#include <I2Cdev.h>

namespace smrtobj
{

  class TCS34725 : public I2CInterface, public Sensor
  {
    public:
      static const uint8_t CMD_BITS = 0xA0;        // 7th bit to 1 for command and
                                                   // 6th and 5th bits to 01  for auto-increment protocol transaction
      /// Device address (slave)
      static const uint8_t DEVICE_ADDRESS = 0x29;

      // Address
      static const uint8_t ENABLE_ADDR  = 0x00;
      static const uint8_t ATIME_ADDR   = 0x01;
      static const uint8_t CONTROL_ADDR = 0x0F;
      static const uint8_t WTIME_ADDR   = 0x03;
      static const uint8_t CONFIG_ADDR  = 0x0D;

      static const uint8_t ID_ADDR      = 0x12;     // 0x12 + 0xa0
      static const uint8_t COLOR_ADDR   = 0xb4;     // register address + command bits

      // Values
      static const uint8_t ENABLE_VALUE  = 0x0B;    // sets PON (bit 0) and AEN (bit 1) to 1
                                                    // enable wait, WEN (bit 3) to 1
                                                    // disable interrupt, AIEN (bit 4) to 0

      static const uint8_t CONTROL_VALUE = 0x01;    // 0x00 :  1 x gain
                                                    // 0x01 :  4 x gain
                                                    // 0x10 : 16 x gain
                                                    // 0x11 : 60 x gain


      static const uint8_t ATIME_VALUE   = 0xC0;    // 256 - roundTowardsZero( itime / 2.4 )
                                                    // 0xFF : 2.4 ms
                                                    // 0xF6 :  24 ms
                                                    // 0xD5 : 101 ms
                                                    // 0xC0 : 154 ms
                                                    // 0x00 : 700 ms

      static const uint8_t WAIT_TIME_VALUE  = 0xDD; // T=5s : 256 - roundTowardsZero( 5000 / 28.8 ) = 0x53;
                                                    // T=1s : 256 - roundTowardsZero( 5000 / 28.8 ) = 0xDD;

      static const int16_t R_COEFF = 136;
      static const int16_t G_COEFF = 1000;
      static const int16_t B_COEFF = -444;
      static const int16_t CPL    = 497;     // gain = 1, atime = 154

      TCS34725();
      TCS34725(const TCS34725 &s);
      virtual ~TCS34725();

      /**
       * Override operator =
       *
       * \param[in] s source signal object
       *
       * \return destination signal reference
       */
      TCS34725 & operator=(const TCS34725 &s);

      virtual bool testConnection();
      virtual bool initialize();
      virtual bool read();
      virtual float measure();

      uint16_t clear_color() { return m_clear; };
      uint16_t red_color()   { return m_red; };
      uint16_t green_color() { return m_green; };
      uint16_t blue_color()  { return m_blue; };

    private:
      uint8_t create_command(uint8_t value);

      unsigned int m_clear;
      unsigned int m_red;
      unsigned int m_green;
      unsigned int m_blue;

  };

} /* namespace smrtobj */

#endif /* PCA9548A_H_ */
