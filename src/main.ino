#include <ESP8266WiFi.h>  // Biblioteca para generar la conexión a internet a través de WiFi
#include <PubSubClient.h> // Biblioteca para generar la conexión MQTT con un servidor (Ej.: ThingsBoard)
#include <ArduinoJson.h>  // Biblioteca para manejar Json en Arduino
#include <SPI.h>      // incluye libreria bus SPI
#include <MFRC522.h>      // incluye libreria especifica para MFRC522


#include <Servo.h>
#include <DHT.h>


/* ========= CONSTANTES ========= */

// Credenciales de la red WiFi
const char* ssid = "HUAWEI-IoT";
const char* PASS = "ORTWiFiIoT";

// Host de ThingsBoard
const char* MQTT_SERVER = "demo.thingsboard.io";
const int MQTT_PORT = 1883;

// Token del dispositivo en ThingsBoard
const char* DEVICE_TOKEN = "LaGfzdODUTK1J51rtpO7";

// Pines TODO: CAMBIAR PINES

const int PIN_PUERTA = 0;      // pin que checkea el estado de si de verdad esta cerrada la puerta.
const int PIN_VENTILADOR = 0;    // pin de control de la unidad de refrigeracion.
const int PIN_SERVO = 0;        

const int PIN_DHT_1 = 0;
const int PIN_DHT_2 = 0; 
const int PIN_DHT_3 = 0; 
const int PIN_DHT_4 = 0;

const int PIN_BUZZER = 0;

const int PIN_HALL = A0;

const int PIN_RESET = 9; // Establecido por libreria
const int PIN_SS = 10;   // Establecido por libreria

/* ========= VARIABLES ========= */


/* CONEXION */ 
WiFiClient espClient;             // Objeto de conexión WiFi
PubSubClient client(espClient);   // Objeto de conexión MQTT

unsigned long lastMsg = 0;        // Timestamp del ultimo mensaje de telemetria

// Mensajes y buffers
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
char msg2[MSG_BUFFER_SIZE];

// Objeto Json para recibir mensajes desde el servidor
DynamicJsonDocument incoming_message(256);

/* SENSORES DHT */

DHT dht_1(PIN_DHT_1, DHT22);
DHT dht_2(PIN_DHT_2, DHT22);
DHT dht_3(PIN_DHT_3, DHT22);
DHT dht_4(PIN_DHT_4, DHT22);

/* SENSORES EFECTO HALL */

float potencia;

/* SERVOMOTOR Y PUERTA */
Servo servoPuerta;
bool estadoPuerta = false;

/* VENTILADOR */
bool estadoVentilador = false;

/* SISTEMA RFID */

MFRC522  mfrc522(PIN_RESET, PIN_SS);
char uidTarjeta[16];

/* ========= FUNCIONES ========= */

/* FUNCIONES PARA LA CAMARA */

void actualizarEstadoPuerta() {
  if (digitalRead(PIN_PUERTA) == LOW){
    estadoPuerta = true;
    Serial.print("La puerta esta abierta!");
  } else {
    estadoPuerta = false;
    Serial.print("La puerta esta cerrada!");
  }
  
}

void comandoPuerta(bool comando) {
  if (comando == true){
    servoPuerta.write(180);
  } else {
    servoPuerta.write(0);
  }

  Serial.print("Cambie el estado de la puerta a ");
  Serial.println(comando);
}

void comandoBuzzer(bool comando) {
  if (comando == true){
    digitalWrite(PIN_BUZZER, HIGH);
  } else {
    digitalWrite(PIN_BUZZER, LOW);
  }

  Serial.print("Cambie el estado del buzzer a ");
  Serial.println(comando);
}

void comandoVentilador(bool comando) {
  if (comando == true){
    digitalWrite(PIN_VENTILADOR, HIGH);
  } else {
    digitalWrite(PIN_VENTILADOR, LOW);
  }

  Serial.print("Cambie el estado del ventilador a ");
  Serial.println(comando);
}

