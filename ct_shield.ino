//#include "ct_shield.h"

void setup_ct_shield()
{
    //Calibration of CT Sensors
  // emonTx Shield Calibration = (100A / 0.05A) / 33 Ohms = 60.6
  //https://learn.openenergymonitor.org/electricity-monitoring/ctac/calibration
  //But Using the 30A/1V CT Clamps I need a ratio of 30 and NO burden resistor on the shield!

  if (CT1) ct1.current(1, 30);     //set for 30A/1V CT Clamp w/o burden resistor on shield                               
  if (CT2) ct2.current(2, 30);                                     
  if (CT3) ct3.current(3, 30); 
  if (CT4) ct4.current(4, 30); 

  CT1_power_RA.clear();
  CT2_power_RA.clear();
  CT3_power_RA.clear();
  CT4_power_RA.clear();
}

void loop_ct_shield(){
    if (CT1) emontx.power1 = ct1.calcIrms(Isamples) * Vcal; 
    if (CT2) emontx.power2 = ct2.calcIrms(Isamples) * Vcal;
    if (CT3) emontx.power3 = ct3.calcIrms(Isamples) * Vcal;
    if (CT4) emontx.power4 = ct4.calcIrms(Isamples) * Vcal;
    //calculating running Averages
    if (CT1) CT1_power_RA.addValue(emontx.power1);
    if (CT2) CT2_power_RA.addValue(emontx.power2);
    if (CT3) CT3_power_RA.addValue(emontx.power3);
    if (CT4) CT4_power_RA.addValue(emontx.power4);
    
    
    

    printSerial();
      // because millis() returns to zero after 50 days ! 
    if (!settled && millis() > FILTERSETTLETIME) settled = true;
  
    if (settled)                                                            
    { 
      //send_rf_data();                                                       
      //digitalWrite(LEDpin, HIGH); delay(2); digitalWrite(LEDpin, LOW);      
      //delay(2000);                                                          
    }

   
}

void printSerial()
{
  if (CT1) {Serial.print(emontx.power1);}
  if (CT2) {Serial.print(" "); Serial.print(emontx.power2);}
  if (CT3) {Serial.print(" "); Serial.print(emontx.power3);}
  if (CT4) {Serial.print(" "); Serial.print(emontx.power4);}
  Serial.println("");
}