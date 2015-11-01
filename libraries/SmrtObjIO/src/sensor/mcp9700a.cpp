/**
 * \file mcp9700a.cpp
 * \brief MCP9700A is a class to model a Linear Active Thermistor sensor.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "mcp9700a.h"

namespace smrtobj
{

  namespace io
  {
  
    MCP9700A::MCP9700A() :
       m_mVpC(MV_PER_DEGREE_C),
       m_Vat0C(ZERO_C_VOLTS)
      {
      }
  
    // copy constructor
    MCP9700A::MCP9700A(const MCP9700A &s) :
        AnalogSensor(s)
    {
      m_mVpC = s.m_mVpC;
      m_Vat0C = s.m_Vat0C;
    }
  
    MCP9700A::~MCP9700A()
    {
    }
  
    MCP9700A & MCP9700A::operator=(const MCP9700A &s)
    {
      AnalogSensor::operator=(s);
      m_mVpC = s.m_mVpC;
      m_Vat0C = s.m_Vat0C;
  
      return (*this);
    }
  
    float MCP9700A::celsius()
    {
      return measure();
    }
  
    float MCP9700A::kelvin()
    {
      return celsius2kelvin(measure());
    }
  
    float MCP9700A::farenheit()
    {
      return celsius2farenheit(measure());
    }
  
    float MCP9700A::read()
    {
      float value = AnalogSensor::read();
  
      value -= m_Vat0C; //ZERO_C_VOLTS;
      value /= m_mVpC; //MV_PER_DEGREE_C;
  
      m_measure = value;
  
      return m_measure;
    }
  
  } /* namespace io */
  
} /* namespace smrtobj */
