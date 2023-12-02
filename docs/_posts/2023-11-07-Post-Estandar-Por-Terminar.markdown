---
layout: post
title:  "Estandar por terminar"
date:   2023-11-07
categories: posts
---

## Estandar por Terminar

Hoy se avanzo en gran medida con respecto al nivel estandard e incluso al premium. Se realizaron las pruebas de concepto que faltaban:

  - Para el sensor por efecto Hall donde se corroboro que funciona pero que debemos tener cuidado con corrientes muy pequeñas.
  - Para el sistema RFID, donde se corroboro que leyera bien.
  - También nos adelantamos e hicimos la prueba para el esp32-cam (que si bien es para el nivel premium ya lo podíamos probar) donde se verifico que
    no solo anda si no que ademas la calidad de la cámara es mejor de los esperado. Solamente se requiere convertir la imagen a base64 y enviarla a ThingsBoard

Se finalizó el código de arduino del nivel estándar, uniendo el sistema RFID, el buzzer y el sensor de corriente. Lo único que nos falta para dar esto por terminado
es corroborar que se envian correctamente los datos a ThingsBoard.

Además se trabajó en la estética del dashboard:

 * Inicio del dashboard:
  ![InicioDelDashboard](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard.jpg)
 * Consumo y temperatura externa:
  ![Consumo](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Consumo.png)
 * Panel de control de la puerta:
  ![PanelDeControl](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/PanelDeControl.png)
