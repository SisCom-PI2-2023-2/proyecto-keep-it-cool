---
layout: post
title:  "Avanzando en la solución Premium"
date:   2023-11-09
categories: posts
---

# Avance en Premium

## Camara

Se avanzo en el código de arduino para el manejo de la cámara, adaptando el código disponible en la documentación de Thingsboard. Falta probarlo en la placa y enviar a ThingsBoard.
Además falta crear el método de llamado en el main para invocar el sacado de foto.

## Sistema RFID

Por otro lado, trabajamos en el envio  de los datos de las tarjetas RFID a ThingsBoard logrando la verificación y adición de las tarjetas a una base de datos en ThingsBoard.
La base de datos es un Json el cual contiene todas las tarjetas permitidas de la siguiente forma: 

```js
// i es un entero que empieza en 0 y aumenta por cada tarjeta añadida.
"tarjeta0": "[codigo de la tarjeta]",
"tarjeta1": "[codigo de la tarjeta]",
"tarjeta2": "[codigo de la tarjeta]",
...
```

Para poder añadir lo que hacemos es tener un atributo de servidor con la cantidad de tarjetas de dónde obtenemos el indice para agregarle al Json.
