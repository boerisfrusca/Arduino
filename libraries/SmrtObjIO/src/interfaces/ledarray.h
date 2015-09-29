/**
 * \file ledarray.h
 * \brief  LEDarray is an interface to model an array of LEDs.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef LEDARRAY_H_
#define LEDARRAY_H_

#include <Arduino.h>
#include "interfaces/signal.h"
#include "actuator/digitalactuator.h"
#include "iosignal.h"


namespace smrtobj
{
  /**
   * This class models an LED array to give feedback about the state of the object.
   * This is a abstract class.
   *
   * To create an specific array of LED, you have to create e new class, inheriting from
   * LEDArray class and you have to redefine the functions:
   * - check;
   * - attach;
   * - change;
   *
   * The new class have to define an array of pointer to DigitalActuator object where each
   * digital actuator is a LED.\n
   * The function \b check will call the static class function \c check using as arguments
   * the array of DigitalActuator pointer and the array size. The function "attach" will
   * initialize the array at \c pos  position, coping here the address of the "digital actuator"
   * object. The function "chance" will change the state of LED according to the state value. \n
   * For example:
   *
   * \code{.cpp}
   *   #include <smrtobjio.h>
   *
   *   ...
   *
   *   class MyLEDs: public smrtobj::LEDArray
   *   {
   *     public:
   *       //! Number of debug LEDs
   *       static const byte N_LEDS = 2;
   *
   *       OutputLED();
   *       ~OutputLED();
   *
   *       ...
   *
   *       virtual bool check();
   *       virtual bool attach(smrtobj::DigitalActuator &led, byte pos);
   *       virtual bool change(byte state);
   *
   *       private:
   *         //! Array of pointer to the outpu LEDs
   *         smrtobj::DigitalActuator *m_leds[N_LEDS];
   *   }
   *
   *   bool MyLEDs::attach(smrtobj::DigitalActuator &led, byte pos)
   *   {
   *     m_leds[pos] = &led;
   *
   *     return true;
   *   }
   *
   *   bool MyLEDs::check()
   *   {
   *     return StateLED::check(m_leds, N_LEDS);
   *   }
   *
   *   bool MyLEDs::change(byte state)
   *   {
   *     switch (state)
   *     {
   *       case 0:
   *       {
   *         m_state = state;
   *         m_leds[0]->off();
   *         m_leds[1]->off();
   *       }
   *       break;
   *       case 1:
   *       {
   *         m_state = state;
   *         m_leds[0]->off();
   *         m_leds[1]->on();
   *       }
   *       break;
   *       case 2:
   *       {
   *         m_state = state;
   *         m_leds[0]->on();
   *         m_leds[1]->off();
   *       }
   *       break;
   *       case 3:
   *       {
   *         m_state = state;
   *         m_leds[0]->on();
   *         m_leds[1]->on();
   *       }
   *       break;
   *       default:
   *       {
   *         m_state = state;
   *         m_leds[0]->off();
   *         m_leds[1]->off();
   *       }
   *     }
   *     return true;
   *   }
   *
   * \endcode
   *
   *
   */
  class LEDArray
  {
    protected:
      //! Time of blinking during the LED array check
      static const unsigned int CHECK_TIME = 1000;

      /**
       * Its blinks a generic array of LEDs. This operation can be used to check if
       * all LEDs are working correctly.
       *
       * \param[in] ledsArray pointer to the LED array
       * \param[in] size size of the LED array
       */
      static bool check(smrtobj::DigitalActuator** ledsArray, byte size);

      //! State of the LED array
      byte m_state;

    public:
      /**
       * Default Constructor.
       * It initializes the state of the LED array
       */
      LEDArray();

      /**
       * Copy constructor.
       *
       */
      LEDArray(const LEDArray &l);

      /**
       * Destructor.
       *
       */
      virtual ~LEDArray();

      /**
       * Gets the current state of the LED array
       *
       * \return the current state of the LED array
       */
      byte state() const { return m_state; }

      /**
       * Checks if all LEDs works correctly, blinking them for #smrtobj::LEDArray::CHECK_TIME milliseconds
       *
       * \return true if no errors, false otherwise
       */
      virtual bool check() = 0;

      /**
       * Attaches a new LED (as a digital actuator) to the state LED array.
       *
       * \return true if no errors, false otherwise
       */
      virtual bool attach(DigitalActuator &led, byte pos) = 0;

      /**
       * Changes the LEDs according the new state
       *
       * \return true if no errors, false otherwise
       */
      virtual bool change(byte state) = 0;
  };
} /* namespace smrtobj */

#endif /* LEDARRAY_H_ */
