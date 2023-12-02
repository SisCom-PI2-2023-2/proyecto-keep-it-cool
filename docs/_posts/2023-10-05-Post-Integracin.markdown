---
layout: post
title:  "Integracion del Proyecto"
date:   2023-10-05 
categories: posts
---

## Trabajo sobre ThingsBoard

Empezamos la integración de las pruebas de conepto del MVP, para poder realizar el prototipo.

Creamos el device y añadimos los atributos que vamos a utilizar, luego creamos el dashboard.


![dashboard](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard.PNG)

Por ultimo creamos las rule chains para el control del 

Root Rule Chain, cada 5 minutos compara la temperatura de la camara con un threshold
![root](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/ruleChainRoot.PNG)

Rule Chain para enviar mails ante temperatura bajo treshold
![mail](https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/main/docs/_posts/img/ruleChainMail.PNG)

Rule Chain para prender ventilador ante temperatura bajo treshold
![ventilador](https://github.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/blob/main/docs/_posts/img/ruleChainVentilador.PNG)

Tambien empezamos el codigo de arduino, utilizando lo aprendido de las pruebas.
