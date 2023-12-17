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

extern "C" {
#include "libb64/cencode.h"
}

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

// Pines para la camara del ESP32 Cam - AI Thinker
#define PWDN_GPIO_NUM 32
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM 0
#define SIOD_GPIO_NUM 26
#define SIOC_GPIO_NUM 27

#define Y9_GPIO_NUM 35
#define Y8_GPIO_NUM 34
#define Y7_GPIO_NUM 39
#define Y6_GPIO_NUM 36
#define Y5_GPIO_NUM 21
#define Y4_GPIO_NUM 19
#define Y3_GPIO_NUM 18
#define Y2_GPIO_NUM 5
#define VSYNC_GPIO_NUM 25
#define HREF_GPIO_NUM 23
#define PCLK_GPIO_NUM 22

#define LED_BUILTIN 4  // LUZ DE LA CAMARA

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

// Buffer para la foto
char *imageBuffer;

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

// inicializa camara
bool initCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  config.fb_count = 1;
  if (DEMO_MODE == 1) {
    config.frame_size = FRAMESIZE_96X96;
    config.jpeg_quality = 63;
  } else {
    config.frame_size = FRAMESIZE_240X240;
    config.jpeg_quality = 10;
  }

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed with error 0x%x", err);
    return false;
  }

  sensor_t *s = esp_camera_sensor_get();
  // initial sensors are flipped vertically and colors are a bit saturated
  s->set_vflip(s, 1);        // flip it back
  s->set_brightness(s, 1);   // up the brightness just a bit
  s->set_saturation(s, -2);  // lower the saturation

  return true;
}

// Metodos
// Camara
bool comandoFoto(bool param) {
  if (param == true) {
    camera_fb_t *fb = NULL;    // vacia el buffer de la camara
    fb = esp_camera_fb_get();  // saca la foto
    if (!fb) {
      return false;  // si no logra sacar la foto, devuelve false
    }
    encode((uint8_t *)fb->buf, fb->len);  // codifica a base 64
    esp_camera_fb_return(fb);             //return the frame buffer back to the driver for reuse
    return true;
  } else {
    return false;
  }
}

// Encode a base 64
void encode(const uint8_t *data, size_t length) {
  if (DEMO_MODE == 1) {
    length = 756;
  }
  size_t size = base64_encode_expected_len(length) + 1;
  base64_encodestate _state;
  base64_init_encodestate(&_state);
  int len = base64_encode_block((char *)&data[0], length, &imageBuffer[0], &_state);
  len = base64_encode_blockend((imageBuffer + len), &_state);
}

/*
// Leer temperaturas de los dhts
leerTemp(DHT dht) {
  return dht.readTempeature(false, false);
}

// Leer humedad de los dhts
leerHum(DHT dht) {
  return dht.readHumidity(false, false);
}
*/

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

    // Ejecutar una acción de acuerdo al método solicitado
    if (metodo == "takePicture") {
      bool status = comandoFoto(true);
      if (status == true) { // NO ESTOY SEGURO DE ESTO HABRIA QUE VER BIEN
        
        DynamicJsonDocument bufferRPC(MAX_MESSAGE_SIZE);
        // bufferRPC["largoFoto"] = strlen(imageBuffer);
        bufferRPC["photo"] = imageBuffer;

        char buffer[MAX_MESSAGE_SIZE];
        serializeJson(bufferRPC, buffer);
        
        //char toPublish[128];
        //("v1/devices/me/rpc/response/"+_request_id).toCharArray(toPublish,128);

        //Serial.println(toPublish);
        //Serial.println(buffer);
        //client.publish(toPublish, buffer); 
        
        client.publish("v1/devices/me/telemetry", buffer);
      }
    }
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
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);
  ledcAttachPin(4, 4);
  ledcSetup(4, 5000, 8);

  imageBuffer = (char *)ps_malloc(50U * 1024);
  Serial.begin(SERIAL_DEBUG_BAUD);
  Serial.println("Camera initialization...");
  if (!initCamera()) {
    Serial.println("Camera initialization failed!");
    ESP.restart();
  }

  dht_1.begin();
  dht_2.begin();
  dht_3.begin();
  dht_4.begin();

  pinMode(LED_BUILTIN, OUTPUT);
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
