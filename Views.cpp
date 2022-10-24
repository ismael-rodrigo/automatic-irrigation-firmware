#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "DeviceManager.hpp"
#include <LiquidCrystal_I2C.h>

int device_id = 0;
int menu_id = 0;

int config_page = 0;

// =============== CONFIGS SETED ===============//
int index_fibonacci = 0;
const int fibonacci[8]  = {0,1, 2, 3, 5, 8, 13, 21 };

int index_flow_rate = 0;
                     //SECONDS  //MINUTES         
int flow_rates[9] = {10 , 30 , 1 ,2 ,3 ,5 ,8 ,13 , 21};

int mode = 0; 

// =============== CONFIGS  ====================//

int flow_rate_in_seconds;

DeviceManager::view(bool state_long_pressed_action_btn, bool action_button ,bool rigth_button ,bool left_button)
{

  if(state_long_pressed_action_btn) {
    _flag_active_message = false;
    if(menu_id == 1){ 
      menu_id = 0; 

      if(index_flow_rate >= 2) flow_rate_in_seconds = flow_rates[index_flow_rate]*60 ;
      else flow_rate_in_seconds = flow_rates[index_flow_rate];

      DeviceManager::updateSettingsDevice(device_id);
      index_fibonacci = 0;
      index_flow_rate = 0;
      mode = 0; 
      config_page= 0;
    }

    else menu_id++ ;
  }

  lcd.clear();
  

  switch (menu_id){
    case 0 :
      
      if(rigth_button) if(device_id == _lengh_devices) device_id =0; else device_id++;
      if(left_button) if(device_id == 0) device_id = _lengh_devices; else device_id--;
      if(action_button) _devices[device_id].is_active = !_devices[device_id].is_active;

      DeviceManager::devices_view();

    break;
    case 1:

      if(rigth_button) if(config_page == 2) config_page =0; else config_page++;
      if(left_button) if(config_page == 0) config_page = 2; else config_page--;

      DeviceManager::config_device_view(action_button);
      break;
  }

}




DeviceManager::devices_view(){
  lcd.setCursor(0, 0);
  lcd.print(_devices[device_id].device_name);
  lcd.setCursor(0, 1);

  if(rtc.now().second()%2 == 1){
    lcd.print("prox:");
    lcd.print(_devices[device_id].next_active.hour());
    lcd.print("-");
    lcd.print(_devices[device_id].next_active.minute());
    lcd.print("-");
    lcd.print(_devices[device_id].next_active.second());
  }
  else {
    lcd.print("ult:");
    lcd.print(_devices[device_id].last_active.hour());
    lcd.print("-");
    lcd.print(_devices[device_id].last_active.minute());
    lcd.print("-");
    lcd.print(_devices[device_id].last_active.second());
  }


}





DeviceManager::config_device_view(bool active_button)
{ 
  if(!_flag_active_message){
    for(int x=0;x<5;x++){
      lcd.clear();
      delay(100);
      lcd.setCursor(0, 0);
      lcd.print("==CONFIG PAGE==");
      lcd.setCursor(0, 1);
      lcd.print(_devices[device_id].device_name); 
      delay(300);
    };
    _flag_active_message = true;
    lcd.clear();
  }

  switch(config_page){


    // CONFIG PAGE --> DELAY FOR AUTOMATIC ACTIVE
    case 0:
    if(active_button) {
      if(index_fibonacci >=  7){
        index_fibonacci = 0 ;
        _devices[device_id].delay_automatic_active = fibonacci[index_fibonacci] ; 
      }
      else{
      index_fibonacci++ ; 
      _devices[device_id].delay_automatic_active = fibonacci[index_fibonacci];
      }
    }

    lcd.setCursor(0, 0);
    lcd.print("Intervalo irrig."); 
    lcd.setCursor(0, 1);
    if(_devices[device_id].delay_automatic_active!=0){
      lcd.print("Hora(s): ");
      lcd.print(_devices[device_id].delay_automatic_active ); 
    }
    else{
      lcd.print("Desligado");
    }
    break;


    // CONFIG PAGE --> TIME OF VALVULE ACTIVE
    case 1:

    if(active_button) {
      if(index_flow_rate >=  8){
        index_flow_rate = 0 ;
        _devices[device_id].flow_rate = flow_rates[index_flow_rate] ; 
      }
      else{
      index_flow_rate++ ; 
      _devices[device_id].flow_rate = flow_rates[index_flow_rate];
      }
    }

    lcd.setCursor(0, 0);
    lcd.print("Tempo ativado   "); 

    if(_devices[device_id].flow_rate == 10 | _devices[device_id].flow_rate == 30){
      lcd.setCursor(0, 1);
      lcd.print("Segundos(s): ");
    }
    else {
      lcd.setCursor(0, 1);
      lcd.print("Minuto(s): ");
    }

    lcd.print(_devices[device_id].flow_rate ); 
      
    break;


   // CONFIG PAGE --> MODE OPERATION

    case 2:

    if(active_button) {
      if( mode >= 2) mode = 0; 
      else mode++ ;
      _devices[device_id].opening_hours = mode ;
    }
    
    lcd.setCursor(0, 0);
    lcd.print("Modo de ativar  "); 
    lcd.setCursor(0, 1);
    lcd.print("Tipo: ");
    if(_devices[device_id].opening_hours == 0) lcd.print("Dia");
    if(_devices[device_id].opening_hours == 1) lcd.print("Noite");
    if(_devices[device_id].opening_hours == 2) lcd.print("Full-Time");
     
    break;

  }




}







