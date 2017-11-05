//#include "wifi_mqtt_ota.h"
//OTA does not work on an Arduino Uno! no bootloader.


void setup_wifi() {
    delay(10);
    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
      Serial.println(F("WiFi shield not present"));
      // don't continue:
      while (true);
    }
  
    String fv = WiFi.firmwareVersion();
    if (fv != "1.1.0") {
      //Serial.println("Please upgrade the firmware");
    }
     // attempt to connect to Wifi network:
     while (status != WL_CONNECTED) {
      Serial.print(F("Attempting to connect to WPA SSID: "));
      Serial.println(ssid);
      // Connect to WPA/WPA2 network:
      status = WiFi.begin(ssid, password);
  
      // wait 10 seconds for connection:
      delay(5000);
    }

    Serial.print(F("Connected to network"));
    Serial.print(F("SSID: "));
    Serial.println(WiFi.SSID());
    Serial.println(F("IP address: "));
    Serial.println(WiFi.localIP());
  }

  void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print(F("Message arrived ["));
    Serial.print(topic);
    Serial.print("] ");
    for (int i=0;i<length;i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();

    //get last part of topic 
   char* cmnd = "test";
   char* cmnd_tmp=strtok(topic, "/");
 
   while(cmnd_tmp !=NULL) {
     cmnd=cmnd_tmp; //take over last not NULL string
     cmnd_tmp=strtok(NULL, "/"); //passing Null continues on string
     //Serial.println(cmnd_tmp);    
   }

   if (!strcmp(cmnd, "tset")) {
    Serial.print(F("Received new temperature setpoint: "));
    //dummy only.
    }

  }

  void reconnect() {
    // Loop until we're reconnected
    while (!client.connected()) {
      Serial.print(F("Attempting MQTT connection to "));
      Serial.println(mqtt_server);
      // Attempt to connect
      if (client.connect(mqtt_id)) {
        Serial.println(F("connected"));
        // Once connected, publish an announcement...
        client.publish(outTopic,"Energy Monitor booted");
        // ... and resubscribe
        client.subscribe(inTopic);
        send_status();
      } else {
        Serial.print(F("failed, rc="));
        Serial.print(client.state());
        Serial.println(F(" try again in 5 seconds"));
        // Wait 5 seconds before retrying
        delay(5000);
      }
    }
  }

  void setup_mqtt() 
  {
    client.setServer(mqtt_server, 1883);
    client.setCallback(callback);
  }

  void loop_wifi()
  {
    //mqtt reconnect loop
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

  }

  void send_status()
  {
    char outTopic_status[50];
    char msg[50];
    //IP Address
    strcpy(outTopic_status,outTopic);
    strcat(outTopic_status,"ip_address");
    IPAddress ip=WiFi.localIP();
    sprintf(msg, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    // strcat(msg,ip[1]);
    // strcat(msg,".");
    // strcat(msg,ip[2]);
    //WiFi.localIP().toString().toCharArray(msg,50); //TODO FIX
    client.publish(outTopic_status,msg ); 
  }

  void send_power_value(const char* ct_name, float power)
  {
    char outTopic_status[50];
    char msg[50];
    strcpy(outTopic_status,outTopic);
    strcat(outTopic_status,ct_name);
    dtostrf(power,2,2,msg);
    client.publish(outTopic_status,msg ); 
  }