#include "DeviceManager.hpp"
#include "Button.hpp"

Button ActiveButton(2), RightButton(3), LeftButton(4);



Device devices[] = {
  {
    .device_name = "Cana de Acucar",
    .device_pin = 13,
  },
  {
    .device_name = "Pe de Limao",
    .device_pin = 12,
  },
    {
    .device_name = "Pe de caja",
    .device_pin = 11,
  }
};






bool state_active_button(){
  return ActiveButton.isClicked();
}
bool state_right_button(){
  return RightButton.isClicked();
}
bool state_left_button(){
  return LeftButton.isClicked();
}



DeviceManager device(devices);

void setup() 
{
  device.lcd_init();
  device.devices_init();
}

void loop() 
{
  device.handler(&ActiveButton , &RightButton ,&LeftButton );
  delay(100);
}
