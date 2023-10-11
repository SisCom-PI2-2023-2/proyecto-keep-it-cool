#pragma once

namespace Wifi {

    // Credenciales de la red WiFi
    const char* SSID = "HUAWEI-IoT";
    const char* PASS = "ORTWiFiIoT";

    void setupWifi();
    void reconnect();
}