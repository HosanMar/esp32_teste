#include <WiFi.h>
#include <PubSubClient.h>

#include "wifi_manager.h"
#include "mqtt_manager.h"
#include "sensor_dht.h"

// Config Wi-Fi
const char* ssid = "brisa-3992484";
const char* password = "zcwbwerm";

// Config MQTT
const char* mqtt_server = "broker.hivemq.com";
const int mqtt_port = 1883;
const char* mqtt_client_id = "ESP32TestClient";
const char* mqtt_topic_sub = "meutopico/receber";
const char* mqtt_topic_temp = "meutop/temp";
const char* mqtt_topic_umid = "meutop/umi";

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  connectToWiFi(ssid, password);
  setupMQTT(client, mqtt_server, mqtt_port);
  setupDHT();
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT(client, mqtt_client_id, mqtt_topic_sub);
  }

  client.loop();

  // Publica temperatura e umidade a cada 10 segundos
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 10000) {
    lastMsg = millis();

    float temp = lerTemperatura();
    float umid = lerUmidade();

    if (temp != -999 && umid != -999) {
      char tempStr[8], umidStr[8];
      dtostrf(temp, 4, 1, tempStr);
      dtostrf(umid, 4, 1, umidStr);

      client.publish(mqtt_topic_temp, tempStr);
      client.publish(mqtt_topic_umid, umidStr);

      Serial.print("Temp: "); Serial.println(tempStr);
      Serial.print("Umid: "); Serial.println(umidStr);
    }
  }
}
