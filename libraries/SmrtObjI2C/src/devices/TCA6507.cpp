/**
 * \file TCA6507.h
 * \brief  TCA6507 is a class to handle an TCA6507 LED driver using I2C protocol.
 *
 * \author Marco Boeris Frusca
 *
 */
#include "TCA6507.h"

namespace smrtobj
{

  TCA6507::TCA6507() : m_reset_pin(0)//, m_pin_state(0)
  {
  }

  TCA6507::TCA6507(uint8_t r_pin) : m_reset_pin(r_pin)//, m_pin_state(0)
  {
  }

  TCA6507::TCA6507(const TCA6507 &d) : I2CInterface(d)
  {
    m_reset_pin = d.m_reset_pin;
  }

  TCA6507::~TCA6507()
  {

  }

  TCA6507 & TCA6507::operator=(const TCA6507 &d)
  {
    I2CInterface::operator=(d);
    m_reset_pin = d.m_reset_pin;

    return (*this);
  }

  bool TCA6507::initialize()
  {
    pinMode(m_reset_pin, OUTPUT);
    stop();

    return true;
  }


  void TCA6507::start()
  {
    digitalWrite(m_reset_pin, HIGH);
  }

  void TCA6507::stop()
  {
    digitalWrite(m_reset_pin, LOW);
  }

  bool TCA6507::isConnected()
  {
    uint8_t result = 0;

    return ( I2Cdev::readByte(DEVICE_ADDRESS, SELECT0, &result) == 1);
  };

  bool TCA6507::RAWSelRegsDrv(uint8_t s0, uint8_t s1, uint8_t s2)
  {
    uint8_t data[3] = {s0, s1, s2};

    return I2Cdev::writeBytes(DEVICE_ADDRESS, INITIALIZATION, 3, data);
  }

  bool TCA6507::RAWRegDrv(uint8_t reg, uint8_t val)
  {
    if(reg >= 3 && reg <= 10)
    {
      return I2Cdev::writeByte(DEVICE_ADDRESS, reg, val);

    }

    return false;
  }

  uint8_t TCA6507::readReg(uint8_t reg)
  {
    uint8_t result = 0;

   I2Cdev::readByte(DEVICE_ADDRESS, reg, &result);

    return result;
  }

  uint8_t TCA6507::pinState(uint8_t pin)
  {
    uint8_t state = 0;

    if( pin >= 0 && pin <= 6 )
    {
      uint8_t SR0 = readReg(0); // SELECT0
      SR0 = bitRead(SR0, pin);
      uint8_t SR1 = readReg(1); // SELECT1
      SR1 = bitRead(SR1, pin);
      uint8_t SR2 = readReg(2); // SELECT2
      SR2 = bitRead(SR2, pin);

      if(SR0 == 1)
        state += 1;
      if(SR1 == 1)
        state += 2;
      if(SR2 == 1)
        state += 4;
    }
    else
      state = 16;

    return state;
  }

  void TCA6507::pinSetState(uint8_t pin, uint8_t state)
  {
    if(pin >= 0 && pin <= 6 && state >= 0 && state <= 7)
    {
      uint8_t SR0 = readReg(0);
      uint8_t SR0b = 0;
      uint8_t SR1 = readReg(1);
      uint8_t SR1b = 0;
      uint8_t SR2 = readReg(2);
      uint8_t SR2b = 0;

      if(state == LED_ON_PWM0)
      {
        SR0b = 0;
        SR1b = 1;
        SR2b = 0;
      }
      else if(state == LED_ON_PWM1)
      {
        SR0b = 1;
        SR1b = 1;
        SR2b = 0;
      }
      else if(state == LED_ON)
      {
        SR0b = 0;
        SR1b = 0;
        SR2b = 1;
      }
      else if(state == LED_ON_ONE_SHOT)
      {
        SR0b = 1;
        SR1b = 0;
        SR2b = 1;
      }
      else if(state == LED_BLINK_BANK0)
      {
        SR0b = 0;
        SR1b = 1;
        SR2b = 1;
      }
      else if(state == LED_BLINK_BANK1)
      {
        SR0b = 1;
        SR1b = 1;
        SR2b = 1;
      }

      SR0 = bitWrite(SR0, pin, SR0b);
      SR1 = bitWrite(SR1, pin, SR1b);
      SR2 = bitWrite(SR2, pin, SR2b);
      RAWSelRegsDrv(SR0, SR1, SR2);
    }
  }

  void TCA6507::basicBankSetup(uint8_t nBank, uint8_t fadeOn, uint8_t onTime, uint8_t fadeOff, uint8_t offTime, uint8_t sdOffTime)
  {

    if (nBank >= 0 && nBank <= 1 && fadeOn >= 0 && fadeOn <= 15 && onTime >= 0 && onTime <= 15 && fadeOff >= 0 && fadeOff <= 15 && offTime >= 0 && offTime <= 15 && sdOffTime >= 0 && sdOffTime <= 15 )
    {
      uint8_t SR3 = readReg(FADE_ON_TIME);
      uint8_t SR4 = readReg(FULLY_ON_TIME);
      uint8_t SR5 = readReg(FADE_OFF_TIME);
      uint8_t SR6 = readReg(FIRST_FULLY_OFF_TIME);
      uint8_t SR7 = readReg(SECOND_FULLY_OFF_TIME);

      if(nBank == 0)
      {
        SR3 = SR3 & 0xF0;
        SR4 = SR4 & 0xF0;
        SR5 = SR5 & 0xF0;
        SR6 = SR6 & 0xF0;
        SR7 = SR7 & 0xF0;
      }

      if(nBank == 1)
      {
        SR3 = SR3 & 0x0F;
        SR4 = SR4 & 0x0F;
        SR5 = SR5 & 0x0F;
        SR6 = SR6 & 0x0F;
        SR7 = SR7 & 0x0F;

        fadeOn = fadeOn << 4;
        onTime = onTime << 4;
        fadeOff = fadeOff << 4;
        offTime = offTime << 4;
        sdOffTime = sdOffTime << 4;
      }

      SR3 = SR3 | fadeOn;
      SR4 = SR4 | onTime;
      SR5 = SR5 | fadeOff;
      SR6 = SR6 | offTime;
      SR7 = SR7 | sdOffTime;

      RAWRegDrv(FADE_ON_TIME, SR3);
      RAWRegDrv(FULLY_ON_TIME, SR4);
      RAWRegDrv(FADE_OFF_TIME, SR5);
      RAWRegDrv(FIRST_FULLY_OFF_TIME, SR6);
      RAWRegDrv(SECOND_FULLY_OFF_TIME, SR7);

    }
  }

  void TCA6507::registryToBank(uint8_t nBank, uint8_t nReg, uint8_t val)
  {

    if( nBank >= 0 && nBank <= 1 && nReg >= 3 && nReg <= 8 && val >= 0 && val <= 15 )
    {
      uint8_t ResData = readReg(nReg);

      if(nBank == 0)
        ResData = ResData & 0xF0;

      if(nBank == 1)
      {
        ResData = ResData & 0x0F;
        val = val << 4;
      }

      ResData = ResData | val;

      RAWRegDrv(nReg, ResData);
    }
  }

} /* namespace smrtobj */
