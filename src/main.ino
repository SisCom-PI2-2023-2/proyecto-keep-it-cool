#include <ArduinoJson.h>  // Biblioteca para manejar Json en Arduino
#include <Servo.h>        // Biblioteca para el servomotor
#include <DHT.h>          // Biblioteca para los sensores de temperatura/humedad

#include "pines.h"
#include "config.h"
#include "wifi.h"

// Objeto de conexión WiFi
WiFiClient espClient;   

// Objeto Json para recibir mensajes desde el servidor
DynamicJsonDocument incoming_message(256);

 // Objeto de conexión MQTT
PubSubClient client(espClient);  

// Token del device de thingsboard
const char* TOKEN = "UoCrfjY1cYVCQalmY5cR";

/* Componentes */

bool estadoPuerta = false;
bool estadoVentilador = false;

Servo servoPuerta;

const unsigned int CANT_SENSORES = 4;
DHT sensores[] = { DHT dth_1(Pines::DHT_1, DHT22),
                   DHT dth_2(Pines::DHT_2, DHT22),
                   DHT dth_3(Pines::DHT_3, DHT22),
                   DHT dth_4(Pines::DHT_4, DHT22)
                 };

int temperaturas[] = { 0, 0, 0, 0 };
int humedades[] = { 0, 0, 0, 0 };


unsigned long lastMsg = 0; // Timestamp del ultimo update de telemetria

void setup() {

  // Conectividad
  Serial.begin(115200);                                     // Inicializar conexión Serie para utilizar el Monitor
  setupWifi();                                              // Establecer la conexión WiFi
  client.setServer(MQTT::MQTT_SERVER, MQTT::MQTT_SERVER>);  // Establecer los datos para la conexión MQTT
  client.setCallback(MQTT::callback);                       // Establecer la función del callback para la llegada de mensajes en tópicos suscriptos
  
  // Servo
  servoPuerta.attach(Pines::SERVO);                    // ATTACHED AL PIN LED HAY QUE CAMBIARLO
}

void loop() {

  /* Conexión e intercambio de mensajes MQTT */
  if (!client.connected()) {  // Controlar en cada ciclo la conexión con el servidor
    reconnect();              // Y recuperarla en caso de desconexión
  }
  
  client.loop();              // Controlar si hay mensajes entrantes o para enviar al servidor
  
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;

    for (int i = 0; i < CANT_SENSORES; i++) {
      temperaturas[i] = reportarTemperatura(sensores[i]) // TODO: no way this works
      humedades[i] = reportarHumedad(sensores[i])
    }

    MQTT::callback(cliente);
    MQTT::report(cliente, temperaturas, humedades);
  }
}

// Sensores temperatura
int reportarTemperatura(DHT sensor) {
  return (float) sensor.readTemperature(false , false); // sin forzar releer y sin convertir a Farenheit
}

int reportarHumedad(DHT sensor) {
  sensor.readHumidity(false);			   // sin forzar relectura
}