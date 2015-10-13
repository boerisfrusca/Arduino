/**
 * \file stringparser.h
 * \brief Arduino library to handle strings.
 *
 * \author Marco Boeris Frusca
 *
 */

#ifndef STRINGPARSER_H_
#define STRINGPARSER_H_

#include "Arduino.h"
// Atmel libraries
#include <avr/pgmspace.h>                     // Store data in flashmemory instead of SRAM 

namespace smrtobj
{

  class StringParser
  {
    public:
      /**
       * Default Constructor
       * It sets all internal variables as the start time at current time as seconds from 1970.
       */
       StringParser();
      /**
       * Destructor
       */
      virtual ~StringParser();

      /**
       * Parses the string str interpreting its content as an integral number of 8 bits and save it in the variable n.
       * It returns false if the string is not a number.
       *
       * \param[in] str string with the representation of an integral number.
       * \param[out] n 8 bit variable where it is saved the number to return.
       * \param[in] size maximum size of string str.
  	   *
	   * \return false if the string is not a number.
       */
      static bool toInt(char* str, byte &n, byte size = 255);

      /**
       * Parses the string str interpreting its content as an integral number of 16 bits and save it in the variable n.
       * It returns false if the string is not a number.
       *
       * \param[in] str string with the representation of an integral number.
       * \param[out] n 16 bit variable where it is saved the number to return.
       * \param[in] size maximum size of string str.
  	   *
	   * \return false if the string is not a number.
       */
      static bool toInt(char* str, int &n, byte size = 255);

      /**
       * Parses the string str interpreting its content as an unsigned integral number of 16 bits and save it in the variable n.
       * It returns false if the string is not a number.
       *
       * \param[in] str string with the representation of an integral number.
       * \param[out] n unsigned 16 bit variable where it is saved the number to return.
       * \param[in] size maximum size of string str.
  	   *
	   * \return false if the string is not a number.
       */
      static bool toInt(char* str, unsigned int &n, byte size);

      /**
       * Parses the string str interpreting its content as an unsigned integral number of 32 bits and save it in the variable n.
       * It returns false if the string is not a number.
       *
       * \param[in] str string with the representation of an integral number.
       * \param[out] n 32 bit variable where it is saved the number to return.
       * \param[in] size maximum size of string str.
  	   *
	   * \return false if the string is not a number.
       */
      static bool toLong(char* str, long &n, byte size);

      /**
       * Parses the string str interpreting its content as an integral number of 32 bits and save it in the variable n.
       * It returns false if the string is not a number.
       *
       * \param[in] str string with the representation of an integral number.
       * \param[out] n 32 bit variable where it is saved the number to return.
       * \param[in] size maximum size of string str.
  	   *
	   * \return false if the string is not a number.
       */
      static bool toLong(char* str, unsigned long &n, byte size);

      /**
       * Parses the string str interpreting its content as a floating point number and save it in the variable n.
       * It returns false if the string is not a number.
       *
       * \param[in] str string with the representation of a floating point number.
       * \param[out] n variable where it is saved the number to return.
       * \param[in] size maximum size of string str.
  	   *
	   * \return false if the string is not a number.
       */
      static bool toFloat(char* str, float &n, byte size);

      /**
       * Parses the string str interpreting its content as an IP address (array of 4 integral number of 8 bits).
       * It returns false if the string is not a IP address.
       *
       * \param[in] str string with the representation of an IP address.
       * \param[in] size maximum size of string str.
  	   *
	   * \return false if the string is not a IP address.
       */
      static bool toIPAddress(char* str, byte*ip, byte size = 255);

      /**
       * Checks if the string str contains an integer number.
       * It returns false if the string is not an integer number.
       *
       * \param[in] str string with the representation of an integer number.
       * \param[in] size maximum size of string str.
 	   *
	   * \return false if the string is not an integer number.
       */
      static bool isDigitStr(char* str, byte size = 255);

      /**
       * Checks if the string str contains an IP address.
       * It returns false if the string is not an IP address.
       *
       * \param[in] str string with the representation of an IP address.
       * \param[in] size maximum size of string str.
 	   *
	   * \return false if the string is not an IP address.
      */
      static bool isIPAddress(char* str, byte size = 255);

      /**
       * Checks if the string str contains a floating point number.
       * It returns false if the string is not a floating point numbers.
       *
       * \param[in] str string with the representation of a floating point number.
       * \param[in] size maximum size of string str.
	   *
	   * \return false if the string is not a floating point numbers.
       */
      static bool isFloatStr(char* str, byte size = 255);
	  
      /**
       * Converts a floating number to a string of maximum size stot and save it in str.
	   * The number of decimals are set by the parameter decimal.
       *
       * \param[in] n number to convert in a string.
       * \param[in] buff where store the number as a string.
       * \param[in] stot maximim size of the string.
       * \param[in] decimal number of decimals.
	   *
	   * \return false if the strins is not enough big.
       */
      static bool convertFloat(float n, char* buff, uint8_t stot, uint8_t decimal);
	  
	  /**
	   * Reads a string from Flash memory. String is stored in a buffer 'buf' of size 'size_b'.
	   * Buffer 'buf' must be enough large to store the wole string. If it is smaller function returns false.
	   * 
	   * \param[in] str string stored in flash memory
	   * \param[out] buf buffer where store string
	   * \param[in] size_b size of buffer 'buf'
	   * 
	   * \return false if buffer 'buf' is smaller then the string store in flash memory.
	   */
	   static bool readStringFromFlash(const char str[] PROGMEM, char* buf, uint8_t size_b);
  };

} /* namespace smrtobj */

#endif /* STRINGPARSER_H_ */
