#ifndef BUTTON
#define BUTTON

#include <Arduino.h>

class Button
{
  public:
    Button(const uint8_t btn_pin);
    bool isClicked();
    bool isLongedPressed(const int milliseconds);


  private:
    const uint8_t _btn_pin;  
    bool _flag = false ;
    unsigned long _lasted_time;
    bool _flas_is_long_pressed;
};

#endif