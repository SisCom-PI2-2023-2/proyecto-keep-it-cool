---
layout: home
---

<style>
body {
  background-image: url('https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/maquetaSinTerminar.jpg');
  background-repeat: no-repeat;
  width: 50%;
  height: auto;
}
</style>

<div style='text-align: justify;'>
  Keep It Cool (KIC) es un sistema integral de control para habitaciones con temperatura controlada. Dentro de sus capacidades incluye métodos para restringir la entrada a personal no autorizado, así como la habilidad de almacenar información de la habitación en la nube. Además, integra un monitor de consumo eléctrico durante la operación de la habitación y un mapeado de temperatura.
 
</div>


## Origen del proyecto

<div style='text-align: justify;'>
  
  Nuestra iniciativa nació de un problema concreto en una cámara frigorífica. Los sistemas actuales carecen de alertas, lo que puede resultar en situaciones problemáticas, como el descuido de los empleados al dejar la puerta abierta, generando pérdidas significativas. Nuestra solución, "Keep It Cool," basada en la nube, resuelve este problema y mejora la experiencia del usuario en cámaras frigoríficas.

</div>


## Funcionalidad 

<div style='text-align: justify;'>
  KIC consta de dos partes principales: los módulos físicos y la lógica en la nube. Los
sensores en la cámara recopilan información sobre las condiciones, que luego se procesa
en la nube. Esta información se utiliza para tomar decisiones y enviar instrucciones a los
actuadores en la cámara.
</div>
<br>

<div style="display:inline;text-align:left; ">
   <img src="https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Diagrama.png" alt="diagrama" width=400 border="0"/>
  <div style="float: right">
  <ol>
    <li>Puerta controlada por Servomotor</li>
    <li>Sensor de estado de la puerta</li>
    <li>Camara para registro fotográfico</li>
    <li>Sistema RFID para acceder</li>
    <li>Sensor de Temperatura y Humedad</li>
    <li>Sistema de Refrigeración</li>
    <li>Buzzer activado ante emergencias</li>
    <li>Comunicacion con la nube </li>
  </ol>
  </div>
</div>

<div style='text-align: justify;'>
  El panel de control principal, dos dashboard de ThingsBoard, centraliza la información de la cámara con versiones de administrador y trabajador. El administrador tiene privilegios exclusivos, como ajustar parámetros de la cámara o revisar registros fotográficos, esto permite un control eficiente y seguro de la cámara donde solamente personas designadas tienen control avanzado acerca de su funcionamiento.

  Esta mejora no solo resuelve problemas sino que también proporciona una experiencia mejorada, otorgando a los usuarios control total, sin importar su ubicación. 
</div>
  
Dashboard para Administradores
![Dashboard Admin](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/assets/Dashboard%20(admin).PNG)

<div style='text-align: justify;'>
  Pueden explorar las diferentes pestañas para conocer mas del proyecto y de <a href="https://siscom-pi2-2023-2.github.io/proyecto-keep-it-cool/equipo/">nosotros</a>. La pestaña de <a href="https://siscom-pi2-2023-2.github.io/proyecto-keep-it-cool/hardware/">Hardware</a> como su nombre indica detalla los componentes utilizados mientras que la pestaña <a href="https://siscom-pi2-2023-2.github.io/proyecto-keep-it-cool/dashboard/">Dashboard</a> explica el uso del nombrado para el control y uso de la camara. Tambien esta la pestaña <a href="https://siscom-pi2-2023-2.github.io/proyecto-keep-it-cool/el_trayecto/">El Trayecto</a> en la cual se indica como fue se fue desarrollando el proyecto y nuestras conclusiones, errores, aprendizajes y mejoras que podemos decir ahora mirando atras del proyecto.
</div>

## Bitacora

