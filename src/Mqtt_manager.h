#ifndef MQTT_MANAGER_H
#define MQTT_MANAGER_H

#include <PubSubClient.h>

void setupMQTT(PubSubClient& client, const char* server, int port);
void reconnectMQTT(PubSubClient& client, const char* client_id, const char* topic_sub);
void mqttCallback(char* topic, byte* payload, unsigned int length);

#endif
