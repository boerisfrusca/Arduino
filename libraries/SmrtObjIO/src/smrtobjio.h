/**
 * \file smrtobjio.h
 * \brief This header gathers headers of all sub-directory library. This is
 * \brief necessary because the files do not get copied to the temporary compilation
 * \brief directory by arduino IDE.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef SMRTOBJIO_H_
#define SMRTOBJIO_H_


// Interfaces
#include "interfaces/ledarray.h"
#include "interfaces/outputdevice.h"
#include "interfaces/sensor.h"
#include "interfaces/sensortemperature.h"
#include "interfaces/signal.h"


// Actuators
#include "actuator/digitalactuator.h"

// Sensors
#include "sensor/analogsensor.h"
#include "sensor/sensorbase.h"
#include "sensor/mcp9700a.h"

// IO signals
#include <iosignal.h>


#endif /* SMRTOBJIO_H_ */
