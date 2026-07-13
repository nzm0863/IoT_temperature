#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include "wifi_manager.h"
#include "wifi_config.h"

void wifiConnect() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("WiFi Connected!");
}