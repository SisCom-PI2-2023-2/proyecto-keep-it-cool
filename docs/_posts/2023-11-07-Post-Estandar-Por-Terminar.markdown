---
layout: post
title:  "Estandar por terminar"
categories: posts
---

Hoy se avanzo en gran medida con respecto al nivel estandard e incluso al premium. Se realizaron las pruebas de concepto que faltaban:

  - para el sensor por efecto Hall donde se corroboro que funciona pero que debemos tener cuidado con corrientes muy pequeñas.
  - para el sistema RFID, donde se corroboro que leyera bien.
  - tambien nos adelantamos e hicimos la prueba para el esp32-cam (que si bien es para el nivel premium ya lo podiamos probar) donde se verifico que
    no solo anda si no que ademas la calidad de la camara es mejor de los esperado. Solamente e requiere convertir la imagen a base64 y enviarla a thingsboard

Se finalizo el codigo de arduino del nivel estandar, uniendo el sistema RFID, el buzzer y el sensor de corriente. Lo unico que nos falta para dar esto por terminado
es corroborar que se envian correctamente los datos a Thingsboard.
