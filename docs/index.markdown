---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults

layout: home
---


## Keep It Cool

Keep It Cool (KIC) es un sistema integral de control para habitaciones con temperatura controlada con la capacidad de añadir métodos para la restricción de entrada a personal no autorizado, con la habilidad de guardar información de la cámara en internet, con monitor de consumo eléctrico durante la operación de la habitación y con mapeado de temperatura de la misma.


## Código incluido

Pueden incluir código y que lo pinte adecuadamente:

```c++
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    value = random(100);

    //Send value as telemetry
    DynamicJsonDocument resp(256);
    resp["value"] = value;
    char buffer[256];
    serializeJson(resp, buffer);
    
    client.publish("v1/devices/me/telemetry", buffer);
    
    Serial.print("Publish message [telemetry]: ");
    Serial.println(buffer);
    
  }
}
```

## Otras páginas

Creando archivos `.markdown` en la carpeta principal pueden agregar "tabs" de navegación a la página. Por ejemplo [la del equipo](proyecto-keep-it-cool/docs/equipo.markdown) y [otra de prueba](prueba.markdown)

## Configuración del sitio

El archivo `_config.yml` contiene la configuración básica del sitio. Edítenlo para ajustarlo a su proyecto.

## Posts

En la carpeta `_posts`` pueden poner posts para crear la bitácora del proyecto. En el primer post está cómo debe ser el formato para que les quede ordenado.
