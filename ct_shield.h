//handle openenergymonitor shield and CTs.
//based on Shield_CT1234.ino example from openenergymonitor


#define FILTERSETTLETIME 5000  //  Time (ms) to allow the filters to settle before sending data

//use three clamps
const int CT1 = 1; 
const int CT2 = 1;                                                     
const int CT3 = 1;
const int CT4 = 0;


#include "EmonLib.h"
#include "RunningAverage.h"

// Create  instances for each CT channel
EnergyMonitor ct1,ct2,ct3, ct4;                                              

// create structure - a neat way of packaging data for RF comms, nothing is added a a 5th integer to match data structure of voltage version
typedef struct { int power1, power2, power3, power4, nothing;} PayloadTX;      
PayloadTX emontx; 

boolean settled = false;
const float Vcal = 232.0; //calibration voltage at home
const int Isamples = 1480; //nummer of power samples to take to calculate RMS Current https://learn.openenergymonitor.org/electricity-monitoring/ac-power-theory/arduino-maths

//Initiliaze RA Arrays with 10 elements
RunningAverage CT1_power_RA(10);
RunningAverage CT2_power_RA(10);
RunningAverage CT3_power_RA(10);
RunningAverage CT4_power_RA(10);


void setup_ct_shield();
void loop_ct_shield();
void printSerial();