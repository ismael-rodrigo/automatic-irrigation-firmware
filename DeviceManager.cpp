#include <Arduino.h>
#include "DeviceManager.hpp"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Button.hpp"
#include <EEPROM.h>



DeviceManager::DeviceManager(struct Device devices[]):
lcd(0x27,16,2)

{
  for (int x; x < sizeof(devices)+1 ; x++){
    _devices[x].device_name = devices[x].device_name;
    _devices[x].device_pin = devices[x].device_pin;
    _devices[x].is_active = false;
    _devices[x].flow_rate = 10;
    _devices[x].flow_rate_sec = 10;
  
  

    _devices[x].delay_automatic_active = EEPROM.read(((x+1)*10) + 1 );
    _devices[x].opening_hours = EEPROM.read(((x+1)*10) + 2 );
    _devices[x].flow_rate_sec = EEPROM.read(((x+1)*10) + 3 );
    _devices[x].flow_rate = EEPROM.read(((x+1)*10) + 4 );
  }
  _lengh_devices = sizeof(devices);


  

}

void DeviceManager::rtc_init()
{
  rtc.begin();
  delay(50);
  for (int x; x < _lengh_devices + 1 ; x++){
    //_devices[x].next_active = rtc.now() + TimeSpan(0, _devices[x].delay_automatic_active, 0, 0);
    _devices[x].next_active = rtc.now() + TimeSpan(0, 0, 0, _devices[x].delay_automatic_active);
  };

}



void DeviceManager::lcd_init()
{
  lcd.init();
  lcd.setBacklight(HIGH);
  lcd.setCursor(0, 0);
  lcd.print("Initializer LCD");
  lcd.setCursor(0, 1);
  for(int x=0 ; x<17 ; x++){
    lcd.print("=");
    delay(100);
  };
  lcd.clear();
}

void DeviceManager::devices_init()
{
  for(int x = 0; x < _lengh_devices + 1 ; x++){
    pinMode(_devices[x].device_pin , OUTPUT);
    lcd.setCursor(0, 0);
    lcd.print(_devices[x].device_name);
    lcd.setCursor(0, 1);
    lcd.print("OK");
    delay(100);
    lcd.clear();
    delay(100);
  }
}


bool flag_changed;
bool first_update = true ;
bool buttons_state;

bool state_action_btn;
bool state_rigth_btn;
bool state_left_btn;
bool state_long_pressed_action_btn;

bool DeviceManager::is_changed()
{
  if(first_update){
    first_update = false;
    return true;
  }
  buttons_state = state_action_btn | state_rigth_btn | state_left_btn | state_long_pressed_action_btn ;

  if(buttons_state && !flag_changed){
    flag_changed = 1;
    return true;
  }
  if(!buttons_state && flag_changed){
    flag_changed = 0;
    return false;
  }
  return false;
}




void DeviceManager::updateSettingsDevice(int device_id)
{
  _devices[device_id].next_active = rtc.now() + TimeSpan(0, 0, 0, _devices[device_id].delay_automatic_active);

  EEPROM.update(((device_id+1)*10) + 1 , _devices[device_id].delay_automatic_active );

  EEPROM.update(((device_id+1)*10) + 2 , _devices[device_id].opening_hours );
 
  EEPROM.update(((device_id+1)*10) + 3 , _devices[device_id].flow_rate_sec ); //in sec
  
  EEPROM.update(((device_id+1)*10) + 4 , _devices[device_id].flow_rate );
}


void DeviceManager::verify_timers_and_update()
{
  for(int x = 0; x < _lengh_devices + 1 ; x++){
    if( rtc.now() >= _devices[x].next_active ){
      _devices[x].is_active = true ;  
    }
  }
}



void DeviceManager::verify_is_active()
{
  for(int x = 0; x < _lengh_devices + 1 ; x++){
    
    if(_devices[x].is_active && !digitalRead(_devices[x].device_pin)){
      _devices[x].now_active = rtc.now() + TimeSpan(0, 0, 0, _devices[x].flow_rate);
      digitalWrite(_devices[x].device_pin , HIGH);
    }
    if(_devices[x].is_active && digitalRead(_devices[x].device_pin))
    {
      if(rtc.now() >= _devices[x].now_active ){
        _devices[x].is_active = false;
        _devices[x].last_active = rtc.now();
        _devices[x].next_active = rtc.now() + TimeSpan(0, 0, 0, _devices[x].delay_automatic_active);
        digitalWrite(_devices[x].device_pin , LOW);
      }
    }

    
  }

}





void DeviceManager::handler(Button* action_button,Button* rigth_button , Button* left_button)

{
  state_action_btn = action_button->isClicked();
  state_long_pressed_action_btn = action_button->isLongedPressed(1000);
  state_rigth_btn  = rigth_button->isClicked();
  state_left_btn   = left_button->isClicked();

  if(DeviceManager::is_changed()){

    DeviceManager::view(
      state_long_pressed_action_btn,
      state_action_btn,
      state_rigth_btn,
      state_left_btn);
  }


  DeviceManager::verify_timers_and_update();
  DeviceManager::verify_is_active();


}














