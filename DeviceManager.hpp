#ifndef DISPLAYMANAGER
#define DISPLAYMANAGER

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Button.hpp"


struct Device {
    String device_name;
    int device_pin;
    bool is_active; // flag control output rele
    int delay_automatic_active; // interval for next activation in hours
    int opening_hours;   // 0-> full-time // 1-> only-day // 2-> only-night
    
    int flow_rate; // open valve visibly in display
    int flow_rate_sec; // flow rate seted in timer in seconds

    String next_active; // next time for active device
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
    int config_device_view(bool active_button);



    void delayMessage(bool* flag);

    int handler(Button* action_button ,Button* rigth_button , Button* left_button);

    void updateSettingsDevice(int device_id , int delay_automatic_active ,int opening_hours , int flow_rate , int flow_rate_display_labels);

  private:
    Device _devices[10];
    int _lengh_devices;

    String _MENU;
    int _DEVICE_SELECTED;
    bool _flag_active_message = false ;




};

#endif