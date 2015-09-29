/**
 * \file outputdevice.cpp
 * \brief  OutputDevice is an interface to model a signal output connected to an actuator.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "outputdevice.h"

namespace smrtobj
{

  OutputDevice::OutputDevice() : m_state(OFF)
  {
  }

  OutputDevice::~OutputDevice()
  {
  }

} /* namespace smrtobj */
