/**
 * \file smrtobji2c.h
 * \brief This header gathers headers of all sub-directory library. This is
 * \brief necessary because the files do not get copied to the temporary compilation
 * \brief directory by arduino IDE.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef SMRTOBJI2C_H_
#define SMRTOBJI2C_H_

// Interfaces
#include "interfaces/signal.h"
#include "interfaces/i2cinterface.h"

// Sensors
#include "sensors/TCS34725.h"  // Lighting
#include "sensors/IAQ2000.h"   // VOC
#include "sensors/ADS1100.h"   // CH2O

// Devices (multiplexer, driver, etc)
#include "devices/PCA9548A.h"  // I2C multiplexer
#include "devices/TCA6507.h"   // LED driver
#include "devices/PIC24FV32KA301.h"   // PIC
#endif /* SMRTOBJI2C_H_ */
