#include "mqtt_manager.h"

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setupMQTT(PubSubClient& client, const char* server, int port) {
  client.setServer(server, port);
  client.setCallback(mqttCallback);
}

void reconnectMQTT(PubSubClient& client, const char* client_id, const char* topic_sub) {
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (client.connect(client_id)) {
      Serial.println("Conectado!");
      client.subscribe(topic_sub);
      Serial.print("Inscrito no tópico: ");
      Serial.println(topic_sub);
    } else {
      Serial.print("Falha, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}
