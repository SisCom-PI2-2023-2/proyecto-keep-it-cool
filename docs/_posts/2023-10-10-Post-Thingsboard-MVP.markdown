---
layout: post
title:  "Trabajo con Thingsboard para el MVP"
date:   2023-09-28 23:00:00 -0300
categories: posts
---

Avanzamos sobre las cadenas de reglas de thingsboard, teníamos un error de comprension sobre como funcionan los atributos del servidor y como cambiarlos, ya logramos corregirlo.

![dashboard](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/Dashboard10_10_23.png)

![dashboard](https://raw.githubusercontent.com/SisCom-PI2-2023-2/proyecto-keep-it-cool/main/docs/_posts/img/RootChain10-10-23.png)

Tambien aprendimos a generar todos los envios/recepciones de informacion desde thingsBoard y arduino que necesitamos para el MVP.

En el codigo de Arduino se organizo el codigo en distintos archivos para serparar la logica y se subio por primera vez. Y se hicieron unos pequeños ajustes

  Se divido en los siguientes archivos:

    - main.ino - Codigo main
    - wifi.ino/h - Codigo correspondiente a la logica wifi.
    - mqtt.ino/h - Codigo para la logica mqtt. Mandar los valores y recibir que hacer.
    - pines.h - Codigo donde se declaran los pines a utilizar para cada componente.

    
