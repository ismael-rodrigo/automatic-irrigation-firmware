#include "Button.hpp"
#include <Arduino.h>

Button::Button(const uint8_t btn_pin):
_btn_pin(btn_pin)
{
  pinMode(_btn_pin , INPUT_PULLUP);
  _lasted_time = millis();
};


bool Button::isClicked()
{
  if(!_flas_is_long_pressed){
    if(!digitalRead(_btn_pin) && !_flag ){
      _flag = 1;
      return false;
    };

    if(digitalRead(_btn_pin) && _flag){
      _flag = 0; 
      return true;   
    };
    return false;
  }
  else{
    _flag=0;
    return false;
  }
};

bool Button::isLongedPressed(const int milliseconds)
{
if(!digitalRead(_btn_pin) && !_flas_is_long_pressed){

  if((unsigned long)( millis() - _lasted_time ) >= milliseconds ){
  _lasted_time = millis();
  _flas_is_long_pressed = true;
  return true;
  };
}

else{
  if(digitalRead(_btn_pin) && _flas_is_long_pressed){
      _flas_is_long_pressed=false;
    }
  _lasted_time = millis();
  return false;  
}
};




