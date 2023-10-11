#include "mqtt.h"
#include <PubSubClient.h>

namespace MQTT
{

  void callback(PubSubClient cliente) {
    
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
      switch(metodo)
      {
        case RPC_PUERTA:
          parametro = incoming_message["params"];
          comandoPuerta(parametro);
          break;  

        case RPC_VENTILADOR:
          parametro = incoming_message["params"];
          comandoPuerta(parametro);
          break;

      }
    }

      // Actualizar el atributo relacionado
      DynamicJsonDocument resp(256);
      resp["estado"] = (String) led_state;
      char buffer[256];
      serializeJson(resp, buffer);
      client.publish("v1/devices/me/attributes", buffer);  //Topico para actualizar atributos
      Serial.print("Publish message [attribute]: ");
      Serial.println(buffer);
    }

  void report(PubSubClient cliente, int[] temperaturas, int[] humedades) {
    // POR AHORA LOS DHT SE VAN A LLAMAR DHT1, DHT2, DHT3 Y DHT4

    //Send value as telemetry
    DynamicJsonDocument resp(256);	//TODO: CAPAZ QUE EL TAMAÑO DEL BUFFER NO DA, AHI HABRIA QUE CAMBIARLO
    
    for (int i = 0; i < 4; i++)
    {
      resp["temperatura" + (i+1)] = temperaturas[0];
      resp["humedad" + (i+1)] = humedades[0];
    }

    char buffer[256];
    serializeJson(resp, buffer);

    client.publish("v1/devices/me/telemetry", buffer);

    Serial.print("Publish message [telemetry]: ");
    Serial.println(buffer);
  }

  bool estadoPuerta() {
    return estadoPuerta;
  }

  void actualizarEstadoPuerta() {
    if (digitalRead(pinFeedbackPuerta == HIGH) ){
      estadoPuerta = true;
    } else {
      estadoPuerta = false;
    }
  }

  void comandoPuerta(bool comando) {
    estadoPuerta = comando;
  }

  void actualizarPuerta() {
    if (estadoPuerta() == true){
      servoPuerta.write(90);
    } else {
      servoPuerta.write(0);
    }
  }



  // ventilador
  bool estadoVentilador() {
    return estadoVentilador;
  }

  void comandoVentilador(bool comando) {
    estadoVentilador = comando;
  }

  void actualizarVentilador() {
    if (estadoVentilador() == true) 
      digitalWrite(pinVentilador, HIGH);
    else 
      digitalWrite(pinVentilador, LOW);
  }

}