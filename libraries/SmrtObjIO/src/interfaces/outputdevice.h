/**
 * \file outputdevice.h
 * \brief  OutputDevice is an interface to model a signal output connected to an actuator.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef OUTPUTDEVICE_H_
#define OUTPUTDEVICE_H_

#include <Arduino.h>

namespace smrtobj
{

  namespace io
  {
  
    /**
     * OutputDevice is an abstract class to model an interface for output signal connected to an actuator.
     */
    class OutputDevice
    {
      public:
        /**
         * \enum  _state
         *
         * State for an actuator
         */
        enum _state
        {
          //! Switched off
          OFF = 0x00,
  
          //! Switched on
          ON = 0x01,
        };
  
        /**
         * Default Constructor.
         * It initializes the state of the actuator to switched off
         */
        OutputDevice();
  
        /**
         * Destructor.
         *
         */
        virtual ~OutputDevice();
  
        /**
         * Gets the state of the actuator.
         *
         * \return actuator state according to #_state enum
         */
        byte state() { return m_state; }
  
        /**
         * Checks actuator state.
         *
         * \return true if actuator is switched on, false otherwise
         */
        bool isOn() { return m_state == ON; };
  
        /**
         * Switches the actuator on
         *
         * \return true if there are no errors, false otherwise
         */
        virtual bool on() = 0;
  
        /**
         * Switches the actuator off
         *
         * \return true if there are no errors, false otherwise
         */
        virtual bool off() = 0;
  
      protected:
        //! State of the actuator. It can be ON or OFF (smrtobj::io::OutputDevice::_state)
        byte m_state;
  
    };
  
  } /* namespace io */
  
} /* namespace smrtobj */

#endif /* OUTPUTDEVICE_H_ */
