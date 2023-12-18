---
layout: page
title: El Trayecto
permalink: /el_trayecto/
---

<div style='text-align: justify;'>
El trayecto de KIC tuvo sus altos y bajos, en el comienzo la introducción a la nueva metodología de trabajo, nuevo software para desarrollo y la inexperiencia del equipo trabajando sobre soluciones de IoT, probaron ser obstáculos en el camino del proyecto. Estos obstáculos inesperados por parte    del equipo de desarrollo generaron atrasos sobre la planificación previa del proyecto, pero gracias a la perseverancia del equipo se lograron los objetivos.
</div>

## Prototipos

<div style='text-align: justify;'>
Comenzaremos explicando las dos pruebas de integración grandes que tuvo el proyecto, para luego proceder a las pequeñas pruebas específicas con sus desafíos particulares.
Se tuvieron dos prototipos el modelo base y el modelo 2.0.
</div>

### Modelo base

<div style='text-align: justify;'>
El modelo base fue la unión de las primeras pruebas de concepto, obteniendo los datos de tres sensores de temperatura, 
el sensor de la puerta, además de controlar su servomotor, el cooler y el sistema de alarmas vía mail.

Este primer prototipo armo los cimientos sobre los cuales el proyecto se mantendría, enseñándonos como interactuar con actuadores y con sensores, y como reportar toda esa información en Thingsboard. Para este prototipo todavía no se había armado la maqueta, por lo que su prueba resulto menos       visual, pero práctica.
</div>

Testeo del prototipo:

![Testeo MVP](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/2023-10-19-pruebaMVP.jpeg)

Dashboard de modelo base:

![Dashboard de modelo base](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard10_10_23.png)

### Modelo 2.0

<div style='text-align: justify;'>
El modelo 2.0 agrega una alarma en el sitio, mediante la utilización de un buzzer, una api para monitorear la temperatura exterior, telemetría sobre el consumo energetico de la cámara gracias al uso de un sensor de corriente y la utilización de RFID para entrar a la cámara.

Este modelo resulto tener más avances sobre el software que sobre el hardware, ya que gracias a la utilización de bibliotecas y ayuda de pares, implementar la lectura de tarjetas RFID no tuvo mayores complicaciones.
El otro gran progreso de este prototipo fue el hecho de que se logró avanzar sobre la construcción de la maqueta, por lo que la prueba resulto un poco más visual que la anterior, pero todavía con camino para avanzar. 
</div>

Fotos del prototipo:

![Foto puerta](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/puerta.jpg)

![Foto Sensores](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/FotoSensores.jpg)

![Foto cooler](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/cooler1.jpg)

Video de puerta: 

