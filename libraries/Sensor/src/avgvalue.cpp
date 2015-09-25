/**
 * \file avgvalue.cpp
 * \brief Arduino library to calculate cumulative average.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "avgvalue.h"

avgValue::avgValue() :
 m_i(0),
 m_value(0.0)
{
}
avgValue::avgValue(const avgValue& v)
{
  m_i = v.m_i;
  m_value = v.m_value;
}

avgValue::~avgValue()
{
}

float avgValue::add(float value)
{
  m_value += (value - m_value) / ( ++m_i );

  return m_value;
}
