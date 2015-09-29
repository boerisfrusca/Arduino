/**
 * \file digitalactuator.h
 * \brief  DigitalActuator models a generic digital actuator. It can assume two different state: on or off.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef DIGITALACTUATOR_H_
#define DIGITALACTUATOR_H_

#include <Arduino.h>
#include "interfaces/signal.h"
#include "interfaces/outputdevice.h"
#include "iosignal.h"

namespace smrtobj
{
  /**
   * The DigitalActuator class models a generic actuator. It changes the output of a digital
   * output to HIGH or LOW. Actuator can have two different state \c ON or \c OFF and works
   * in \c positive (HIGH means ON and LOW means OFF) or negative (HIGH means OFF and LOW
   * means ON) logic.
   *
   */
  class DigitalActuator: public OutputDevice, public DigitalOutput
  {
      //! true if actuator works in negative logic (0 (LOW): on, 1 (HIGH: off)
      bool m_negate;

    public:
      /**
       * Default Constructor.
       * It initializes the state of the actuator to switched off and the output pin
       * to 0. The actuator works in positive logic by default (HIGH: turn on,
       * LOW: turn off).
       */
      DigitalActuator();

      /**
       * Copy constructor.
       *
       * \param[in] a source digital actuator
       *
       */
      DigitalActuator(const DigitalActuator &a);

      /**
       * Destructor.
       *
       */
      virtual ~DigitalActuator();

      /**
       * Override operator =
       *
       * \param[in] a source digital actuator
       *
       * \return reference to the destination digital actuator
       */
      DigitalActuator & operator=(const DigitalActuator &a);

      /**
       * Initializes all attributes of the actuator and switches it off.
       *
       * \param[in] pin number of the output pin
       * \param[in] negate true if actuator works in negative logic, false otherwise
       *
       * \return true if there are errors, false otherwise
       */
      bool init(byte pin, bool negate = false);

      /**
       * Switches the actuator on
       *
       * \return true if there are no errors, false otherwise
       */
      virtual bool on();

      /**
       * Switches the actuator off
       *
       * \return true if there are no errors, false otherwise
       */
      virtual bool off();

  };

} /* namespace smrtobj */

#endif /* DIGITALACTUATOR_H_ */
