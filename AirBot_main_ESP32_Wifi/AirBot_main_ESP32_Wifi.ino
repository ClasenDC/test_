// ~ ~ 


include <ESP32Servo.h>
#include "SRF02.h"
#include <Wire.h>
#include <Ticker.h>

#include <esp_now.h>
#include <WiFi.h>

#define CHANNEL 1

//Definitions
const byte LEFT_ROTOR = 32;  
const byte RIGHT_ROTOR = 15;
const int SERVO_PIN = 32;
const byte led_gpio = 13;

//const int ULTRA_SDA = 22; //Ultrasonic/Wire library
//const int ULTRA_SCL = 23; //Ultrasonic/Wire library
SRF02 ultra1(0x70, SRF02_CENTIMETERS);
int irDistance = 0;
uint16_t bottomDistance = 0;

const int IR_SENSOR = A0; //infraRed

//byte incomingByte; //Serial input
Servo myServo;
Ticker myPulse; //tmr for motorCtrl
Ticker storyTicker;
Ticker mySense; //tmr for Sensor read
Ticker bottomTicker;

void InitESPNow() {
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  }
  else {
    Serial.println("ESPNow Init Failed");
    // Retry InitESPNow, add a counte and then restart?
    // InitESPNow();
    // or Simply Restart
    ESP.restart();
  }
}

// config AP SSID
void configDeviceAP() {
  const char *SSID = "ESP32_FlyBot_1";
  bool result = WiFi.softAP(SSID, "Slave_1_Password", CHANNEL, 0);
  if (!result) {
    Serial.println("AP Config failed.");
  } else {
    Serial.println("AP Config Success. Broadcasting with AP: " + String(SSID));
  }
}


void setup() {
  Serial.begin(115200);
  delay(10);  
  Wire.begin(22,23);
  //  wifiInit();
  myServo.attach(13);
  setForwardDir();

  pinMode(LEFT_ROTOR, OUTPUT);
  pinMode(RIGHT_ROTOR, OUTPUT);
  //  mySense.attach(2, autoBot); //activate Autobot
  
    pinMode(led_gpio, OUTPUT);
    WiFi.mode(WIFI_AP);
  // configure device AP mode
  configDeviceAP();
  // This is the mac address of the Slave in AP Mode
  Serial.print("AP MAC: "); Serial.println(WiFi.softAPmacAddress());
  // Init ESPNow with a fallback logic
  InitESPNow();
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info.
  esp_now_register_recv_cb(OnDataRecv);

  
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Recv from: "); Serial.println(macStr);
  Serial.print("Last Packet Recv Data: "); Serial.println(*data);
  Serial.println("");
}

void loop() {
  delay(1000);
  autoBot();
  //  wifiLoop();
}
