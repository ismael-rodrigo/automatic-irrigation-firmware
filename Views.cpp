#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "DeviceManager.hpp"
#include <LiquidCrystal_I2C.h>

int device_id;
int menu_id ;


int submenu_horizontal;

DeviceManager::view(bool state_long_pressed_action_btn, bool action_button ,bool rigth_button ,bool left_button){
  if(action_button) if(menu_id == 1) menu_id = 0; else menu_id++ ; submenu_horizontal = 0;





  lcd.clear();
  
  switch (menu_id){
    case 0 :
    
      if(rigth_button) if(device_id == _lengh_devices) device_id =0; else device_id++;
      if(left_button) if(device_id == 0) device_id = _lengh_devices; else device_id--;
      if(state_long_pressed_action_btn) _devices[device_id].is_active = !_devices[device_id].is_active;

      DeviceManager::devices_view();
    break;
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("CONFIG PAGE");
      lcd.setCursor(0, 1);
      lcd.print(_devices[device_id].device_name); 
      break;
  }

}




DeviceManager::devices_view(){
  lcd.setCursor(0, 0);
  lcd.print(_devices[device_id].device_name);
  lcd.setCursor(0, 1);
  if(_devices[device_id].is_active) lcd.print("ATIVADO");
  else lcd.print("DESATIVADO");
}


DeviceManager::config_device_view(){
  lcd.setCursor(0, 0);
  lcd.print(_devices[device_id].device_name);




}







