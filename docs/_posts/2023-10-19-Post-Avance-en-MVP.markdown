---
layout: post
title:  "Avance en MVP"
date:   2023-10-19 
categories: posts
---

Continuamos con el intento de utilizar simultaneamente todos los componentes juntos para completar el MVP.

Cambiamos la librería de los DHT a ´dht11esp8266´ pese a que usamos DHT22, la librería funciona correctamente con los DHT22.

Tras multiples intentos descubrimos que uno de los cuatro DHT22 no funciona. 

Además notamos que no es posible manejar el servo y los DHTs usando los 3,3V de la placa. El servo requiere de una alimentación externa de 4.8V (5V) para funcionar correctamente.
Normalmente es posible manejar el servo con los 3.3V de la placa pero al conectar los DHT los 3,3V caen lo suficiente como para que no puedan manejar al servo.


Final del día:
  Nos retiramos con todo funcionando (excluyendo al DHT22 que vino sin funcionar)

![mvp](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/2023-10-19-pruebaMVP.jpeg)
