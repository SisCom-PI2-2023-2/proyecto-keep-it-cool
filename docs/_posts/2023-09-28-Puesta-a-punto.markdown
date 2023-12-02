---
layout: post
title:  "Estado actual del proyecto"
date:   2023-09-28
categories: posts
---

Este post es para mencionar lo que se ha hecho los días anteriores en el proyecto.

## 2023-09-12 y 2023-09-14

En estas fechas trabajamos en:

	* Comunicar al ESP con ThingsBoard
	* Manejar un servomotor con la placa
	* Manejar el servomotor con ThingsBoard a traves de la placa

## 2023-09-21

En este día trabajamos en el uso de un DHT22 para tomar la temperatura y la humedad para finalmente subirla a ThingsBoard.

Además implementamos la cadena de reglas y la alarma para enviar un correo cada vez que se cumple una condición, en nuestro caso, cuando el sensor de temperatura registraba una temperadura demasiado alta.

## 2023-09-26

Tratamos de enviar una señal para encender el ventilador que representa nuestro enfriamiento activo, esta señal depende de lógica que corre en la nube

## 2023-09-28

Logramos ejecutar la lógica en la nube y crear el guardado de atributos para a futuro poder cambiar el valor en el cual se activa el enfriamiento activo

Decidimos utilizar un relay para manejar el ventilador de refrigeración, la semana siguiente realizaremos pruebas combinando 