[![Image alt text](https://img.youtube.com/vi/F3nZ_RjiW-k/0.jpg)](https://www.youtube.com/watch?v=F3nZ_RjiW-k)

Dashboard modelo 2.0:

![Dashboard de modelo 2.0](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard.jpg)

## Pruebas de concepto

<div style='text-align: justify;'>
En esta sección hablaremos de las pruebas específicas sobre cada uno de los elementos y sus obstáculos.
</div>

### Cooler

<div style='text-align: justify;'>
La primer prueba de concepto fue el cooler, consistiendo en unir un ventilador de 12v utilizado para refrigerar CPUs a un hielo y colocándolo dentro de un tupper, al cual también se le colocó un sensor de temperatura, se vió que al prender el ventilador la temperatura del tupper bajó más de 10°C lo cual es más que suficiente para mostrar el funcionamiento del proyecto, siendo este el objetivo de la prueba.  
</div>

### Contol de puerta

<div style='text-align: justify;'>
Controlar la puerta de la cámara desde un dashboard es una parte vital del proyecto, además de enseñarnos sobre el comportamiento de los RPC call. Está prueba no solo nos sirvió para poder tener el control de la puerta funcionando, si no que también comenzamos a comprender la comunicación entre Thingsboard y las placas.
</div>

Bitácora: 29/09/23

### Termohigrómetros

<div style='text-align: justify;'>
La utilización de sensores con capacidad para leer la temperatura de la cámara cumplía un rol muy importante dentro de nuestro proyecto por lo que lograr que los sensores lean la temperatura y generen el reporte a Thingsboard era otra de las partes vitales del proyecto. En esta prueba descubrimos que uno de los sensores que compramos estaba roto, de ahí el hecho que en la prueba del modelo base simplemente se utilicen tres sensores. 

Gracias al uso de bibliotecas leer la temperatura y humedad en una placa se resumió a un ejecutar un comando sobre el pin al cual estaba conectado el sensor y simplemente lo enviamos como telemetría a la nube.
</div>

Bitácora: 29/09/23

link a código de prueba : 

<https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/pruebas-de-concepto/tests/Prueba%20Sensor%20Temperatura.ino>

### Sensor de la puerta

<div style='text-align: justify;'>
Para el sensor de la puerta simplemente decidimos utilizar un pequeño circuito con los pines de la placa y una resistencia de 10kΩ. La idea es que mientras el circuito este abierto (Puerta abierta) el pin lea 0v y cuando el circuito está cerrado (Puerta cerrada) el pin lea 3,3V.
</div>

![Circuito](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/CircuitoSensorPuerta.png)

Bitácora: 17/10/23

### API OpenWeather

<div style='text-align: justify;'>
Se utilizó Postman para realizar las primeras interacciones con la API para luego integrarla mediante una cadena de reglas a Thingsboard. Una vez obtenidos los datos de la temperatura de la ubicación de la cámara los guardamos como telemetría.
</div>

![RuleChain](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/RuleChainOpen.png)

Bitácora: 26/10/23

### Buzzer

<div style='text-align: justify;'>
La alarma local de la cámara decidimos que sea un buzzer activo, por lo que su funcionamiento es bastante sencillo, simplemente debemos conectarlo a un pin de la placa y ponerlo en alto cuando queremos que se prenda la alarma. La lógica de cuando prender la alarma ya estaba hecha para el envío de emails y se lo enviamos mediante un RPC call.
</div>

Bitácora: 31/10/23

link a código de prueba : 

<https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/pruebas-de-concepto/tests/Prueba_Buzzer.ino>

### Monitoreo de eficiencia
<div style='text-align: justify;'>
Debido al bajo consumo de la cámara, al ser un modelo, debemos monitorear el consumo de otro circuito. Utilizando un sensor de corriente por efecto hall, mediremos la corriente consumida por el circuito y como conocemos el voltaje al cual está sometido sabemos su consumo.
</div>

Bitácora: 07/11/23

link a código de prueba : 

<https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/pruebas-de-concepto/tests/Prueba_Sensor_Corriente.ino>

### Sistema RFID
<div style='text-align: justify;'>
La primera prueba fue probar si el módulo RFID podía leer correctamente una tarjeta, para esto se utilizó una librería de Arduino donde se logró confirmar que el módulo leía correctamente. Luego de esto lo siguiente fue intentar mandar el codigo de la tarjeta como texto hacia Thingsboard, y aquí estuvo el problema pues no había forma fácil de obtener el código como texto en la librería por lo que tuvimos que utilizar código extra que pasa el codigo leido en bytes a string. Una vez que hicimos esto nos surgió otro problema y es que no se estaba logrando que leyera la tarjeta, después de debuggear descubrimos que probablemente el módulo se estaba desactivando en el loop debido a otra librería por lo que simplemente hicimos que se activará el módulo en el loop, con poner un poco más de código se logró finalmente la total funcionalidad del módulo RFID y su comunicación con Thingsboard.
</div>

Bitácora: 07/11/23

link a código de prueba : 

<https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/pruebas-de-concepto/tests/Prueba%20Lectura%20RFID.ino>

### Cámara de fotos

<div style='text-align: justify;'>
En cuanto a la cámara, nos topamos con una diversa cantidad de problemas y limitaciones.
La primera de ellas fue que las librerías de prueba para testear el funcionamiento de la cámara no funcionaban correctamente en las computadoras del laboratorio, entonces era necesario programarlo desde una laptop o programarlo en nuestras casas.
<br><br>
Después de un día entero probando para hacer que funcionara, lo logramos, pudimos hacer que el ejemplo de prueba corriera sin ningún problema en la placa. Luego de esto pasamos a probar el ejemplo dado por ThingsBoard, el cual no estaba pensado para el AI-Thinker, así que tuvimos que asignar los pines para nuestra placa y poder utilizarlo.
<br><br>
Finalmente nos topamos con una limitación de la versión demo de ThingsBoard, la cual nos limita a 1024 bytes por llamada de RPC, por lo tanto no podemos mandar la imagen completa y nos impide poder intentar hacer reconocimiento facial como habíamos pensado inicialmente
</div>

Bitácora: 23/11/23

link a código de prueba : 

<https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/pruebas-de-concepto/tests/FotoESP32Adaptada.ino>

### Inventario previo (API restdb)

<div style='text-align: justify;'>
Para simular el inventario previo del cliente se utilizó una  <a href="https://restdb.io/">base de datos</a> que se actualiza mediante una API, esto es debido a que Thingsboard no ofrece una solución gratuita para integrar un dashboard con SQL. Creando una cadena de reglas que se ejecuta cada vez que se acciona un botón de refrescar, se pide el inventario de la base de datos y al hacer el comando desde el dashboard para retirar/agregar un objeto del inventario se ejecuta otra cadena de reglas con la finalidad de editar el inventario.
</div>

Bitácora: 23/11/23

## Comparación entre planificación y ejecución

<div style='text-align: justify;'>
Al comparar el cronograma inicial delineado en el Gantt para el Anteproyecto con el cronograma actual, construido a partir de la bitácora, se evidencian notables discrepancias entre ambas planificaciones. La modificación más significativa se refiere a la maqueta, originalmente programada como la primera tarea, pero que experimentó un considerable retraso y se completó meses después de lo previsto. Además, observamos que el desarrollo del MVP demandó 20 días más de lo inicialmente estimado. Este retraso se atribuye principalmente a dificultades encontradas con Thingsboard y las librerías de Arduino. Aunque en un principio estas tareas parecían relativamente sencillas, surgieron complicaciones durante la implementación que requirieron una investigación exhaustiva y debugging. Otra variación notable es que se inició la fase de nivel Premium antes de completar la fase Estándar. Esta decisión se basó en la consideración de que permitir a un miembro del equipo avanzar en el nivel Premium mientras otros finalizaban el Estándar optimizaría el progreso general del proyecto. Esta estrategia resultó beneficiosa y facilitó un avance más rápido del proyecto, de no haberla adoptado, nos habría sido difícil cumplir con los plazos establecidos para la fase Premium antes de la entrega del proyecto.
</div>

[Gantt Original:](https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/main/gantt/Primer_Gantt.gan)

![Gantt Original](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/gantt/Primer_Gantt.jpg)

[Gantt Final:](https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/main/gantt/Segundo_Gantt.gan)

![Gantt Final](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/gantt/Segundo_Gantt.png)

## Conclusión

<div style='text-align: justify;'>
El proyecto KIC a nivel de software cumplió con todos objetivos planteados en el anteproyecto de forma correcta, con excepción del reconocimiento facial, para el cual no logramos tener el tiempo suficiente para investigarlo y desarrollarlo correctamente. También cabe destacar el hecho de que no existe un inventario previo al cual acceder como “inventario de la cámara”, por lo que tuvimos que simularlo. Para esto utilizamos la página web <https://restdb.io>  ya que nos permitía alterar la base de datos directamente con el uso de APIs.

Sobre la maqueta uno de los mayores problemas es la puerta, ya que no tenemos el suficiente espacio para controlarla directamente con un servo motor, se podría mejorar utilizando alguna mejor construcción para transmitir el movimiento del motor a movimiento de la puerta. Otro punto para destacar sobre la maqueta es el problema del cooler, el cual debido a su tamaño se decidió colocar todo dentro la “cámara”, lo cual no es muy conveniente a la hora de recargar los hielos. Esto al nivel industrial no sería un problema ya que la unidad utilizada para refrigerar ya esta diseñada para caber dentro de la cámara de forma correcta.

Además, también tenemos el problema de la cámara de fotos, con la cual no logramos enviar fotos completas, el tamaño máximo de envío a Thingsboard no es suficiente. A nivel industrial esto no sería un problema, ya que la versión paga de Thingsboard permite el envío de archivos más grandes. Tampoco logramos integrar el envío de fotos con el resto del dashboard, ya que no tuvimos el suficiente tiempo, no logrando agregar la foto recibida en el registro de fotos del dashboard. 
</div>
