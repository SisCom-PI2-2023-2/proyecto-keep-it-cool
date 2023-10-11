#include <config.h>
#include <ESP8266WiFi.h>

void setupWifi() {
    delay(10);
    Serial.println();
    Serial.print("Conectando a: ");
    Serial.println(SSID);

    WiFi.mode(Wifi::WIFI_STA); // Declarar la ESP como STATION
    WiFi.begin(Wifi::SSID, Wifi::PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("¡Conectado!");
    Serial.print("Dirección IP asignada: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
  // Bucle hasta lograr la conexión
  while (!client.connected()) {
    Serial.print("Intentando conectar MQTT...");
    if (client.connect("ESP8266", token, token)) {  //Nombre del Device y Token para conectarse
      Serial.println("¡Conectado!");
      
      // Una vez conectado, suscribirse al tópico para recibir solicitudes RPC
      client.subscribe("v1/devices/me/rpc/request/+");
      
    } else {
      
      Serial.print("Error, rc = ");
      Serial.print(client.state());
      Serial.println("Reintenar en 5 segundos...");
      // Esperar 5 segundos antes de reintentar
      delay(5000);
      
    }
  }
}

