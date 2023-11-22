---
layout: post
title:  "Penultima clase"
date:   2023-11-21 21:45:20 -0300
categories: posts
---



En esta clase trabajamos los 3 en 3 cosas distintas, 

Inventario SQL

Uno investigo sobre la posible implementacion de un inventario SQL con Thingsboard de lo cual se logro tener el servidor con el inventario pero todavía no se pudo implementar una conexion con ThingsBoard.

Mapa de Calor

Otro continuo trabajando sobre el mapa de calor tratando de obtener los datos de temperatura del ESP8266 dentro del widget como timeseries para poder hacer el interpolado, lo cual se pudo lograr y se verifico que se muestran los datos y que el mapa se genera como deberia segun la temperatura. Faltaria unicamente emprolijar el aspecto del widget. Y el último trabajó sobre el envío de imagenes a Thingsboard para mayor seguridad en la puerta. 

Imagen del mapa de calor para temperatura (0,0,0,25):
![Mapa-de-Calor](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/2023-11-21-Mapa-de-Calor.png)

Cámara

El último trabajo en mandar una foto sacada desde la puerta para mejorar la seguridad, esta foto se debería tomar al pasar la tarjeta RDIF para corroborar quien entro. Esto se cumplió; el problema es que nos topamos con una limitación de la versión demo de ThingsBoard, solo podemos mandar por RPC un máximo de 1024 bytes, por lo tanto la imagen se ve de la siguiente manera:

![Imagen-de_camara]()
