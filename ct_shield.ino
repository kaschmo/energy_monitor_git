//#include "ct_shield.h"

void setup_ct_shield()
{
    //Calibration of CT Sensors
  // emonTx Shield Calibration = (100A / 0.05A) / 33 Ohms = 60.6
  //https://learn.openenergymonitor.org/electricity-monitoring/ctac/calibration
  //But Using the 30A/1V CT Clamps I need a ratio of 30 and NO burden resistor on the shield!

  ct1.current(1, 30);     //set for 30A/1V CT Clamp w/o burden resistor on shield                               
  ct2.current(2, 30);                                     
  ct3.current(3, 30); 

  CT1_power_RA.clear();
  CT2_power_RA.clear();
  CT3_power_RA.clear();
  
  if (CT1_power_RA.getSize()==0) Serial.println(F("Failed to malloc RA array 1"));
  if (CT2_power_RA.getSize()==0) Serial.println(F("Failed to malloc RA array 2"));
  if (CT3_power_RA.getSize()==0) Serial.println(F("Failed to malloc RA array 3"));
  
  power_sample_cnt=0;
}

void loop_ct_shield(){
    power1 = ct1.calcIrms(Isamples) * Vcal; 
    power2 = ct2.calcIrms(Isamples) * Vcal;
    power3 = ct3.calcIrms(Isamples) * Vcal;
    //calculating running Averages
    CT1_power_RA.addValue(power1);
    CT2_power_RA.addValue(power2);
    CT3_power_RA.addValue(power3);
    
    power_sample_cnt++;
    printSerial();
       
}

void printSerial()
{
  if (CT1) {Serial.print(power1);}
  if (CT2) {Serial.print(" "); Serial.print(power2);}
  if (CT3) {Serial.print(" "); Serial.print(power3);}
  
  Serial.println("");
}