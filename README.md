# shelving-unit-LED-lightning
LED lightning system - RC with Arduino

Sistema de iluminación creativa de mueble de estanterías desarrollado por el artista José Manuel González y el 
estudio de arquitectura Properties Creative dirigido por el arquitecto Liam Phelan.

https://cargocollective.com/geometriaemocional

http://www.lphelan.com/

Consiste en un sistema de control de espacios iluminados mediante tiras led ws2812b
que permite al usuario controlar por separado cada estante, mediante sistema HSV.

![91cikqGC+BL _AC_SX569_](https://user-images.githubusercontent.com/20140969/70261234-4ba52680-1792-11ea-8d23-bb63ed30e717.jpg)

El control remoto, hackeado para su uso mediante una arduino nano(master) y una arduino mega(slave),
permite al usuario control HSV, luminosidad y animaciones. También ofrece la posibilidad de composición de colores 
aleatoria y grabación de valores en la EEPROM.

El esquema de iluminación consiste en 8 espacios controlados mediante mapeado de leds con el simple uso de 5 señales digitales. Los leds se encuentran embutidos en perfiles de aluminio y PVC translúcido dentro del mueble.

https://learn.adafruit.com/1500-neopixel-led-curtain-with-raspberry-pi-fadecandy

https://github.com/FastLED/FastLED

http://industriumvita.com/lighthouse-with-remote-controlled-led-beacon/

<iframe width="560" height="315" src="https://www.youtube.com/embed/OFv94LBmmmQ" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>


