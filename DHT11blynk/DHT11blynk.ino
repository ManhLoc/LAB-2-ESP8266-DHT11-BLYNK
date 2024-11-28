#define BLYNK_TEMPLATE_ID "TMPL6TmbmCRnJ"
#define BLYNK_TEMPLATE_NAME "DHT11"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"
#define BLYNK_PRINT Serial
#define APP_DEBUG
#define USE_NODE_MCU_BOARD
#include "BlynkEdgent.h"

#include "DHTesp.h"

DHTesp dht;
unsigned long timeupdate=millis();
float temperature, humidity;
BlynkTimer timer;
WidgetLED LEDCONNECT (V0);
#define   NHIETDO     V1
#define   DOAM        V2

void setup()
{
  Serial.begin(115200);
  delay(100);
  BlynkEdgent.begin();

  pinMode(D5,OUTPUT);

  dht.setup(16, DHTesp::DHT11);
  timer.setInterval(1000L,updateBlynk);
}

void loop() {
  BlynkEdgent.run();
  timer.run();
  if(millis()-timeupdate>dht.getMinimumSamplingPeriod()){
    float t = dht.getTemperature();
    float h = dht.getHumidity();
    if(dht.getStatusString()=="OK"){
      temperature=t;
      humidity=h;
    }
    timeupdate=millis();
  }
}

void updateBlynk(){
  if(LEDCONNECT.getValue())LEDCONNECT.off();
  else LEDCONNECT.on();
  Blynk.virtualWrite(NHIETDO,temperature);
  Blynk.virtualWrite(DOAM,humidity);
}

BLYNK_CONNECTED(){
  Blynk.syncAll();
}
BLYNK_WRITE(V3){
  int p=param.asInt();
  digitalWrite(D5,p);
}

