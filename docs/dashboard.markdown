---
layout: page
title: Dashboard
permalink: /dashboard/
---

Trabajador                                                                                                              |  Administrador
:----------------------------------------------------------------------------------------------------------------------:|:---------------------------------------------------------------------------------------------------------------------------------------:
![Dashboard](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Dashboard.jpg)  |  ![Dashboard Admin](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Dashboard%20(admin).PNG)



El dashboard es el centro de trabajo de KIC, desde el se puede acceder a toda la informacion, configuracion y actuadores de la camara. A continuacion se profundiza cada seccion del mismo.

####  Panel Principal

![Panel Principal](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Panel%20de%20Control.PNG)

En el panel principal se muestra toda la información principal y necesaria:

* Graficas para la temperatura y humedad promedio actual en la camara.
* Botón sincronizado con la puerta de la cámara.

#### Alarmas

![Alarmas](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Alarmas.png)

El panel de alarmas tiene un registro histórico con todas las alarmas añadidas. Las alarmas se producen cuando se detectan temperaturas superiores a las deseadas, estas temperaturas threshold se pueden configurar en otro panel.

#### Temperatura

![Temperatura](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Temperatura.png)

En este panel se muestra con más profundidad la temperatura de la cámara, se tiene un historial de lo que mide cada sensor en la cámara y un mapa de calor para acompañar.

#### Inventario

![Inventario](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Inventario.png)

Aquí simplemente se muestra la lista de todos los productos en la cámara, estos deben ser registrados manualmente por el personal con un QR.

#### Configuracion (solo admin)

![Configuración](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Configuracion.png)

Panel solamente habilitado para administradores, permite cambiar parámetros de la cámara, como las temperaturas threshold, el tiempo entre chequeos. También es el lugar desde el cual se le indica al sensor RFID que registre nuevas tarjetas.

#### Personal (solo admin)

![Personal](img.png)

Panel solamente habilitado para administradores, contiene un registro fotográfico con todo el personal que entró a la cámara.

#### Consumo (solo admin)

![Consumo](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Consumo.png)

Panel solamente habilitado para administradores, reporta el consumo en potencia (Watts) de la cámara y lo grafica con la temperatura exterior. De esta forma se puede obtener información de cuánto se gasta según la temperatura.
