//#include <Arduino_MQTT_Client.h>
#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include <PubSubClient.h>  // Biblioteca para generar la conexión MQTT con un servidor (Ej.: ThingsBoard)
#include <ArduinoJson.h>   // Biblioteca para manejar Json en Arduino

#include <DHT.h>

#define THINGSBOARD_ENABLE_DYNAMIC 1
#define DEMO_MODE 1

//#include <ThingsBoard.h>
#include <esp_heap_caps.h>



// Valores para la conexion a internet
constexpr char WIFI_SSID[] = "FIBRA";
constexpr char WIFI_PASSWORD[] = "superman02";

// Token del dispositivo
constexpr char TOKEN[] = "yFcJpMSJC2ol6yQ43Lt6";

// Servidor MQTT de ThingsBoard
constexpr char THINGSBOARD_SERVER[] = "demo.thingsboard.io";

// Puerto MQTT
constexpr uint16_t THINGSBOARD_PORT = 1883U;

// Tamaño maximo del mensaje por MQTT
constexpr size_t MAX_MESSAGE_SIZE = 100U * 1024;

// Baud rate for the debugging serial connection.
// If the Serial output is mangled, ensure to change the monitor speed accordingly to this variable
constexpr uint32_t SERIAL_DEBUG_BAUD = 9600U;



// Pines para los DHTs 22

const int PIN_DHT_1 = 12; //violeta  
const int PIN_DHT_2 = 13; //blanco
const int PIN_DHT_3 = 15; //verde
const int PIN_DHT_4 = 14; //azul

// Objetos DHT
DHT dht_1(PIN_DHT_1, 22);
DHT dht_2(PIN_DHT_2, 22);
DHT dht_3(PIN_DHT_3, 22);
DHT dht_4(PIN_DHT_4, 22);

// Objeto para la conexion al internet
WiFiClient wifiClient;
// Inicializar cliente para el MQTT
PubSubClient client(wifiClient);

// Valores para el envio de telemetria
constexpr int16_t intervaloEntreMensajes = 5000U;
uint32_t lastMsg;



// Objeto Json para recibir mensajes desde el servidor
DynamicJsonDocument incoming_message(256);

/// @brief Initalizes WiFi connection,
// will endlessly delay until a connection has been successfully established

void InitWiFi() {
  Serial.println("Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);  // Espero a que se conecte
    Serial.println(WiFi.status());
    Serial.println(WL_CONNECTED);
    Serial.println(".");
  }
  Serial.println("Conectado");
}

const bool reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect - client.connect(DEVICE_ID, TOKEN, TOKEN)
    if (client.connect("NODEMCU Nuevo", TOKEN, TOKEN )) {
      Serial.println("connected");
      // Once connected, subscribe to rpc topic
      client.subscribe("v1/devices/me/rpc/request/+");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
  if (WiFi.status() == WL_CONNECTED) {
    return true;
  }
  

  // If we aren't establish a new connection to the given WiFi network
  InitWiFi();
  return true;
}



// callback
void callback(char *topic, byte *payload, unsigned int length) {

  // Log en Monitor Serie
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("]: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // En el nombre del tópico agrega un identificador del mensaje que queremos extraer para responder solicitudes
  String _topic = String(topic);

  // Detectar de qué tópico viene el "mensaje"
  if (_topic.startsWith("v1/devices/me/rpc/request/")) {  // El servidor "me pide que haga algo" (RPC)
    // Obtener el número de solicitud (request number)
    String _request_id = _topic.substring(26);

    // Leer el objeto JSON (Utilizando ArduinoJson)
    deserializeJson(incoming_message, payload);  // Interpretar el cuerpo del mensaje como Json
    String metodo = incoming_message["method"];  // Obtener del objeto Json, el método RPC solicitado

    
    
  }
}

// Funcion de envio de telemetria
void report() {
  // Enviar valores como telemetria
  DynamicJsonDocument resp(256);  
 
  resp["temperatura1"] = dht_1.readTemperature();
  resp["humedad1"] = dht_1.readHumidity();

  resp["temperatura2"] = dht_2.readTemperature();
  resp["humedad2"] = dht_2.readHumidity();

  resp["temperatura3"] = dht_3.readTemperature();
  resp["humedad3"] = dht_3.readHumidity();

  resp["temperatura4"] = dht_4.readTemperature();
  resp["humedad4"] = dht_4.readHumidity();

  char buffer[256];
  serializeJson(resp, buffer);
  
  client.publish("v1/devices/me/telemetry", buffer);
  
  Serial.print("Publish message [telemetry]: ");
  Serial.println(buffer);
}


void setup() {
  

  
  Serial.begin(SERIAL_DEBUG_BAUD);
  
  dht_1.begin();
  dht_2.begin();
  dht_3.begin();
  dht_4.begin();

  
  delay(1000);
  InitWiFi();

  client.setServer(THINGSBOARD_SERVER, THINGSBOARD_PORT);     // Establecer los datos para la conexión MQTT
  client.setCallback(callback);    // Establecer la función del callback para la llegada de mensajes en tópicos suscriptos


}

void loop() {
  //delay(10);
  
  if (!reconnect()) {
    return;
  }

  client.loop();    //revisa si tenemos mensajes entrantes o salientes para el servidor

  // Envia telemetria cada vez que pasa tanto tiempo como dicta la variable intervaloEntreMensajes
  if (millis() - lastMsg > intervaloEntreMensajes) {
    lastMsg = millis();
    report();
  }
}
