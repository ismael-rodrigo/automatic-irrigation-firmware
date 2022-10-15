#include "Button.hpp"

Button btn(12);

void setup() {
pinMode(13 , OUTPUT);
}

void loop() {
  if(btn.isLongedPressed(2000)){
    digitalWrite(13 ,!digitalRead(13));
  }
  if(btn.isClicked()){
    digitalWrite(13 , !digitalRead(13));
  }

  delay(40);
}
