#include <Arduino_MQTT_Client.h>
#include "esp_camera.h"
#include <WiFi.h>
#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include <PubSubClient.h>  // Biblioteca para generar la conexión MQTT con un servidor (Ej.: ThingsBoard)
#include <ArduinoJson.h>   // Biblioteca para manejar Json en Arduino

#include <DHT.h>

#define THINGSBOARD_ENABLE_DYNAMIC 1
#define DEMO_MODE 1

#include <ThingsBoard.h>
#include <esp_heap_caps.h>

extern "C" {
#include "libb64/cencode.h"
}


// Valores para la conexion a internet
constexpr char WIFI_SSID[] = "HUAWEI-IoT";
constexpr char WIFI_PASSWORD[] = "ORTWiFiIoT";

// Token del dispositivo
constexpr char TOKEN[] = "5qowMiecw1GxvyI9l8cu";

// Servidor MQTT de ThingsBoard
constexpr char THINGSBOARD_SERVER[] = "demo.thingsboard.io";

// Puerto MQTT
constexpr uint16_t THINGSBOARD_PORT = 1883U;

// Tamaño maximo del mensaje por MQTT
constexpr size_t MAX_MESSAGE_SIZE = 100U * 1024;

// Baud rate for the debugging serial connection.
// If the Serial output is mangled, ensure to change the monitor speed accordingly to this variable
constexpr uint32_t SERIAL_DEBUG_BAUD = 115200U;

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

// pines para los DHTs 22

const int PIN_DHT_1 = 12;
const int PIN_DHT_2 = 13; 
const int PIN_DHT_3 = 15; 
const int PIN_DHT_4 = 14;


// Objeto para la conexion al internet
WiFiClient wifiClient;
// Inicializar cliente para el MQTT
PubSubClient client(wifiClient);

/*
Arduino_MQTT_Client mqttClient(wifiClient);

// Inicializa instancia para comunicarse con Thingsboard, usando los 1024 bytes de informacion
ThingsBoard tb(mqttClient, MAX_MESSAGE_SIZE);
*/

// Valores para el envio de telemetria
constexpr int16_t telemetrySendInterval = 2000U;
uint32_t previousDataSend;

// Buffer para la foto
char *imageBuffer;

/// @brief Initalizes WiFi connection,
// will endlessly delay until a connection has been successfully established

void InitWiFi() {
  Serial.println("Connecting ...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);  // Espero a que se conecte
    Serial.println(WiFi.status());
    Serial.println(WL_CONNECTED);
    Serial.println(".");
  }
  Serial.println("Conectado");
}

/// @brief Reconnects the WiFi uses InitWiFi if the connection has been removed
/// @return Returns true as soon as a connection has been established again
const bool reconnect() {
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

/*
RPC_Response processTakePicture(const RPC_Data &data) {
  Serial.println("Received the take picture RPC method");

  if (!captureImage()) {
    return RPC_Response("error", "Cannot take a picture!");
  }

  sendPicture = true;

  // Returning current mode
  return RPC_Response("size", strlen(imageBuffer));
}
*/

const Shared_Attribute_Callback attributes_callback(&processSharedAttributes, SHARED_ATTRIBUTES_LIST.cbegin(), SHARED_ATTRIBUTES_LIST.cend());
const Attribute_Request_Callback attribute_shared_request_callback(&processSharedAttributes, SHARED_ATTRIBUTES_LIST.cbegin(), SHARED_ATTRIBUTES_LIST.cend());
const Attribute_Request_Callback attribute_client_request_callback(&processClientAttributes, CLIENT_ATTRIBUTES_LIST.cbegin(), CLIENT_ATTRIBUTES_LIST.cend());

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

  pinMode(LED_BUILTIN, OUTPUT);
  delay(1000);
  InitWiFi();



  tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT);
  tb.RPC_Subscribe(callbacks.cbegin(), callbacks.cend());
  tb.Shared_Attributes_Subscribe(attributes_callback);
  tb.Shared_Attributes_Request(attribute_shared_request_callback);
  tb.Client_Attributes_Request(attribute_client_request_callback);
}

void loop() {
  //delay(10);

  if (!reconnect()) {
    return;
  }

  if (!tb.connected()) {
    // Connect to the ThingsBoard
    Serial.print("Connecting to: ");
    Serial.print(THINGSBOARD_SERVER);
    Serial.print(" with token ");
    Serial.println(TOKEN);
    if (!tb.connect(THINGSBOARD_SERVER, TOKEN, THINGSBOARD_PORT)) {
      Serial.println("Failed to connect");
      return;
    }
    Serial.println("Connection to server successful");
    // Sending a MAC address as an attribute
    tb.sendAttributeData("macAddress", WiFi.macAddress().c_str());

    Serial.println("Subscribing for RPC...");
    // Perform a subscription. All consequent data processing will happen in
    // processSetLedState() and processSetLedMode() functions,
    // as denoted by callbacks array.
    if (!tb.RPC_Subscribe(callbacks.cbegin(), callbacks.cend())) {
      Serial.println("Failed to subscribe for RPC");
      return;
    }

    if (!tb.Shared_Attributes_Subscribe(attributes_callback)) {
      Serial.println("Failed to subscribe for shared attribute updates");
      return;
    }

    Serial.println("Subscribe done");

    // Request current states of shared attributes
    if (!tb.Shared_Attributes_Request(attribute_shared_request_callback)) {
      Serial.println("Failed to request for shared attributes");
      return;
    }

    // Request current states of client attributes
    if (!tb.Client_Attributes_Request(attribute_client_request_callback)) {
      Serial.println("Failed to request for client attributes");
      return;
    }






    // Sending telemetry every telemetrySendInterval time
    if (millis() - previousDataSend > telemetrySendInterval) {
    }






    // Metodos



    // CAMBIAR
    /*
  if (sendPicture) {
    tb.sendTelemetryData(PICTURE_ATTR, imageBuffer);
    sendPicture = false;
  }
*/
    // Camara
    bool comandoFoto() {
      camera_fb_t *fb = NULL;    // vacia el buffer de la camara
      fb = esp_camera_fb_get();  // saca la foto
      if (!fb) {
        return false;  // si no logra sacar la foto, devuelve false
      }
      encode((uint8_t *)fb->buf, fb->len);  // codifica a base 64
      esp_camera_fb_return(fb);             //return the frame buffer back to the driver for reuse
      return true;
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
        if (metodo == "comandoFoto") {
          comandoFoto(incoming_message["params"]);
        }
      }
    }
