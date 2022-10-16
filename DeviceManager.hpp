#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Button.hpp"



struct Device {
    String device_name;
    int device_pin;
    bool is_active;
  };



class DeviceManager 
{
  

  public:
    LiquidCrystal_I2C lcd;
    DeviceManager(struct Device devices[]);

    bool is_changed();

    int lcd_init();

    int devices_init();

    int view(bool state_long_pressed_action_btn ,bool action_button , bool rigth_button ,bool left_button);
    int devices_view();
    int config_device_view();

    
    int handler(Button* action_button ,Button* rigth_button , Button* left_button);

    void update_ios();


  private:
    Device _devices[10];
    int _lengh_devices;

    String _MENU;
    int _DEVICE_SELECTED;


};

#endif