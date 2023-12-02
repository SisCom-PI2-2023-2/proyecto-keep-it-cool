---
layout: post
title:  "Intento de MVP"
date:   2023-10-17 
categories: posts
---

# Intento de MVP

Empezamos el desarrollo del MVP, intentando unir todos lo logrado hasta este punto:
 
  - Sensores DHT
  - Circuito para detectar estado de puerta y ademas servomotor para moverla al notar que esta abierta.
  - Relé y ventilador para el sistema de refrigeracion

## Complicaciones

Por separado ya se logro hacer funcionar todo pero al intentar unirlo no se pudo conseguir debido a constantes problemas con el codigo de Arduino. Luego de debuggear
se encontro el posible error: se esta utilizando una libreria de DHT incorrecta, que no coincide con la utilizada para escribir el codigo o el codigo de la libreria para leer temperatura no retorna ints dando
problemas al intentar mandar la respuesta a Thingsboard.

Aun asi se intento utilizar la funcion random para remplazar los sensores y se encotro que funciona todo correctamente menos el ventilador el cual aunque el relé se encienda correctamente este ultimo no se prende, 
no pudimos encotrar el porque.

Finalmente se solicito los componentes para ir trabajando en la solución estandar (RFID y buzzer)
