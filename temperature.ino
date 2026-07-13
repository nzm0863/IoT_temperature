#include <DHT.h>
#include "wifi_manager.h"
#include "color_press.h"

#define DHTPIN 5       // GPIO5
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  wifiConnect();
  dht.begin();

  Serial.println("DHT Test Start");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("読み取り失敗");
  } else {
    Serial.print("温度: ");
    Serial.print(temperature);
    Serial.print(" °C\t湿度: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  delay(2000);
}