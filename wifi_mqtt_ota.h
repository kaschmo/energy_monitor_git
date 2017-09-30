#include <SPI.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <PubSubClient.h> //MQTT
#include "wifi_credentials.h"

int status = WL_IDLE_STATUS; 

//MQTT
WiFiClient ardClient;
PubSubClient client(ardClient); //MQTT client
const char* inTopic = "cmnd/energy_mon/#";
const char* outTopic = "stat/energy_mon/";
const char* mqtt_id = "energy_mon";
//-MQTT


void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);
void reconnect();
void loop_wifi();
void setup_mqtt();
void send_status();
void send_power_value(const char* ct_name, float power);