---
layout: page
title: El trayecto
permalink: /el_trayecto/
---

## Prototipos
Se tuvieron dos prototipos el modelo base y el modelo 2.0

### Modelo base

El modelo base fue la unión de las pruebas de las primeras concepto, obteniendo los datos de tres sensores de temperatura, 
el sensor de la puerta, además de su servomotor, el cooler y el sistema de alarmas vía mail.

Dashboard de modelo base:

![Dashboard de modelo base](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard10_10_23.png)

### Modelo 2.0

El modelo 2.0 agrega una alarma en el sitio, una api para monitorear la temperatura exterior, telemetría sobre el consumo de la cámara y la utilización de RFID para entrar a la cámara.
Además de estas mejoras al hardware también se hicieron mejoras para el dashboard.

Dashboard modelo 2.0:

![Dashboard de modelo 2.0](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard.jpg)


## Pruebas de concepto

### Cooler

La primer prueba de concepto fue el cooler, consistiendo en unir un ventilador de 12v  utilizado para refrigerar CPUs a un hielo y colocándolo dentro de un tupper, al cual también se le colocó un sensor de temperatura, se vió que al prender el ventilador la temperatura del tupper bajó más de 10°C lo cual es más que suficiente para mostrar el funcionamiento del proyecto, siendo este el objetivo de la prueba.  

### Contol de puerta

Controlar la puerta de la cámara desde un dashboard es una parte vital del proyecto, además de enseñarnos sobre el comportamiento de los RPC call. Está prueba no solo nos sirvió para poder tener el control de la puerta funcionando, si no que también comenzamos a comprender la comunicación entre Thingsboard y las placas.
Bitácora: 29/09/23


