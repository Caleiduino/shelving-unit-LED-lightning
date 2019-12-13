# shelving-unit-LED-lightning
Arduino LED light system

Sistema de iluminación creativa de mueble de estanterías basado en Arduino y desarrollado por el artista José Manuel González y el estudio de diseño Property Creative dirigido por el arquitecto Liam Phelan.

https://cargocollective.com/geometriaemocional

http://www.lphelan.com/

Consiste en un sistema de control de espacios iluminados mediante tiras led ws2812b
que permite al usuario controlar por separado cada estante, mediante sistema HSV.

![91cikqGC+BL _AC_SX569_](https://user-images.githubusercontent.com/20140969/70261234-4ba52680-1792-11ea-8d23-bb63ed30e717.jpg)

El control remoto hackeado (usando la librería IRremote) para su uso mediante una arduino nano(master) y una arduino mega(slave),
permite al usuario control HSV, luminosidad y animaciones. También ofrece la posibilidad de composición de colores 
aleatoria y grabación de valores en la EEPROM. A continuación el diseño del mando customizado mediante vinilo impreso adhesivo:

![MANDO](https://user-images.githubusercontent.com/20140969/70262269-56f95180-1794-11ea-9734-f22ba1e28f6b.png)

El esquema de iluminación consiste en 8 espacios controlados mediante mapeado de leds con el simple uso de 5 señales digitales. Los leds se encuentran embutidos en perfiles de aluminio y PVC translúcido dentro del mueble.

![Estantería_LEDS](https://user-images.githubusercontent.com/20140969/70262053-eb16e900-1793-11ea-8cdf-6e16aff4bd4e.jpg)

Fueron de gran importancia para la realización del proyecto los siguientes tutoriales y repositorios:

Para el control remoto: https://github.com/z3t0/Arduino-IRremote

Para el sistema de alimentación de los LEDs: https://learn.adafruit.com/1500-neopixel-led-curtain-with-raspberry-pi-fadecandy

Para el control de LEDs: https://github.com/FastLED/FastLED

Para el sistema de conexiones: http://industriumvita.com/lighthouse-with-remote-controlled-led-beacon/

Fue muy de agradecer la ayuda encomiable y los consejos impagables del gran David Cuartielles. También fue de gran ayuda el disfrutar de una residencia artística en el Makerspace UNDERBROEN de Copenhagen, durante agosto de 2019, lugar en donde se desarrolló la mayor parte del diseño.

A continuación varias fotos del desarrollo del proyecto y un vídeo de youtube que muestra su funcionamiento tras la instalación en la casa del cliente:

![IMG_20190802_133024_1](https://user-images.githubusercontent.com/20140969/70611412-76193880-1c05-11ea-80bf-59cf1fd0dae1.jpg)
![IMG_20190805_131356](https://user-images.githubusercontent.com/20140969/70611483-8f21e980-1c05-11ea-86a9-551b29e01a41.jpg)
![IMG_20190807_094845](https://user-images.githubusercontent.com/20140969/70611577-b4aef300-1c05-11ea-83cb-b523fb28536b.jpg)
![IMG-20190914-WA0000](https://user-images.githubusercontent.com/20140969/70792507-af82ad00-1d99-11ea-8b43-60dcdde8de9a.jpeg)
![IMG_20190726_151242](https://user-images.githubusercontent.com/20140969/70611695-e2943780-1c05-11ea-92f9-0472ba8ed221.jpg)

Vídeo: https://youtu.be/OFv94LBmmmQ