/* FUNCIONES SETUP */

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
        } else if (metodo == "comandoVentilador") {
            comandoVentilador(incoming_message["params"]);
        }
    }

    // Actualizar el atributo relacionado
    DynamicJsonDocument resp(256);
     resp["estadoPuerta"] = estadoPuerta;
    char buffer[256];
    serializeJson(resp, buffer);
    client.publish("v1/devices/me/attributes", buffer);  //Topico para actualizar atributos
    Serial.print("Publish message [attribute]: ");
    Serial.println(buffer);
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect - client.connect(DEVICE_ID, TOKEN, TOKEN)
    if (client.connect("NODEMCU Nuevo", DEVICE_TOKEN, DEVICE_TOKEN )) {
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

void setupWifi() {

    delay(10);
    Serial.println();
    Serial.print("Conectando a: ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA); // Declarar la ESP como STATION
    WiFi.begin(ssid, PASS);

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

void setup() {

  // Conectividad
  Serial.begin(115200);    // Inicializar conexión Serie para utilizar el Monitor
  SPI.begin();             // Inicializa el SPI
  mfrc522.PCD_Init();      // Inicializa el modulo
  
  setupWifi();     // Establecer la conexión WiFi          
                                                            
  client.setServer(MQTT_SERVER, MQTT_PORT);     // Establecer los datos para la conexión MQTT
  client.setCallback(callback);    // Establecer la función del callback para la llegada de mensajes en tópicos suscriptos

  pinMode(PIN_PUERTA,INPUT);
  pinMode(PIN_VENTILADOR, OUTPUT);
  pinMode(PIN_HALL, INPUT);
  servoPuerta.attach(PIN_SERVO);

  dht_1.begin();
  dht_2.begin();
  dht_3.begin();
  dht_4.begin();

  servoPuerta.write(0);
}

// LOOP

void sistemaRFID() {
  
  // Limpiar uidTarjeta
  for (int i = 0; i < 16; i++) {
    uidTarjeta[i] = 0;
  }
  
  // Revisamos si hay nuevas tarjetas  presentes
  if ( mfrc522.PICC_IsNewCardPresent()) {    
    Serial.println("Lectura del UID");

    //Seleccionamos una tarjeta
    if ( mfrc522.PICC_ReadCardSerial()) {

        // Convertir array de bytes que representan el codigo hexadecimal a string.
        sprintf(uidTarjeta, "%02x%02x%02x%02x", mfrc522.uid.uidByte[0], mfrc522.uid.uidByte[1], mfrc522.uid.uidByte[2], mfrc522.uid.uidByte[3]);
        Serial.print("Se leyo una tarjeta con codigo:");
        Serial.println(uidTarjeta);

        // Terminamos la lectura de la tarjeta  actual
        mfrc522.PICC_HaltA();    
    }      
  } 
}

void sensorHall() {

    float voltaje = analogRead(PIN_SENSOR) * (3.3 / 1023.0);
    float corriente = (voltaje - 1.69) / 0.185;
    float potencia = voltaje * corriente;
    Serial.print("Potencia utilizada: ");
    Serial.println(potencia);
}

void report() {

  // Enviar valores como telemetria
  DynamicJsonDocument resp(256);  //TODO: CAPAZ QUE EL TAMAÑO DEL BUFFER NO DA, AHI HABRIA QUE CAMBIARLO
 
  resp["temperatura1"] =dht_1.readTemperature();
  resp["humedad1"] = dht_1.readHumidity();

  resp["temperatura2"] = dht_2.readTemperature();
  resp["humedad2"] = dht_2.readHumidity();

  resp["temperatura3"] = dht_3.readTemperature();
  resp["humedad3"] = dht_3.readHumidity();

  resp["temperatura4"] = dht_4.readTemperature();
  resp["humedad4"] = dht_4.readHumidity();

  resp["potencia"] = potencia;

  char buffer[256];
  serializeJson(resp, buffer);
  
  client.publish("v1/devices/me/telemetry", buffer);
  
  Serial.print("Publish message [telemetry]: ");
  Serial.println(buffer);

  // Enviar valores como atriubto

    // Actualizar tarjeta
    DynamicJsonDocument resp(256);
    
    resp["tarjetaEscaneada"] = uidTarjeta;
    
    char buffer[256];
    serializeJson(resp, buffer);
    
    client.publish("v1/devices/me/attributes", buffer);  //Topico para actualizar atributos
    
    Serial.print("Publish message [attribute]: ");
    Serial.println(buffer);
}

void loop() {
  
  /* Conexión e intercambio de mensajes MQTT */
  if (!client.connected()) {  // Controlar en cada ciclo la conexión con el servidor
    reconnect();              // Y recuperarla en caso de desconexión
  }
  
  client.loop();              // Controlar si hay mensajes entrantes o para enviar al servidor
  
  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    
    sensorHall();
    sistemaRFID();

    report();
    actualizarEstadoPuerta();

    lastMsg = now;
  }
}