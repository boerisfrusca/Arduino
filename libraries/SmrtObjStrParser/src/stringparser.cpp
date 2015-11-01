/**
 * \file stringparser.cpp
 * \brief Arduino library to handle strings.
 *
 * \author Marco Boeris Frusca
 *
 */

#include "stringparser.h"

namespace smrtobj
{

  namespace i2c
  {

    StringParser::StringParser()
    {
    }
  
    StringParser::~StringParser()
    {
    }
  
    bool StringParser::isDigitStr(char* str, uint8_t size)
    {
      // Check if is a number
      uint8_t i = 0;
      for (; i < strlen(str) && (i < size); i++)
      {
        if (!isDigit(str[i]) /*str[i] < '0' || str[i] > '9'*/)
        {
          return false;
        }
      }
  
      if (i >= size)
      {
        return false;
      }
  
      return true;
    }
  
    bool StringParser::isIPAddress(char* str, uint8_t size)
    {
      char n[4] = {0};
      uint8_t iStr = 0;
      char* p = &str[iStr];
  
      for (uint8_t j = 0; j < 4; j++)
      {
  
        uint8_t i = 0;
        for (i = 0; i < 4 && p[iStr] != '.' && p[iStr] != '\0'; i++)
        {
          n[i] = p[iStr++];
  
          if (n[i] < '0' || n[i] > '9')
          {
            break;
          }
        }
        if ( p[iStr] == '.' || p[iStr] == '\0')
        {
          n[i] = '\0';
          memset(n, 0, 4);
          iStr++;
        }
        else
        {
          return false;
        }
  
      }
      return true;
    }
  
    bool StringParser::toIPAddress(char* str, uint8_t*ip, uint8_t size)
    {
      char *field;
      char *p = str;
      uint8_t nWord = 0;
  
      while ((field = strtok_r(p, ".", &p)) != NULL)  // Don't use \n here it fails
      {
        if (nWord < 4)
        {
          uint8_t n = 0;
          if (!StringParser::toInt(field, n, strlen(field ) + 1))
          {
            return false;
          }
          else
          {
            if (n > 255)
            {
              return false;
            }
            ip[nWord++] = n;
          }
        }
        else
        {
          return false;
        }
      }
  
      return true;
    }
  
    bool StringParser::isFloatStr(char* str, uint8_t size)
    {
      // Check if is a number
      uint8_t i = 0;
      uint8_t state = 0; // decimal part
      bool d = false;
      if (str[0] == '+' || str[0] == '-')
      {
        i++;
      }
  
      for (; i < strlen(str) && (i < size); i++)
      {
        if (str[i] == '.' && d)
        {
          state = 1;
        }
        else
        {
          if (!isDigit(str[i]) && state == 0)
          {
            return false;
          }
          else
          {
            d = true;
          }
          if (!isDigit(str[i]) && state == 1)
          {
            return false;
          }
        }
      }
  
      if (i >= size)
      {
        return false;
      }
  
      return true;
    }
  
    bool StringParser::toInt(char* str, uint8_t &n, uint8_t size)
    {
      bool ret = true;
  
      if ( !isDigitStr(str, size) )
      {
        ret = false;
      }
      else
      {
        n = atoi(str);
      }
  
      return ret;
    }
  
    bool StringParser::toInt(char* str, int &n, uint8_t size)
    {
      bool ret = true;
  
      if ( !isDigitStr(str, size) )
      {
        ret = false;
      }
      else
      {
        n = atoi(str);
      }
  
      return ret;
    }
  
    bool StringParser::toInt(char* str, unsigned int &n, uint8_t size)
    {
      bool ret = true;
  
      if ( !isDigitStr(str, size) )
      {
        ret = false;
      }
      else
      {
        n = (unsigned int) atol(str);
      }
  
      return ret;
    }
  
    bool StringParser::toLong(char* str, unsigned long &n, uint8_t size)
    {
      bool ret = true;
  
      if ( !isDigitStr(str, size) )
      {
        ret = false;
      }
      else
      {
        n = atol(str);
     }
   
      return ret;
    }
  
    bool StringParser::toLong(char* str, long &n, uint8_t size)
    {
      bool ret = true;
  
      if ( !isDigitStr(str, size) )
      {
        ret = false;
      }
      else
      {
        n = atol(str);
      }
  
      return ret;
    }
  
    bool StringParser::toFloat(char* str, float &n, uint8_t size)
    {
      bool ret = true;
  
      if ( !isFloatStr(str, size) )
     {
        ret = false;
      }
     else
      {
        n = atof(str);
      }
  
      return ret;
    }
  
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
    bool StringParser::convertFloat(float n, char* buff, uint8_t stot, uint8_t decimal)
    {
      uint8_t sz = 2 + decimal;              // '.' + '\0' + decimal size
  
      long pi = (long) n;                    // Integer part
  
      if ( n < 0)                            // Test if number is negative
      {
        pi*= -1;                             // Get integer part as absolute value
        sz++;                                // Increase size of 1 for '-' char
      }
  
      // Check if buffer is enough big
      long lm = 1;
      for (uint8_t i = 0; i < (stot - sz); i++)
        lm*=10;
  
      if (pi < lm)
      {
        // Save value into the buffer
        dtostrf(n, 4, decimal, buff);  // 4 is mininum width, 3 is precision; float value is copied onto buff
  
        return true;
      }
  
      return false;
    }
    
    bool StringParser::readStringFromFlash(const char str[] PROGMEM, char* buf, uint8_t size_b)
    {
      // read back a char
      int len = strlen_P(str);
      int k = 0;
        
      // clear buffer
      memset(buf, 0, size_b);
      
      for (k = 0; k < len && k < size_b; k++)
      {
        buf[k] =  pgm_read_uint8_t_near(str + k);
      }
      if ( k == len )
      {
        return true;
      }
  
      //buf[size_b - 1] =  0;
      return false;
    }
  
  } /* namespace parser */
  
} /* namespace smrtobj */
