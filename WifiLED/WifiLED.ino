#include <Blynk.h>

//https://randomnerdtutorials.com/esp32-ntp-client-date-time-arduino-ide/

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


#include <BlynkSimpleEsp32.h>

uint8_t RE = 13;
uint8_t GR = 14;
uint8_t BL = 12;

uint8_t color = 0;
uint32_t R, G, B;
uint8_t brightR = 0;
uint8_t brightG = 0;
uint8_t brightB = 0;

uint8_t ledArray[3] = {1, 2, 3};

char auth[] = "ZXMcI__ClbI7BqtpcFMDg36D9L-VEGbC";
char ssid[] = "RT_24_5GHZ";
char pass[] = "RsRt!9699";

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup() { 
  Serial.begin(115200);
  
  ledcAttachPin(RE, 1);
  ledcAttachPin(GR, 2);
  ledcAttachPin(BL, 3);

  ledcSetup(1, 12000, 8);
  ledcSetup(2, 12000, 8);
  ledcSetup(3, 12000, 8);

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("WiFi connected");  
  Blynk.begin(auth, ssid, pass);
}

void loop(){
    Blynk.run();
}

BLYNK_WRITE(V1) //Red RGB control
{
  brightR = param.asInt();
  setRGB();
}

BLYNK_WRITE(V2) //Green RGB control
{
  brightG = param.asInt();
  setRGB();
}

BLYNK_WRITE(V3) //Blue RGB control
{
  brightB = param.asInt();
  setRGB();
}

void setRGB() {
  ledcWrite(1, brightR);
  ledcWrite(2, brightG);
  ledcWrite(3, brightB);
  delay(10);
}
