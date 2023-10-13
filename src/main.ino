#include <ESP8266WiFi.h>  // Biblioteca para generar la conexión a internet a través de WiFi
#include <PubSubClient.h> // Biblioteca para generar la conexión MQTT con un servidor (Ej.: ThingsBoard)
#include <ArduinoJson.h>  // Biblioteca para manejar Json en Arduino

#include <Servo.h>
#include <DHT.h>


/* ========= CONSTANTES ========= */

// Credenciales de la red WiFi
const char* SSID = "HUAWEI-IoT";
const char* PASS = "ORTWiFiIoT";

// Host de ThingsBoard
const char* MQTT_SERVER = "demo.thingsboard.io";
const int MQTT_PORT = 1883;

// Token del dispositivo en ThingsBoard
const char* DEVICE_TOKEN = "LaGfzdODUTK1J51rtpO7";

// Pines

const int PIN_PUERTA = 0;    // pin que checkea el estado de si de verdad esta cerrada la puerta.
const int PIN_VENTILADOR = 0;    // pin de control de la unidad de refrigeracion.
const int PIN_SERVO = 0;

const int PIN_DHT_1 = 0;
const int PIN_DHT_2 = 0;
const int PIN_DHT_3 = 0;
const int PIN_DHT_4 = 0;

const int CANT_SENSORES = 4;

/* ========= VARIABLES ========= */

// Objetos de conexión 
WiFiClient espClient;             // Objeto de conexión WiFi
PubSubClient client(espClient);   // Objeto de conexión MQTT

unsigned long lastMsg = 0;        // Timestamp del ultimo mensaje de telemetria

// Mensajes y buffers
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
char msg2[MSG_BUFFER_SIZE];

// Objeto Json para recibir mensajes desde el servidor
DynamicJsonDocument incoming_message(256);

DHT dth_1(PIN_DHT_1, DHT22);
DHT dth_2(PIN_DHT_2, DHT22);
DHT dth_3(PIN_DHT_3, DHT22);
DHT dth_4(PIN_DHT_4, DHT22);


Servo servoPuerta;

bool estadoPuerta = false;
bool estadoVentilador = false;

/* ========= FUNCIONES ========= */

/* FUNCIONES PARA LA CAMARA */

// Sensores temperatura
int reportarTemperatura(DHT sensor) {
  return (float) sensor.readTemperature(false , false); // sin forzar releer y sin convertir a Farenheit
}

int reportarHumedad(DHT sensor) {
  sensor.readHumidity(false);         // sin forzar relectura
}

// Puerta
void actualizarEstadoPuerta(int pinPuerta) {
  if (digitalRead(pinPuerta == HIGH) ){
    estadoPuerta = true;
  } else {
    estadoPuerta = false;
  }
}

void comandoPuerta(bool comando) {
  if (comando == true){
    servoPuerta.write(90);
  } else {
    servoPuerta.write(0);
  }

  Serial.print("Cambie el estado de la puerta a ");
  Serial.println(comando);
}

void comandoVentilador(bool comando)
{
  if (comando == true){
    digitalWrite(PIN_VENTILADOR, HIGH);
  } else {
    digitalWrite(PIN_VENTILADOR, LOW);
  }

  Serial.print("Cambie el estado del ventilador a ");
  Serial.println(comando);
}

/* FUNCIONES SETUP */

void setupWifi() {

    delay(10);
    Serial.println();
    Serial.print("Conectando a: ");
    Serial.println(SSID);

    WiFi.mode(WIFI_STA); // Declarar la ESP como STATION
    WiFi.begin(SSID, PASS);

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

void callback(char* topic, byte* payload, unsigned int length) {

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
    if (_topic.startsWith("v1/devices/me/rpc/request/")) { // El servidor "me pide que haga algo" (RPC)
        // Obtener el número de solicitud (request number)
        String _request_id = _topic.substring(26);

        // Leer el objeto JSON (Utilizando ArduinoJson)
        deserializeJson(incoming_message, payload); // Interpretar el cuerpo del mensaje como Json
        String metodo = incoming_message["method"]; // Obtener del objeto Json, el método RPC solicitado

        // Ejecutar una acción de acuerdo al método solicitado
        if(metodo ==  "comandoPuerta"){
            comandoPuerta(incoming_message["params"]);
        } else if (metodo == "comandoVentilador")
            comandoVentilador(incoming_message["params"]);
        }
    }

    // Actualizar el atributo relacionado
    DynamicJsonDocument respuesta(256);
    respuesta["estadoPuerta"] = estadoPuerta;
    char buffer[256];
    serializeJson(respuesta, buffer);
    client.publish("v1/devices/me/attributes", buffer);  //Topico para actualizar atributos
    Serial.print("Publish message [attribute]: ");
    Serial.println(buffer);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect - client.connect(DEVICE_ID, TOKEN, TOKEN)
    if (client.connect("NODEMCU Nuevo", token, token )) {
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
}

void setup() {

  // Conectividad
  Serial.begin(115200);    // Inicializar conexión Serie para utilizar el Monitor
  
  setupWifi();     // Establecer la conexión WiFi          
                                                            
  client.setServer(MQTT_SERVER, MQTT_PORT);     // Establecer los datos para la conexión MQTT
  client.setCallback(callback);    // Establecer la función del callback para la llegada de mensajes en tópicos suscriptos
}

// LOOP

void report() {

  // Enviar valores como telemetria
  DynamicJsonDocument resp(256);	//TODO: CAPAZ QUE EL TAMAÑO DEL BUFFER NO DA, AHI HABRIA QUE CAMBIARLO
  
  // Leo temperatura y humedad
  resp["temperatura1"] = random(0,50) // reportarTemperatura(dht_1]);
  resp["humedad1"] = random(0, 25) // reportarHumedad(dht_1]);

  resp["temperatura2"] = random(0,50) // reportarTemperatura(dht_1]);
  resp["humedad2"] = random(0, 25) // reportarHumedad(dht_1]);

  resp["temperatura2"] = random(0,50) // reportarTemperatura(dht_2]);
  resp["humedad2"] = random(0, 25) // reportarHumedad(dht_2]);

  resp["temperatura3"] = random(0,50) // reportarTemperatura(dht_3]);
  resp["humedad3"] = random(0, 25) // reportarHumedad(dht_3]);

  resp["temperatura4"] = random(0,50) // reportarTemperatura(dht_4]);
  resp["humedad4"] = random(0, 25) // reportarHumedad(dht_4]);
  
  char buffer[256];
  serializeJson(resp, buffer);
  
  client.publish("v1/devices/me/telemetry", buffer);
  
  Serial.print("Publish message [telemetry]: ");
  Serial.println(buffer);
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

    report();
    estadoPuerta = actualizarEstadoPuerta;
  }
}
