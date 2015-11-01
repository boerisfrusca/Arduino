/**
 * \file iosignal.h
 * \brief Classes to model input and output signal.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef IOSINGAL_H_
#define IOSINGAL_H_

#include <Arduino.h>
#include "interfaces/signal.h"

namespace smrtobj
{

  namespace io
  {
  
    /**
     * The DigitalOutput class models an digital output. Output value can be \b HIGH or
     * \b LOW. The last value written is stored in an internal variable. The default
     * output pin is 0.
     *
     */
    class DigitalOutput : public Signal
    {
      public:
        /**
         * Default Constructor.
         * It initializes the last value written to LOW and the pin number to 0.
         */
        DigitalOutput();
  
        /**
         * Copy Constructor.
         *
         * \param[in] o source digital output
         *
         */
        DigitalOutput(const DigitalOutput &o);
  
        /**
         * Destructor.
         *
         */
        virtual ~DigitalOutput();
  
        /**
         * Override operator =
         *
         * \param[in] o source digital output
         *
         * \return reference to the destination digital output
         */
        DigitalOutput & operator=(const DigitalOutput &o);
  
        /**
         * Gets the type of the interface according to #smrtobj::Signal::_type enum
         *
         * \return type of the interface
         */
        byte type() {return m_type; }
  
        /**
         * Opens the pin and initializes the digital output.
         *
         * \param[in] pin number of the output pin
         *
         */
        void init(byte pin);
  
        /**
         * Gets the last value written.
         *
         * \return last value written
         */
        bool value() { return m_value; }
  
        /**
         * Gets the number of the output pin.
         *
         * \return pin number
         */
        byte pin() { return m_pin; }
  
        /**
         * Writes value on the digital output
         *
         * \param[in] value digital value. It can be LOW  or HIGH
         *
         * \return false if digital output not initialized yet
         */
        bool write(bool value);
  
      private:
        //! Last value written
        bool m_value;
  
        //! Pin number
        byte m_pin;
    };
  
  
    /**
     * The PWMOutput class models a PWM (Pulse Width Modulation) output. It can be used to light
     * a LED at varying brightnesses or drive a motor at various speeds. Writing a value, the pin will
     * generate a steady square wave of the specified duty cycle. This is achieved by \b analogWrite function.
     * PWM duty-cycle is between  0 (always off) and 255 (always on).
     * The default output pin is 0.
     *
     * \b Note: \n
     * Check it out which pins support PWM on your Arduino board and the documentation of analogWrite
     * function if you have an unexpected behavior ( http://arduino.cc/en/Reference/analogWrite ).
     *
     * The PWM outputs generated on pins 5 and 6 will have higher-than-expected duty cycles.
     * This is because of interactions with the millis() and delay() functions, which share the same internal
     * timer used to generate those PWM outputs.
     * This will be noticed mostly on low duty-cycle settings (e.g 0 - 10) and may result in a value of 0
     * not fully turning off the output on pins 5 and 6.
     *
     */
    class PWMOutput : public Signal
    {
      public:
        /**
         * Default Constructor.
         * It initializes the last value written to 0 and the pin number to 0.
         */
        PWMOutput();
  
        /**
         * Copy Constructor.
         *
         * \param[in] o source PWM output
         *
         * \return reference to the destination PWM output
         */
        PWMOutput(const PWMOutput &o);
  
        /**
         * Destructor.
         *
         */
        virtual ~PWMOutput();
  
        /**
         * Override operator =
         *
         * \param[in] o source PWM output
         *
         * \return reference to the destination PWM output
         */
        PWMOutput & operator=(const PWMOutput &o);
  
        /**
         * Gets the type of the interface according to #smrtobj::Signal::_type enum
         *
         * \return type of the interface
         */
        byte type() {return m_type; }
  
        /**
         * Opens the pin and initializes the PWM output, writing 0 as duty cycle.
         *
         * \param[in] pin number of the output pin
         *
         */
        void init(byte pin);
  
        /**
         * Gets the last value written (PWM duty-cycle between 0 and 255).
         *
         * \return last value written
         */
        byte value() { return m_value; }
  
        /**
         * Gets the number of the output pin.
         *
         * \return pin number
         */
        byte pin() { return m_pin; }
  
        /**
         * Writes value on the output pin
         *
         * \param[in] value he duty cycle: between 0 (always off) and 255 (always on)
         *
         * \return false if digital output not initialized yet
         */
        bool write(byte value);
  
      private:
        //! Last value written. This is the duty cycle of the PWM (0-255)
        byte m_value;
  
        //! Pin number
        byte m_pin;
    };
  
  
    /**
     * The DigitalInput class models a digital input. Using this, it is possible read the value from a
     * specified digital pin, either HIGH or LOW.
     *
     */
    class DigitalInput : public Signal
    {
      public:
  
        /**
         * Default Constructor.
         * It initializes the last value read to 0 and the pin number to 0.
         */
        DigitalInput();
  
        /**
         * Copy Constructor.
         *
         * \param[in] o source digital input
         *
         */
        DigitalInput(const DigitalInput &o);
  
        /**
         * Destructor
         *
         */
        virtual ~DigitalInput();
  
        /**
         * Override operator =
         *
         * \param[in] o source digital input
         *
         * \return reference to the destination digital input object
         */
        DigitalInput & operator=(const DigitalInput &o);
  
        /**
         * Gets the type of the interface according to #smrtobj::Signal::_type enum
         *
         * \return type of the interface
         */
        byte type() { return m_type; }
  
        /**
         * Opens the pin in input mode. It is possible use internal pull up resistor.\n
         * The Atmega microcontroller on the Arduino has internal pull-up resistors (resistors that
         * connect to power internally) that you can access. If you prefer to use these instead of
         * external pull-up resistors, you can use pullup argument to true.
         *
         * \param[in] pin number of the input pin
         * \param[in] pullup use internal pull up resistor. Default value is false
         *
         */
        void init(byte pin, bool pullup = false);
  
        /**
         * Gets the last value read.
         *
         * \return last value read (true if HIGH, false if LOW or input has not been opened)
         */
        bool value() { return m_value; }
  
        /**
         * Gets the number of the input pin.
         *
         * \return pin number
         */
        byte pin() { return m_pin; }
  
        /**
         * Reads value from the digital input
         *
         * \return value, it can be HIGH or LOW
         */
        bool read();
  
      private:
        //! Last value written
        bool m_value;
  
        //! Pin number
        byte m_pin;
    };
  
  
    /**
     * The AnalogInput class models a analog input. Using this, it is possible read the value from a
     * specified analog pin.
     *
     * The Arduino board contains a 6 channel (8 channels on the Mini and Nano, 16 on the Mega),
     * 10-bit analog to digital converter. This means that it will map input voltages between 0 and 5 volts
     * into integer values between 0 and 1023. This yields a resolution between readings of: 5 volts / 1024 units
     * or, .0049 volts (4.9 mV) per unit. The input range and resolution can be changed using analogReference().
     *
     * It takes about 100 microseconds (0.0001 s) to read an analog input, so the maximum reading rate is about
     * 10,000 times a second.
     *
     */
    class AnalogInput : public Signal
    {
      public:
        //! ADC resolution
        static const byte RESOLUTION = 10;
  
        //! Default ADC reference voltage
        static const float DEFAULT_VREF = 5.0;
  
        /**
         * Default reference voltage
         */
        enum _v_default
        {
          //! Off, 0.0 Volt
          V0_0 = 0,
  
          //! 5.0 Volt
          V5_0 = 1,
  
          //! 3.3 Volt
          V3_3 = 2,
        };
  
        /**
         * Gets reference voltage for ADCs in volts
         *
         * \return  reference voltage for ADCs
         */
        static float reference();
  
        /**
         * Change reference for ADCs, using default board value. Please check the working voltage for
         * your Arduino board: default analog reference of 5 volts (on 5V Arduino boards) or 3.3 volts
         * (on 3.3V Arduino boards). If \c vdef parameter is not valid (#smrtobj::AnalogSensor::_v_default)
         * all ADCs will be turned off, putting the reference voltage to 0.0V.
         *
         * \b Note:
         * Check the correct default voltage for your Arduino board! This function sets this value in an internal
         * attribute. If it is different from the actual board, reading will give a wrong result.
         *
         * \param[in] vdef analog reference for your Arduino board according to #smrtobj::AnalogSensor::_v_default enum.
         *
         * \return true if  default voltage is correct, false otherwise
         */
        static bool setReferenceDefault(byte vdef = V5_0);
  
        /**
         * Change reference for ADCs, using external reference. The voltage applied to the AREF pin
         * (0 to 5V only) is used as the reference.
         * It is suggested to initialize before the default voltage using smrtobj::AnalogSensor::setReferenceDefault
         * before set an external reference voltage. If you use an invalid voltage as parameter, it will be use
         * the default voltage and return false.
         *
         * \b Note:
         * Check the correct default voltage for your Arduino board! This function sets this value in an internal
         * attribute. If it is different from the actual board, reading will give a wrong result.
         *
         * \param[in] voltage the voltage applied to the AREF pin (0 to 5V only).
         *
         * \return true if voltage is valid, false otherwise
         */
        static bool  setReference(float voltage);
  
        /**
         * Default Constructor
         * It initializes the last value read to 0 and the pin number to 0.
         */
        AnalogInput();
  
        /**
         * Copy Constructor
         *
         * \param[in] o source digital input
         *
         * \return reference to the destination digital input object
  
         */
        AnalogInput(const AnalogInput &o);
  
        /**
         * Destructor
         *
         */
        virtual ~AnalogInput();
  
        /**
         * Override operator =
         */
        AnalogInput & operator=(const AnalogInput &i);
  
        /**
         * Gets the type of the interface according to #smrtobj::Signal::_type enum
         *
         * \return type of the interface
         */
        byte type() {return m_type; }
  
        /**
         * Opens the pin in input mode. It is possible use internal pull up resistor.\n
         * The analog pins also have pullup resistors, which work identically to pullup resistors
         * on the digital pins.\n
         * Be aware however that turning on a pullup will affect the values reported by analogRead().
         *
         * \param[in] pin number of the input pin
         * \param[in] pullup use internal pull up resistor. Default value is false
         */
        void init(byte pin, bool pullup = false);
  
        /**
         * Gets the last value read. If the input has not been opened yet, it returns 0.
         *
         * \return last value read
         */
        unsigned long value() { return m_value; }
  
        /**
         * Gets the number of the analog input pin.
         *
         * \return pin number
         */
        byte pin() { return m_pin; }
  
        /**
         * Reads value from the analog input. If the input has not been opened yet, it returns 0.
         *
         * \return value, it is a number between 0 and 1023
         */
        unsigned long read();
  
        /**
         * Gets value as voltage. Pay attention, this value depends on reference voltage, if it has been set a
         * wrong value for this voltage, function will return a wrong result. See
         * #smrtobj::AnalogSensor::setReferenceDefault and smrtobj::AnalogSensor::setReference
         *
         * \return input value as voltage
         */
        float inputVoltage();
  
      private:
        //! ADC reference voltage
        static float VREF;
  
        //! Last value written
        unsigned long m_value;
  
        //! Pin number
        byte m_pin;
    };
  
  } /* namespace io */
  
} /* namespace smrtobj */

#endif /* IOSINGAL_H_ */
