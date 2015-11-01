/**
 * \file iosignal.cpp
 * \brief Classes to model input and output signal.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "iosignal.h"

namespace smrtobj
{

  namespace io
  {
  
    /**********************************************************************************
     * DigitalOutput
     **********************************************************************************/
    DigitalOutput::DigitalOutput() : m_value(LOW), m_pin(0)
    {
      m_type = TYPE_OUTPUT;
    }
  
    DigitalOutput::DigitalOutput(const DigitalOutput &o) : Signal(o)
    {
      m_value = o.m_value;
      m_pin = o.m_pin;
    }
  
    DigitalOutput::~DigitalOutput()
    {
    }
  
    DigitalOutput & DigitalOutput::operator=(const DigitalOutput &o)
    {
      Signal::operator=(o);
      m_value = o.m_value;
      m_pin = o.m_pin;
  
      return (*this);
    }
  
    void DigitalOutput::init(byte pin)
    {
      m_pin = pin;
      pinMode(m_pin, OUTPUT);
      m_open = true;
    }
  
    bool DigitalOutput::write(bool value)
    {
      if (!m_open)
      {
        return false;
      }
  
      m_value = value;
      digitalWrite(m_pin, m_value);
  
      return true;
  
    }
  
    /**********************************************************************************
     * PWMOutput
     **********************************************************************************/
    PWMOutput::PWMOutput() : m_value(0), m_pin(0)
    {
      m_type = TYPE_OUTPUT;
    }
  
    PWMOutput::PWMOutput(const PWMOutput &o) : Signal(o)
    {
      m_value = o.m_value;
      m_pin = o.m_pin;
    }
  
    PWMOutput::~PWMOutput()
    {
    }
  
    PWMOutput & PWMOutput::operator=(const PWMOutput &o)
    {
      Signal::operator=(o);
      m_value = o.m_value;
      m_pin = o.m_pin;
  
      return (*this);
    }
  
    void PWMOutput::init(byte pin)
    {
      m_pin = pin;
      pinMode(m_pin, OUTPUT);
      m_open = true;
  
      write(0);
    }
  
    bool PWMOutput::write(byte value)
    {
      if (!m_open)
      {
        return false;
      }
  
      m_value = value;
      analogWrite(m_pin, m_value);
  
      return true;
  
    }
  
    /**********************************************************************************
     * DigitalInput
     **********************************************************************************/
    DigitalInput::DigitalInput() : m_value(0), m_pin(0)
    {
      m_type = TYPE_INPUT;
    }
  
    DigitalInput::DigitalInput(const DigitalInput &o) : Signal(o)
    {
      m_value = o.m_value;
      m_pin = o.m_pin;
    }
  
    DigitalInput::~DigitalInput()
    {
    }
  
    DigitalInput & DigitalInput::operator=(const DigitalInput &o)
    {
      Signal::operator=(o);
      m_value = o.m_value;
      m_pin = o.m_pin;
  
      return (*this);
    }
  
    void DigitalInput::init(byte pin, bool pullup)
    {
      m_pin = pin;
  
      if (pullup)
      {
        pinMode(m_pin,INPUT_PULLUP);
      }
      else
      {
        pinMode(m_pin,INPUT);
      }
  
      m_open = true;
    }
  
    bool DigitalInput::read()
    {
      if (!m_open)
      {
        return 0;
      }
  
      m_value = digitalRead(m_pin);
  
      return m_value;
    }
  
  
    /**********************************************************************************
     * AnalogInput
     **********************************************************************************/
    float  AnalogInput::VREF = DEFAULT_VREF;
  
    float AnalogInput::reference()
    {
      return VREF;
    }
  
    bool AnalogInput::setReferenceDefault(byte vdef)
    {
      switch (vdef)
      {
        case V5_0 : VREF = 5.0; break;
        case V3_3 : VREF = 3.3; break;
        case V0_0 : VREF = 0.0; break;
        default :  {
          VREF = 0.0;
          return false;
        }
      }
  
      return true;
    }
  
    bool AnalogInput::setReference(float voltage)
    {
      if (voltage < 0 || voltage > 5.0)
      {
        return false;
      }
  
      VREF = voltage;
  
      return true;
    }
  
    AnalogInput::AnalogInput() : m_value(0), m_pin(0)
    {
      m_type = TYPE_INPUT;
    }
  
    AnalogInput::AnalogInput(const AnalogInput &o) : Signal(o)
    {
      m_value = o.m_value;
      m_pin = o.m_pin;
    }
  
    AnalogInput::~AnalogInput()
    {
    }
  
    AnalogInput & AnalogInput::operator=(const AnalogInput &o)
    {
      Signal::operator=(o);
      m_value = o.m_value;
      m_pin = o.m_pin;
  
      return (*this);
    }
  
    void AnalogInput::init(byte pin, bool pullup)
    {
      m_pin = pin;
      pinMode(m_pin,INPUT);
  
      if (pullup)
      {
        digitalWrite(pin, HIGH);
      }
      m_open = true;
    }
  
    unsigned long AnalogInput::read()
    {
      if (!m_open)
      {
        return 0;
      }
  
      m_value = analogRead(m_pin);
  
      return m_value;
    }
  
    float  AnalogInput::inputVoltage()
    {
      float lsb = reference();
  
      switch (RESOLUTION)
      {
        case 1  : { lsb /= 2; } break;
        case 2  : { lsb /= 4; } break;
        case 3  : { lsb /= 8; } break;
        case 4  : { lsb /= 16; } break;
        case 5  : { lsb /= 32; } break;
        case 6  : { lsb /= 64; } break;
        case 7  : { lsb /= 128; } break;
        case 8  : { lsb /= 256; } break;
        case 9  : { lsb /= 512; } break;
        case 10 : { lsb /= 1024; } break;
        case 11 : { lsb /= 2048; } break;
        case 12 : { lsb /= 4096; } break;
        default : { lsb /= 4096; }
      }
  
      if (RESOLUTION > 12)
      {
        for (byte i = 0; i <  RESOLUTION - 12; i++)
        {
          m_value /=10;
        }
      }
  
      return m_value * lsb;
    }
  
  } /* namespace io */
  
} /* namespace smrtobj */
