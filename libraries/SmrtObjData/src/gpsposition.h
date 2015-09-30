/**
 * \file gpsposition.h
 * \brief Arduino library to model GPS position. A coordinate has three component:
 *        latitude, longitude and altitude. Latitude and longitude are in decimal
 *        degree format (where positive value means North for latitude and West for
 *        longitude). Altitude value is an integer and its unit is meter.
 *
 * \author Marco Boeris Frusca
 *
 */

#ifndef GPSPOSITION_H_
#define GPSPOSITION_H_

#include "Arduino.h"

namespace smrtobj
{
  /**
   * A coordinate has three component: latitude, longitude and altitude. Latitude and 
   * longitude are in decimal degree format (where positive value means North for latitude 
   * and West for longitude). Altitude value is an integer and its unit is meter.
   */
  class GPSPosition
  {
    public:
	  /**
	   * Error code for GPS initialize.
	   */
      enum _gps_error
	  {
        //! No errors
        NO_ERROR = 0,
        //! Invalid coordinate length
        INVALID_COORD_LEN  = -1,

        //! Invalid format of the coordinate
        INVALID_COORD_STRING_FORMAT  = -2,

        //! Invalid value of the coordinate
        INVALID_COORD_VALUE = -3,
      };

	  /**
	   * Size of the GPS attributes.
	   */
      enum _gps_attributes
	  {
        //! Length of internal buffer where coordinate (latitude or longitude) is stored
        COODINATE_LENGTH = 0x12,

        //! Length of internal buffer where altitude is stored
        ALTITUDE_LENGTH = 0x08,
      };

      /**
       * Default Constructor
       *
       */
      GPSPosition();

      /**
       * Copy Constructor
       *
       * \param[in] p GPS position
       */
      GPSPosition(const GPSPosition& p);

      /**
       * Destructor
       *
       */
      virtual ~GPSPosition();

      /**
       * Sets latitude to the coord value. Value have to be in decimal degree. Positive
       * values represent North coordinate and negative ones represent South coordinate.
       *
       * \param[in] coord latitude value (in decimal degree)
       *
       * \return NO_ERROR: if no errors, code errors (from _gps_error enum) otherwise
       */
      int setLatitude(const char *coord);

      /**
       * Sets longitude to the coord value. Value have to be in decimal degree. Positive
       * values represent West coordinate and negative ones represent Est coordinate.
       *
       * \param[in] coord longitude value (in decimal degree)
      *
       * \return NO_ERROR: if no errors, code errors (from _gps_error enum) otherwise
      */
      int setLongitude(const char *coord);

      /**
       * Sets altitude to the coord value. Value have to be an integer value (in meters).
       *
       * \param[in] coord altitude value (meters)
       *
       * \return NO_ERROR: if no errors, code errors (from _gps_error enum) otherwise
       */
      int setAltitude(const char *coord);

      /**
       * Gets latitude in decimal degree as a string.
       *
       * \return coordinate value in decimal degree
       */
      const char* latitude() const;

      /**
       * Gets longitude in decimal degree as a string.
       *
       * \return coordinate value in decimal degree
       */
      const char* longitude() const;

      /**
       * Gets altitude in meters as a string.
       *
       * \return altitude value in meters
       */
      const char* altitude() const;

      /**
       * Overload operator = . It copies latitude, longitude and altitude values
       *
       */
      GPSPosition& operator=(const GPSPosition& p);

    private:
      /**
       * Sets coordinate to the coord value. Value have to be an integer value (in meters).
       * This function is the same for latitude and longitude and checks the format and the
       * value of the coordinate (it must be between -180 and 180)
       *
       * \param[in] coord coordinate value (meters)
       *
       * \return NO_ERROR: if no errors, code errors (from _gps_error enum) otherwise
       */
      int setCoordinate(const char *coord, char *dest);

      //! Latitude
      char m_latitude[COODINATE_LENGTH];

      //! Longitude
      char m_longitude[COODINATE_LENGTH];

      //! Altitude
      char m_altitude[ALTITUDE_LENGTH];

  };

  inline const char* GPSPosition::latitude() const
  {
   return m_latitude;
  } 

  inline const char* GPSPosition::longitude() const
  {
    return m_longitude;
  }

  inline const char* GPSPosition::altitude() const
  {
    return m_altitude;
  }

} /* namespace smrtobj */

#endif /* GPSPOSITION_H_ */
