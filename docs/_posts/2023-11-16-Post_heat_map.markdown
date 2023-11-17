---
layout: post
title:  "Comienzo de heat map"
date:   2023-11-16 22:35:20 -0300
categories: posts
---

  Hoy trabajamos sobre el mapa de calor para las temperaturas de la camara, como tenemos cuatro sensores tenemos 
que interpolar el resto de datos. Para lograr esto decidimos hacer una interpolación lineal, tomando la distancia 
aproximada entre los sensores y su ubicación en la camara.

  El mayor problema a la hora de implementar este widget es hacer el widget, ya que hasta ahora simplemente estabamos
usando widget previamente creados, o minimamente modificados, en nuestra solución. Para lograr esto le pedimos ayuda 
a otro grupo el cual ya hizo un widget parecido, una vez logremos tener el código de la visual del widget y de obtener los
datos de la temperatura interpolarlos es sencillo y ya lo tenemos programado.

  Tambien trabajamos sobre los circuitos que vamos a tener en nuestra solucón ya que creiamos tener un problema
de cantidad de pines. Pero utilizando ambas placas (Esp8266 y Esp32Cam) tenemos los suficientes pines para controlar todos
los dispositivos que queremos.
