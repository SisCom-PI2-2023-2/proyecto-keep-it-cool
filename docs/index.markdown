---
# Feel free to add content and custom Front Matter to this file.
# To modify the layout, see https://jekyllrb.com/docs/themes/#overriding-theme-defaults
layout: home
---

Keep It Cool (KIC) es un sistema integral de control para habitaciones con temperatura controlada con la capacidad de añadir métodos para la restricción de entrada a personal no autorizado, con la habilidad de guardar información de la cámara en internet, con monitor de consumo eléctrico durante la operación de la habitación y con mapeado de temperatura de la misma.

## Origen del proyecto

Nuestro proyecto nace a raíz de un problema concreto que surgió en una cámara frigorífica en la práctica. Los sistemas actuales de control de temperatura en cámaras frigoríficas carecen de sistemas de alerta, lo que puede dar lugar a situaciones problemáticas, como el descuido de los empleados al dejar la puerta de la cámara refrigerada abierta. Esto puede resultar en una pérdida significativa de temperatura y, en un caso en concreto, estuvo a punto de causar una pérdida de aproximadamente $U 100,000 en mercancía, si no fuera por la rápida intervención del guardia de seguridad.

Dado este problema y la oportunidad de mejorar la experiencia del usuario en cámaras refrigeradas, hemos decidido emprender el proyecto "Keep It Cool" (KIC). Este proyecto, al estar basado en la nube, soluciona el problema de la falta de alertas relacionadas con la temperatura. Además, permite la implementación de alertas directas al usuario, así como alarmas locales. Además de la mejora en la alerta, KIC tiene como objetivo mejorar la experiencia del usuario mediante la incorporación de capacidades inteligentes, brindando a los usuarios un control total, sin importar su ubicación.

## Funcionalidad 


KIC consta de dos partes principales: los módulos físicos y la lógica en la nube. Los
sensores en la cámara recopilan información sobre las condiciones, que luego se procesa
en la nube. Esta información se utiliza para tomar decisiones y enviar instrucciones a los
actuadores en la cámara. Las acciones posibles incluyen

* Monitoreo de temperatura y humedad en la cámara.
* Sistema RFID para la puerta de la cámara.
* Registro Fotográfico de quien entra.
* Alertas por mail y buzzer ante emergencias.
* Permite incorporarse a una base de datos existente.

Todas estas acciones se llevan a cabo a través de ThingsBoard el cual es el principal panel de control de la cámara y reúne toda la información de la misma.  El dashboard tiene dos versiones: una de administrador y otra para trabajadores. La versión de administrador añade los privilegios correspondientes como el acceso a la configuración de la cámara, un registro fotográfico de todos los que entran, panel con el consumo de la cámara según el clima utilizando una API. De esta forma se separan los privilegios y se logra que solo el encargado de la cámara pueda cambiar parámetros que podrían poner la cámara en peligro si no se tiene cuidado.

![Dashboard](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Dashboard.PNG)

### Dashboard

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














## Bitácora

