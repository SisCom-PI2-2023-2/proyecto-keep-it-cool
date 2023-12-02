---
layout: post
title:  "Finalizacion de MVP"
date:   2023-10-24 
categories: posts
---

Continuamos probando lo unico que no pudimos verificar que fue el envio por mail ante una alerta, al intentar probar encotramos el error de que no estaba mandando el mail. Luego de probar varias cosas encotramos que el error es que cuando probamos
mandar un mail lo hicimos con la cuenta de Thingboard que tiene mas funcionalidades pero ahora al intentar utilizar la version demo se debe hacer distinto. Tras investigar pudimos arreglar y correctamente enviar un mail pero se descubrio que no se pueden
usar cuentas gmail para enviar la alerta y probando con alternativas encotramos que los correos de microsoft se pueden utilizar sin mucha dificultad, por lo que se deberia crear una cuenta outlook para enviar los correos del obligatorio.

Una vez arreglado este error podemos decir que (sin contar la maqueta) el MVP esta finalizado.

## Estandar

Luego de terminar y verificar todo de nuevo, empezamos a trabajar en el nivel estandar del projecto, investigando el uso de las tarjeta RFID y como implementarlas en el sistema. Luego de pensar decidimos que la base de datos con todas las tarjetas permitidas seria un JSON como atributo
de servidor en Thingsboard, esto implica que el chequeo de la tarjeta y el guardado del historial de las mismas debe ser programado en Thingsboard. 

Para esto empezamos con el mecanismo de verificar que el codigo enviado por la placa sea una tarjeta verificada por lo que para terminar el dia implementamos la rulechain para verificar la tarjeta, esto implica obtener las tarjetas verificadas, y con un script ver si se encuentra la
tarjeta recibida. Para esto utilizamos originate attributes y un script en JS.

 
```javascript
let tar = JSON.parse(metadata.ss_tarjetasPermitidas);
let esValida = false;

for (key in tar) {
  if (metadata.ss_ultimaTarjeta = tar[key])
    esValida = true;
}
return esValida;1

```
