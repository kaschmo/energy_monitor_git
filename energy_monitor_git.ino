//Main for EnergyMonitor
//170930 Karsten Schmolders

#include "wifi_mqtt_ota.h"
#include "ct_shield.h"

unsigned long timer_send_power_prev;
unsigned long timer_send_power = 10000; 

void setup() 
{
  Serial.begin(9600);
  Serial.println("emonTX Shield Smo Version"); 
  
  SPI.begin();
  while(!Serial) ;

  setup_wifi();
  setup_mqtt();
  setup_ct_shield();
  timer_send_power_prev=millis(); 
}

void loop()
{
    loop_ct_shield();
    loop_wifi();     
      
     //send power values update via MQTT every XX minutes
    if(millis()-timer_send_power_prev >= timer_send_power) {
     
     timer_send_power_prev=millis(); 
     //Serial.print("\t Running Average: ");
     //Serial.println(CT1_power_RA.getAverage());
     float total_power=0;
     if (CT1) {
       send_power_value("CT1_power",CT1_power_RA.getAverage());
       total_power+=CT1_power_RA.getAverage();
     }
     if (CT2) {
       send_power_value("CT2_power",CT2_power_RA.getAverage());
       total_power+=CT2_power_RA.getAverage();
     }
     if (CT3) {
        send_power_value("CT3_power",CT3_power_RA.getAverage());
        total_power+=CT3_power_RA.getAverage();
     }
     
     if (CT4) {
        send_power_value("CT4_power",CT4_power_RA.getAverage());
        total_power+=CT4_power_RA.getAverage();
     }
     send_power_value("power",total_power);

     

     CT1_power_RA.clear();
     CT2_power_RA.clear();
     CT3_power_RA.clear();
     CT4_power_RA.clear();
     
    }
}