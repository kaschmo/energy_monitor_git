//Main for EnergyMonitor
//170930 Karsten Schmolders

#include "wifi_mqtt_ota.h"
#include "ct_shield.h"



void setup() 
{
  Serial.begin(9600);
  Serial.println(F("emonTX Shield Smo Version")); 
  
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
    if((unsigned long)(millis()-timer_send_power_prev) >= timer_send_power) {
     
     timer_send_power_prev=millis(); 
     //Serial.print("\t Running Average: ");
     //Serial.println(CT1_power_RA.getAverage());
     unsigned int total_power=0;
     float avg=0;
     if (CT1) {
       avg=CT1_power_RA.getAverage();
       send_power_value("CT1_power",avg);
       total_power+=avg;       
     }
     if (CT2) {
        avg=CT2_power_RA.getAverage();
        send_power_value("CT2_power",avg);
        total_power+=avg;
     }
     if (CT3) {
      avg=CT3_power_RA.getAverage();
      send_power_value("CT3_power",avg);
      total_power+=avg;
     }
     
     
     send_power_value("power",total_power);
     //Serial.println(power_sample_cnt);
     power_sample_cnt=0;
     

     CT1_power_RA.clear();
     CT2_power_RA.clear();
     CT3_power_RA.clear();
     
    }
}