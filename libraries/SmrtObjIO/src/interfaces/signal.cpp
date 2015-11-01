/**
 * \file signal.cpp
 * \brief Signal is an interface to model every input or output signal of an Arduino board.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "signal.h"

namespace smrtobj
{

  namespace io
  {
  
    Signal::Signal() : m_type(NOT_INITIALIZED), m_open(false)
    {
    }
  
    Signal::Signal(const Signal &s)
    {
      m_type = s.m_type;
      m_open = s.m_open;
    }
  
    Signal::~Signal()
    {
    }
  
    Signal & Signal::operator=(const Signal &s)
    {
      m_type = s.m_type;
      m_open = s.m_open;
  
      return (*this);
    }
  
  } /* namespace io */
  
} /* namespace smrtobj */
