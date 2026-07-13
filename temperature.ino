#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <DHT.h>
#include "wifi_manager.h"
#include "line_config.h"

#define DHTPIN 5  // GPIO5
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);


void sendLineMessage(String message) {
  WiFiClientSecure client;
  client.setInsecure();  // 証明書チェック無効（ESP32定番）

  HTTPClient https;
  https.begin(client, "https://api.line.me/v2/bot/message/push");

  https.addHeader("Content-Type", "application/json");
  https.addHeader("Authorization", "Bearer " + String(LINE_TOKEN));

  String body =
    "{"
    "\"to\":\""
    + String(LINE_USER_ID) + "\","
                             "\"messages\":["
                             "{"
                             "\"type\":\"text\","
                             "\"text\":\""
    + message + "\""
                "}"
                "]"
                "}";

  int httpCode = https.POST(body);

  Serial.print("HTTP Code: ");
  Serial.println(httpCode);

  Serial.println(body);

  String response = https.getString();
  Serial.println(response);

  https.end();
}

void setup() {
  Serial.begin(115200);
  wifiConnect();
  dht.begin();

  Serial.println("DHT Test Start");

  sendLineMessage("ESP32からテスト通知！");
}

bool isAlertSent = false;

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
  Serial.print("判定: ");
  Serial.println(temperature >= 25);

  if (temperature >= 25 && !isAlertSent) {
    String message =
      "🔥 高温警告\\n"
      "温度: "
      + String(temperature) + "℃\\n湿度: " + String(humidity) + "%";

    sendLineMessage(message);
  }

  if (temperature <= 20) {
    isAlertSent = false;
  }

  delay(2000);
}