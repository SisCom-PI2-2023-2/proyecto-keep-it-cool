---
layout: page
title: El trayecto
permalink: /el_trayecto/
---
El trayecto de KIC tuvo sus altos y bajos, en el comienzo la introducción a la nueva metodología de trabajo, nuevo software para desarrollo y la inexperiencia del equipo trabajando sobre soluciones de IoT, probaron ser obstáculos en el camino del proyecto. Estos obstáculos inesperados por parte del equipo de desarrollo generaron atrasos sobre la planificación previa del proyecto, pero gracias a la perseverancia del equipo se lograron los objetivos.

## Prototipos

Comenzaremos explicando las dos pruebas de integración grandes que tuve el proyecto, para luego proceder a las pequeñas pruebas específicas con sus desafíos particulares.
Se tuvieron dos prototipos el modelo base y el modelo 2.0

### Modelo base

El modelo base fue la unión de las primeras pruebas de concepto, obteniendo los datos de tres sensores de temperatura, 
el sensor de la puerta, además de controlar su servomotor, el cooler y el sistema de alarmas vía mail.

Este primer prototipo armo los cimientos sobre los cuales el proyecto se mantendría, enseñándonos como interactuar con actuadores y con sensores, y como reportar toda esa información en Thingsboard. Para este prototipo todavía no se había armado la maqueta, por lo que su prueba resulto menos visual, pero práctica.

Testeo del prototipo:

![Testeo MVP](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/2023-10-19-pruebaMVP.jpeg)

Dashboard de modelo base:

![Dashboard de modelo base](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard10_10_23.png)

### Modelo 2.0

El modelo 2.0 agrega una alarma en el sitio, mediante la utilización de un buzzer, una api para monitorear la temperatura exterior, telemetría sobre el consumo de la cámara gracias a y la utilización de RFID para entrar a la cámara.
Este modelo resulto tener más avances sobre el software que sobre el hardware, ya que gracias a la utilización de bibliotecas y ayuda de pares, implementar la lectura de tarjetas RFID no tuvo mayores complicaciones.
El otro gran progreso de este prototipo fue el hecho de que se logró avanzar sobre la construcción de la maqueta, por lo que la prueba resulto un poco un poco más visual que la anterior, pero todavía con camino para avanzar. 


Fotos del prototipo:

![Foto puerta](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/puerta.jpg)


![Foto Sensores](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/FotoSensores.jpg)

Dashboard modelo 2.0:

![Dashboard de modelo 2.0](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard.jpg)


## Pruebas de concepto

### Cooler

La primer prueba de concepto fue el cooler, consistiendo en unir un ventilador de 12v  utilizado para refrigerar CPUs a un hielo y colocándolo dentro de un tupper, al cual también se le colocó un sensor de temperatura, se vió que al prender el ventilador la temperatura del tupper bajó más de 10°C lo cual es más que suficiente para mostrar el funcionamiento del proyecto, siendo este el objetivo de la prueba.  

### Contol de puerta

Controlar la puerta de la cámara desde un dashboard es una parte vital del proyecto, además de enseñarnos sobre el comportamiento de los RPC call. Está prueba no solo nos sirvió para poder tener el control de la puerta funcionando, si no que también comenzamos a comprender la comunicación entre Thingsboard y las placas.

Bitácora: 29/09/23


### Termohigrómetros

La utilización de sensores con capacidad para leer la temperatura de la cámara cumplía un rol muy importante dentro de nuestro proyecto por lo que lograr que los sensores lean la temperatura y generen el reporte a Thingsboard era otra de las partes vitales del proyecto. En esta prueba descubrimos que uno de los sensores que compramos estaba roto, de ahí el hecho que en la prueba del modelo base simplemente se utilicen tres sensores.

Bitácora: 29/09/23

### Sensor de la puerta

Para el sensor de la puerta simplemente decidimos utilizar un pequeño circuito con los pines de la placa y una resistencia de 10kΩ. La idea es que mientras el circuito este abierto (Puerta abierta) el pin lea 0v y cuando el circuito está cerrado (Puerta cerrada) el pin lea 3,3v.

![Circuito](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/CircuitoSensorPuerta.png)

Bitácora: 17/10/23

### API OpenWeather

Se utilizó Postman para realizar las primeras interacciones con la API para luego integrarla mediante una cadena de reglas a Thingsboard. Una vez obtenidos los datos de la temperatura del lugar los guardamos como telemetría.

![RuleChain](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/RuleChainOpen.png)

Bitácora: 26/10/23

### Buzzer

La alarma local de la cámara decidimos que sea un buzzer activo, por lo que su funcionamiento es bastante sencillo, simplemente debemos conectarlo a un pin de la placa y ponerlo en alto cuando queremos que se prenda la alarma. La lógica de cuando prender la alarma ya estaba hecha para el envío de emails y se lo enviamos mediante un RPC call.

Bitácora: 31/10/23

### Monitoreo de eficiencia

Debido al bajo consumo de la cámara, al ser un modelo, debemos monitorear el consumo de otro circuito. Utilizando un sensor de corriente por efecto hall, mediremos la corriente consumida por el circuito y como conocemos el voltaje al cual está sometido sabemos su consumo.

Bitácora: 07/11/23

### Sistema RFID

Brahian escribí vos

Bitácora: 07/11/23


### Cámara de fotos

Mauro

### Inventario previo (API restdb)

Para simular el inventario previo del cliente se utilizó una base de datos que se actualiza mediante una API, esto es debido a que Thingsboard no ofrece una solución gratuita para integrar un dashboard con SQL. Creando una cadena de reglas que se ejecuta cada vez que se acciona un botón de refrescar, se pide el inventario de la base de datos y al hacer el comando desde el dashboard para retirar/agregar un objeto del inventario se ejecuta otra cadena de reglas con la finalidad de editar el inventario.

Bitácora: 23/11/23
