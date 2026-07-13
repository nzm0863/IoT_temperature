# IoT Temperature

ESP32とDHT22を使用した温度・湿度取得サンプルです。

## 使用機材

- ESP32-S3
- DHT22
- Arduino IDE

## 配線

| DHT22 | ESP32 |
|-------|-------|
| + | 3.3V |
| OUT | GPIO5 |
| - | GND |

## ライブラリ

- DHT sensor library by Adafruit
- Adafruit Unified Sensor

## 実行結果

```
Temperature: 28.5°C
Humidity: 62%
```