#include "sensor_dht.h"
#include <DHT.h>

#define DHTPIN 27      // Pino conectado ao DHT11
#define DHTTYPE DHT11  // Tipo do sensor

DHT dht(DHTPIN, DHTTYPE);

void setupDHT() {
  dht.begin();
}

float lerTemperatura() {
  float t = dht.readTemperature();
  if (isnan(t)) {
    Serial.println("Erro ao ler temperatura!");
    return -999;
  }
  return t;
}

float lerUmidade() {
  float h = dht.readHumidity();
  if (isnan(h)) {
    Serial.println("Erro ao ler umidade!");
    return -999;
  }
  return h;
}
