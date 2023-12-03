---
layout: home
---
<div style='text-align: justify;'>
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
* Sistema RFID para añadir seguridad a la puerta.
* Alertas por mail y buzzer ante emergencias.
* Permite incorporarse a una base de datos existente.
* Registro Fotográfico de quien entra.
  
Todas estas acciones se llevan a cabo a través de ThingsBoard el cual es el principal panel de control de la cámara y reúne toda la información de la misma.  El dashboard tiene dos versiones: una de administrador y otra para trabajadores. La versión de administrador añade los privilegios correspondientes, por ejemplo solo el administrador puede cambiar los parámetros de threshold de la cámara o mirar los registros fotográficos de quien entra en la cámara, esto permite un control eficiente y seguro de la cámara donde solamente personas designadas tienen control avanzado acerca de su funcionamiento. 


## Imagenes

Maqueta
![Maqueta](upsnohaymaquetaxd.png)

Dashboard
![Dashboard](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Dashboard.PNG)

Pueden explorar las diferentes pestañas para conocer mas del proyecto y de [nosotros](equipo.markdown). La pestaña de [Hardware](hardware.markdown) como su nombre indica detalla los componentes utilizados mientras que la pestaña [Dashboard](dashboard.markdown) explica el uso del nombrado para el control y uso de la camara. Tambien esta la pestaña [El Trayecto](el_trayecto.markdown) en la cual se indica como fue se fue desarrollando el proyecto y nuestras conclusiones, errores, aprendizajes y mejoras que podemos decir en esta etapa final del proyecto.

</div>



## Bitácora

