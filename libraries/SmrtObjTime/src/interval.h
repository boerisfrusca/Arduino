/**
 * \file interval.h
 * \brief Arduino Library to handle time interval (in milliseconds). Time library is required.
 *
 * \author Marco Boeris Frusca
 *
 */
#ifndef INTERVAL_H_
#define INTERVAL_H_

#include "Arduino.h"

namespace smrtobj
{

  /**
   * The Interval class handles time interval (in milliseconds). An interval has an instant where
   * it starts. Calling the time() function it is possible to know how much time has passed from
   * the starting time.
   */
  class Interval
  {
    public:
      /**
       * Default Constructor
       * It sets all internal variables and counters.
       */
      Interval();

      /**
       * Constructor
       * It sets the start time at a given value (number of milliseconds).
       *
       * \param[in] start number of milliseconds to use as start time
       */
      Interval(unsigned long start);

      /**
       * Copy Constructor
	   *
       * \param[in] s Interval in mills
       */
      Interval(const Interval& s);

      /**
       * Destructor
       */
      virtual ~Interval();

      /**
       * Updates the start time at current time.
       *
       */
      void update();

      /**
       * Returns the start time (in milliseconds).
       *
       * \return start time
       */
     unsigned long start();
 
      /**
       * Resets the start time to now().
       *
       * \param[in] start new starting time
       */
      void reset(unsigned long start = 0);

      /**
       * Returns the time passed from the start time (in milliseconds).
       *
       * \return time passed
       */
      unsigned long time();

      /**
       * Returns the remaining time calculated as endTime - m_start (in milliseconds).
       *
       * \param[in] endTime end time of an interval
       *
       * \return residual time
       */
      unsigned long residualTime(unsigned long endTime);

      /**
       *  Overload operator =
       *
       */
      Interval& operator=(const Interval&);

    protected:
      //! start time (in milliseconds)
      unsigned long m_start;

};

inline unsigned long Interval::start()
{
  return m_start;
}

inline void Interval::update()
{
  m_start = millis();
}

} /* namespace smrtobj */

#endif /* INTERVAL_H_ */
