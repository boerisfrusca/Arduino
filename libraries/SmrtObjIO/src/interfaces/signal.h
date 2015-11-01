/**
 * \file signal.h
 * \brief Signal is an interface to model every input or output signal of an Arduino board.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef Signal_H_
#define Signal_H_

#if ARDUINO >= 100
#include "Arduino.h"       // for delayMicroseconds, digitalPinToBitMask, etc
#else
#include "WProgram.h"      // for delayMicroseconds
#include "pins_arduino.h"  // for digitalPinToBitMask, etc
#endif

namespace smrtobj
{

  namespace io
  {
    /**
     * Signal is an abstract class to model an interface for every I/O signal of an Arduino board.
     * It is possible define the type of signal (Input or Output).
     *
     * \b TYPE_INPUT
     * Arduino (Atmega) pins configured as INPUT with pinMode() are said to be in a high-impedance state.
     * Pins configured as INPUT make extremely small demands on the circuit that they are sampling,
     * equivalent to a series resistor of 100 Megohms in front of the pin. This makes them useful for reading
     * a sensor.
     *
     * \b TYPE_OUTPUT
     * Pins configured as OUTPUT are said to be in a low-impedance state. This means that they can provide a
     * substantial amount of current to other circuits. Atmega pins can source (provide current) or sink
     * (absorb current) up to 40 mA (milliamps) of current to other devices/circuits. This makes them useful
     * for powering LEDs because LEDs typically use less than 40 mA.
     * Loads greater than 40 mA (e.g. motors) will require a transistor or other interface circuitry.\n
     * Pins configured as outputs can be damaged or destroyed if they are connected to either the ground or
     * positive power rails.
     *
     */
    class Signal
    {
      public:
        /**
         * \enum  _type
         *
         * Type of signal
         */
        enum _type
        {
          //! Not initialized
          NOT_INITIALIZED = 0x00,
  
          //! Input
          TYPE_INPUT = 0x01,
  
          //! Output
          TYPE_OUTPUT = 0x02,
  
          //! bidirectional
          TYPE_BIDIRECTIONAL = 0x03,
        };
  
        /**
         * Default Constructor.
         * It initializes all attribute of the signal interface: type will be not initialized and state will
         * be not opened yet.
         */
        Signal();
  
        /**
         * Copy Constructor.
         *
         * \param[in] s source signal object
         *
         */
        Signal(const Signal &s);
  
        /**
         * Destructor.
         *
         */
        virtual ~Signal();
  
  
        /**
         * Override operator =
         *
         * \param[in] s source signal object
         *
         * \return destination signal reference
         */
        Signal & operator=(const Signal &s);
  
  
        /**
         * Virtual method, it gets the type of the interface according to smrtobj::io::Signal::_type enum
         *
         * \return the type of the signal interface
         */
        virtual byte type() = 0;
  
        /**
         * Checks if the interface is open or not
         *
         * \return false if the interface is not initialized yet, true otherwise
         */
        bool isOpen() { return m_open; }
  
      protected:
        //! Signal interface type
        byte m_type;
  
        //! false if the interface is not initialized yet, true otherwise
        bool m_open;
    };
  
  } /* namespace io */
  
} /* namespace smrtobj */

#endif /* Signal_H_ */
