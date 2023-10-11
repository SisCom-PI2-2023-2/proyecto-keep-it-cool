#pragma once

namespace MQTT {

    const char* MQTT_SERVER = "thingsboard.cloud";
    const int MQTT_PORT = 1883;

    // Mensajes y buffers
    #define MSG_BUFFER_SIZE  (50)
    char msg[MSG_BUFFER_SIZE];
    char msg2[MSG_BUFFER_SIZE];

    // Metodos RPC
    const char* RPC_PUERTA = "comandoPuerta";
    const char* RPC_VENTILADOR = "comandoVentilador"

    // Función de callback para recepción de mensajes MQTT (Tópicos a los que está suscrita la placa)
    // Se llama cada vez que arriba un mensaje entrante (En este ejemplo la placa se suscribirá al tópico: v1/devices/me/rpc/request/+)
    void callback();

    void report(int[] temperaturas, int[] humedades);
}