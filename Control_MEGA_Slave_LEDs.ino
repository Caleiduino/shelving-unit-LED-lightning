// Control de LEDs con la Arduino Mega conectada por el serial a la Arduino nano que maneja los comandos del mando RC

#include <EEPROM.h> // LIBRERIA PARA GUARDAR PARAMETROS EN LA MEMORIA DE ARDUINO
#include <FastLED.h> // LIBRERIA DE CONTROL DE LEDS

// Numero de LEDs por tira . Ponemos un número mayor del necesario.
#define NUM_LEDS1 258 
#define NUM_LEDS2 258 
#define NUM_LEDS3 258 
#define NUM_LEDS4 258
#define NUM_LEDS5 258
//---------------------------------------------- 
/*
uint8_t brightness = 114;
uint8_t colourscheme = 0;
uint8_t colourschemeqty;

CRGBPalette16 currentPalette;
TBlendType    currentBlending;

extern CRGBPalette16 static_WhitePalette;
extern const TProgmemPalette16 static_WhitePalette_p PROGMEM;
*/
//---------------------------------------------- 

// Pines de datos para cada tira de LEDs
#define DATA_PIN1 2
#define DATA_PIN2 3
#define DATA_PIN3 4
#define DATA_PIN4 5
#define DATA_PIN5 6

#define COLOR_ORDER BGR // Orden de colores en WS2812B


// Define the array of leds
CRGB leds1[NUM_LEDS1];
CRGB leds2[NUM_LEDS2];
CRGB leds3[NUM_LEDS3];
CRGB leds4[NUM_LEDS4];
CRGB leds5[NUM_LEDS5];

////////////// PARA TRABAJAR EN CHSV
byte hue = 0; // TONO - EMPEZAMOS CON EL VERDE / AMARILLO / NARANJA / ROJO / MAG / VIOL / AZUL / VERDE
byte saturation = 100;  // SATURACION MEDIA
byte value = 100; // BRILLO MEDIO

byte color[] = {30, 30, 30, 30, 30, 30, 30, 30}; // TONO - EMPEZAMOS CON EL VERDE / AMARILLO / NARANJA / ROJO / MAG / VIOL / AZUL / VERDE
byte saturacion[] = {100, 100, 100, 100, 100, 100, 100, 100};  // SATURACION MEDIA
byte brillo[] = {100, 100, 100, 100, 100, 100, 100, 100}; //VALOR MEDIO
uint8_t brightness = 100; // Luminosidad media

// -------------PARÁMETROS DEL CONTROL DE DATOS DEL RC-----------------------------
/////////////
int     animation_rate = 1; 
int     mode = 9; // Animation mode index
boolean on = true;
char    incoming_command /* = 'Q'*/;
/////////////
volatile boolean animate = true;
volatile long animation_change_timeout;


void setup() { 

       LEDS.setBrightness(brightness);
       //set_max_power_in_volts_and_milliamps(5, 500);
       
       FastLED.addLeds<WS2812B, DATA_PIN1, RGB>(leds1, NUM_LEDS1);
       FastLED.addLeds<WS2812B, DATA_PIN2, RGB>(leds2, NUM_LEDS2);
       FastLED.addLeds<WS2812B, DATA_PIN3, RGB>(leds3, NUM_LEDS3);
       FastLED.addLeds<WS2812B, DATA_PIN4, RGB>(leds4, NUM_LEDS4);
       FastLED.addLeds<WS2812B, DATA_PIN5, RGB>(leds5, NUM_LEDS5);
       
       Serial.begin(9600);
       
}


void loop() { 
  
//int color[] = {random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255)}; // TONO - 8 TIRAS + TODAS JUNTAS
//int saturacion[] = {random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255), random(0, 255)};  // SATURACION MEDIA
//int brillo[] = {random(0, 160), random(0, 160), random(0, 160), random(0, 160), random(0, 160), random(0, 160), random(0, 160), random(0, 160), random(0, 160)}; // BRILLO MEDIO
    

///////// Control mando a distancia/ 24 COMANDOS de A->Z
switch (incoming_command) {
    
    case 'A': 
    if(mode == 4){ // Encender/Apagar Cuarta Tira
        lamp4();
        mode = 13;
      }else{
        Apagar4();
        mode = 4;
      }
      break;
      
    case 'B':
    if(mode == 3){ // Encender/Apagar Tercera Tira
        lamp3();
        mode = 12;
      }else{
        Apagar3();
        mode = 3;
      }
      break;
      
    case 'C':
    if(mode == 2){ // Encender/Apagar Segunda Tira
        lamp2();
        mode = 11;
      }else{
        Apagar2();
        mode = 2;
      }
      break;
      
    case 'D':
     if(mode == 1){ // Encender/Apagar Primera Tira
        lamp1();
        mode = 10;
      }else{
        Apagar1();
        mode = 1;
      }
      break;
      
    case 'E':
    if(mode == 8){ // Encender/Apagar Octava Tira
        lamp8();
        mode = 17;
      }else{
        Apagar8();
        mode = 8;
      }
      break;
      
    case 'F': 
    if(mode == 7){ // Encender/Apagar Septima Tira
        lamp7();
        mode = 16;
      }else{
        Apagar7();
        mode = 7;
      }
      break;
      
    case 'G':
    if(mode == 6){ // Encender/Apagar Sexta Tira
        lamp6();
        mode = 15;
      }else{
        Apagar6();
        mode = 6;
      } 
      break;
      
    case 'H':
    if(mode == 5){ // Encender/Apagar Quinta Tira
        lamp5();
        mode = 14;
      }else{
        Apagar5();
        mode = 5;
      }
      break;
      
    case 'I': // ------------------brightness +
    if (brightness <= 200){
          brightness += 10;
          FastLED.setBrightness(brightness);
        }
      break;
      
    case 'J': // -----------------value +
    if (value <= 220){
          value += 20;
        }
      break;
      
    case 'K': // ----------------saturacion +
    if (saturation <= 220){
          saturation += 20;
        } 
      break;
      
    case 'L': // -----------------hue +
    if (hue <= 240){
          hue += 10;
        } 
      break;
      
    case 'M': // ----------------brightness -
    if (brightness >= 10){
          brightness -= 10;
          FastLED.setBrightness(brightness);
        } 
      break;
      
    case 'N': // ------------------ value -
    if (value >= 20){
          value -= 20;
        }
      break;

    case 'O': // -------------------saturation -
    if (saturation >= 20){
          saturation -= 20;
        }
      break;
      
    case 'P': // -------------------hue -
    if (hue >= 10){
          hue -= 10;
        }
      break;
      
    case 'Q': // // ON/OFF TODOS los LEDS IGUALES con valores HSV guardados en la EEPROM
    if(mode == 18){ 
      lampX(); // Boton R CONTROL RGB
        mode = 9;
      }else{
        ApagarTodo();
        mode = 18;
      } 
    //////////
    
      break;
      
    case 'R': // ON/OFF todos los LEDS Con valores HSV(Luz cálida) guardados por defecto HSV(30, 100, 100) y se puede cambiar;
    if(mode == 0){ 
      lamp();
        //ApagarTodo();
        mode = 9;
      }else{
        //lamp();
        ApagarTodo();
        mode = 0;
      }
      break;
      
    case 'S': //-------------Salva los valores elegidos HSV para TODOS los LEDS en EEPROM
    salvarHSV();
    delay(500);
      break;
      
    case 'T'://---------------Salva los valores random() en la EEPROM
    salvarRandomHSV();
    delay(500);
      break;
      
    case 'U': // --------------APAGA TODO OFF
    if(mode == 9){
    ApagarTodo();
    mode = 9;
    }else{
     ApagarTodo();
     mode = 9;
    }
      break;
      
    case 'V': 
    //------------------------ CAMBIAR animationA(), animationB(), animationC()
    if(mode == 21){
      animationA();
      mode = 22;
    }else if(mode == 22){
      animationB();
      mode = 23;
    }else{
      animationC();
      mode = 21;
    }
        break;
        
    case 'W': // -----------Enciende los LEDS separados con valores random() guardados en la EEPROM
    if(mode == 20){
      lampRandomEEPROM();
      mode = 20;
    }else{
      mode = 20;    
    }
      break;
    case 'X': // --------------Enciende los LEDS separados con valores random()
    if(mode == 19){
    RandomHsv();
    lampRandom();
    mode = 19;
    }else{
    mode = 19;
    }  
      break;

}
    switch (mode) {
    case 0:
      lamp(); // BOTON Q LAMP() SE ENCIENDEN TODOS LOS LEDS Y SE PUEDEN CAMBIAR HSV
      break;
     case 1:
      lamp1();// BOTON D PRIMERA TIRA
      break;
    case 2:
      lamp2();// BOTON C SEGUNDA TIRA
      break;
    case 3:
      lamp3();// BOTON B TERCERA TIRA
      break;
    case 4:
      lamp4();// BOTON A CUARTA TIRA
      break;
    case 5:
      lamp5();// BOTON H QUINTA TIRA
      break;
    case 6:
      lamp6();// BOTON G SEXTA TIRA
      break;
    case 7:
      lamp7();// BOTON F SEPTIMA TIRA
      break;
     case 8:
      lamp8();// BOTON E OCTAVA TIRA
      break;
     case 9:
      ApagarTodo();
      break;
     case 10:
      Apagar1();
      break;
     case 11:
      Apagar2();
      break;
     case 12:
      Apagar3();
      break;
     case 13:
      Apagar4();
      break;
     case 14:
      Apagar5();
      break;
     case 15:
      Apagar6();
      break;
     case 16:
      Apagar7();
      break;
     case 17:
      Apagar8();
      break;
      case 18:
      lampX(); // LAMPX() TODOS LOS LEDS SE ENCIENDEN IGUALES CON VALORES DE LA EEPROM
      break;
      case 19:
      lampRandom(); // COLORES ALEATORIOS DE TODOS LOS ESPACIOS
      break;
      case 20:
      lampRandomEEPROM(); // LEE COLORES ALEATORIOS DE TODOS LOS ESPACIOS EN LA EEPROM
      case 21:
      animationA();
      break;
      case 22:
      animationB();
      break;
      case 23:
      animationC();
      break;

  } 

  animation_change_timeout = 0;
  animate = true;
}


//----------SEÑAL IR--------------------------------------------------


void check_for_input() {
  if (animation_change_timeout > 100) {
    if (Serial.available() > 0) {
      // read the incoming byte:
      incoming_command = Serial.read();
      
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incoming_command);
      animate = false;
    }
  }
}

//--------------LAMP1 SE ENCIENDE LA PRIMERA TIRA DE LEDS 
//--------------(3 primeros LEDS tira1 + 4 últimos LEDS de tira2)
// Funciona perfectamente
void lamp1 () {
  long loop_start = millis();
  while(animate) {
    
    ////// Mapeo de Primera Tira LEDS
    
    for(int x = 0; x < 61; x++){
      //LEDS.setBrightness(luminosidad);
        leds1[x] = CHSV( hue, saturation, value);
    }
    //FastLED.show();
    
    for(int x = 0; x < 56; x++){
      //LEDS.setBrightness(luminosidad);
        leds4[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp1()

//////////////////LAMP2 SE ENCIENDE LA SEGUNDA TIRA DE LEDS 
//--------------(4 LEDS del 3 al 6 de la tira1)
void lamp2 () {
  long loop_start = millis();
  while(animate) {
   
    ////// Mapeo de Segunda Tira LEDS
    
    for(int x = 61; x < 117; x++){
      //LEDS.setBrightness(luminosidad);
        leds1[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    //////// Fin Mapeo LEDS
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp2()

//////////////////LAMP3 SE ENCIENDE LA TERCERA TIRA DE LEDS 
//--------------(3 LEDS del 7 al 9 de la tira1)
void lamp3 () {
  long loop_start = millis();
  while(animate) {
    
    ////// Mapeo de Tercera Tira LEDS
    
    for(int x = 117; x < 236; x++){
      //LEDS.setBrightness(luminosidad);
        leds1[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    //////// Fin Mapeo LEDS
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp3()

//////////////////LAMP4 SE ENCIENDE LA CUARTA TIRA DE LEDS 
//--------------(6 LEDS del 0 al 5 de la tira2)
void lamp4 () {
  long loop_start = millis();
  while(animate) {
   
    ////// Mapeo de Segunda Tira LEDS
    
    for(int x = 0; x < 182; x++){
      //LEDS.setBrightness(luminosidad);
        leds2[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    //////// Fin Mapeo LEDS
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp4()

//////////////////LAMP5 SE ENCIENDE LA QUINTA TIRA DE LEDS 
//--------------(3 LEDS del 0 al 2 de la tira3 + tira4)
void lamp5 () {
  long loop_start = millis();
  while(animate) {
   
    ////// Mapeo de Cuarta Tira LEDS
    
    for(int x = 0; x < 59; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    for(int x = 182; x < 241; x++){
      //LEDS.setBrightness(luminosidad);
       leds2[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    //////// Fin Mapeo LEDS
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp5()

//////////////////LAMP6 SE ENCIENDE LA SEXTA TIRA DE LEDS 
//--------------(4 LEDS del 3 al 6 de la tira3)
void lamp6 () {
  long loop_start = millis();
  while(animate) {
   
    ////// Mapeo de Sexta Tira LEDS
    
    for(int x = 59; x < 112; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
   
    //////// Fin Mapeo LEDS
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp6()

//////////////////LAMP7 SE ENCIENDE LA SEPTIMA TIRA DE LEDS 
//--------------(3 LEDS del 7 al 9 de la tira3)
void lamp7 () {
  long loop_start = millis();
  while(animate) {
    
    ////// Mapeo de Septima Tira LEDS
    
    for(int x = 112; x < 241; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    //////// Fin Mapeo LEDS
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp7()

//////////////////LAMP8 SE ENCIENDE LA OCTAVA TIRA DE LEDS 
//--------------(10 LEDS de la tira5)
void lamp8 () {
  long loop_start = millis();
  while(animate) {
    
    ////// Mapeo de Octava Tira LEDS
    
    for(int x = 0; x < 257; x++){
      //LEDS.setBrightness(luminosidad);
        leds5[x] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    //////// Fin Mapeo LEDS
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp8()

//--------------APAGAR TODO---------------------------------------------

// Funciona perfectamente
void ApagarTodo() {
  long loop_start = millis();
  while(animate) {
    for(int i=0; i<NUM_LEDS5; i++) {
      leds1[i] = CHSV( 0,0,0);
      leds2[i] = CHSV( 0,0,0);
      leds3[i] = CHSV( 0,0,0);
      leds4[i] = CHSV( 0,0,0);
      leds5[i] = CHSV( 0,0,0);
    }
    
    FastLED.show();
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}

//--------------APAGAR lamp1---------------------------------------------

// Funciona perfectamente
void Apagar1 () {
  long loop_start = millis();
  while(animate) {
    ////// Mapeo de Primera Tira LEDS
    for(int x = 0; x < 61; x++){
        leds1[x] = CHSV( 0,0,0);
    }
    //FastLED.show();
    
    for(int x = 0; x < 56; x++){
        leds4[x] = CHSV( 0,0,0);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}
//--------------APAGAR lamp2---------------------------------------------

// Funciona perfectamente
void Apagar2 () {
  long loop_start = millis();
  while(animate) {
    ////// Mapeo de Segunda Tira LEDS
    for(int x = 61; x < 117; x++){
        leds1[x] = CHSV( 0,0,0);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}
//--------------APAGAR lamp3---------------------------------------------

// Funciona perfectamente
void Apagar3 () {
  long loop_start = millis();
  while(animate) {
    for(int x = 117; x < 236; x++){
        leds1[x] = CHSV( 0,0,0);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}
//--------------APAGAR lamp4---------------------------------------------

// Funciona perfectamente
void Apagar4 () {
  long loop_start = millis();
  while(animate) {
    for(int x = 0; x < 182; x++){
        leds2[x] = CHSV( 0,0,0);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}
//--------------APAGAR lamp5---------------------------------------------

// Funciona perfectamente
void Apagar5 () {
  long loop_start = millis();
  while(animate) {
    
    for(int x = 0; x < 59; x++){
        leds3[x] = CHSV( 0,0,0);
    }
    
    for(int x = 182; x < 241; x++){
        leds2[x] = CHSV( 0,0,0);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}
//--------------APAGAR lamp6---------------------------------------------

// Funciona perfectamente
void Apagar6 () {
  long loop_start = millis();
  while(animate) {
    for(int x = 59; x < 112; x++){
        leds3[x] = CHSV( 0,0,0);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}
//--------------APAGAR lamp7---------------------------------------------

// Funciona perfectamente
void Apagar7 () {
  long loop_start = millis();
  while(animate) {
    for(int x = 112; x < 241; x++){
        leds3[x] = CHSV( 0,0,0);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}
//--------------APAGAR lamp8---------------------------------------------

// Funciona perfectamente
void Apagar8 () {
  long loop_start = millis();
  while(animate) {
    for(int x = 0; x < 257; x++){
        leds5[x] = CHSV( 0,0,0);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    check_for_input();
  }
}

//--------------LAMP() TODOS LOS LEDS SE PUEDEN CAMBIAR HSV----------------------------------------------

// Funciona perfectamente
void lamp() {
  long loop_start = millis();
  while(animate) {
   
    for(int i=0; i<NUM_LEDS1; i++) { /// ILUMINAMOS TODAS LAS TIRAS
     
      leds1[i] = CHSV( hue, saturation, value);
      leds2[i] = CHSV( hue, saturation, value);
      leds3[i] = CHSV( hue, saturation, value);
      leds4[i] = CHSV( hue, saturation, value);
      leds5[i] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp()

//--------------LAMPX() TODOS LOS LEDS SE ENCIENDEN CON VALORES DE LA EEPROM----------------------

// Funciona perfectamente
void lampX() {
  long loop_start = millis();
  while(animate) {
    
      leerHSV();
  
    for(int i=0; i<NUM_LEDS1; i++) { /// ILUMINAMOS TODAS LAS TIRAS
      leds1[i] = CHSV( hue, saturation, value);
      leds2[i] = CHSV( hue, saturation, value);
      leds3[i] = CHSV( hue, saturation, value);
      leds4[i] = CHSV( hue, saturation, value);
      leds5[i] = CHSV( hue, saturation, value);
    }
    FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lamp()


////////////////----------------COLORES ALEATORIOS DE TODOS LOS ESPACIOS---------------
void lampRandom () {
  
  long loop_start = millis();
  while(animate) {
    
    
    ////// Mapeo de Primera Tira LEDS
    
    for(int x = 0; x < 61; x++){
      leds1[x] = CHSV( color[0], saturacion[8], brillo[16]);
    }
    
    for(int x = 0; x < 56; x++){
      leds4[x] = CHSV( color[0], saturacion[8], brillo[16]);
    }
    
    ////// Mapeo de Segunda Tira LEDS
    for(int x = 61; x < 117; x++){
        leds1[x] = CHSV( color[1], saturacion[9], brillo[17]);
    }
    
    ////// Mapeo de Tercera Tira LEDS
    for(int x = 117; x < 236; x++){
      //LEDS.setBrightness(luminosidad);
        leds1[x] = CHSV( color[2], saturacion[10], brillo[18]);
    }
    
    ////// Mapeo de Cuarta Tira LEDS
    for(int x = 0; x < 182; x++){
      //LEDS.setBrightness(luminosidad);
        leds2[x] = CHSV( color[3], saturacion[11], brillo[19]);
    }
    
    ////// Mapeo de Quinta Tira LEDS
    for(int x = 0; x < 59; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( color[4], saturacion[12], brillo[20]);
    }
    
    for(int x = 182; x < 241; x++){
      //LEDS.setBrightness(luminosidad);
       leds2[x] = CHSV( color[4], saturacion[12], brillo[20]);
    }
    
    ////// Mapeo de Sexta Tira LEDS
    for(int x = 59; x < 112; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( color[5], saturacion[13], brillo[21]);
    }
    
    ////// Mapeo de Septima Tira LEDS
    for(int x = 112; x < 241; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( color[6], saturacion[14], brillo[22]);
    }
    
    ////// Mapeo de Octava Tira LEDS
    for(int x = 0; x < 257; x++){
      //LEDS.setBrightness(luminosidad);
        leds5[x] = CHSV( color[7], saturacion[15], brillo[23]);
    }
   FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lampRandom()

////////////////----------------COLORES ALEATORIOS DE TODOS LOS ESPACIOS GRABADOS EN EEPROM---------------
void lampRandomEEPROM() {
  long loop_start = millis();
  while(animate) {

    leerHSVRandom();
    ////// Mapeo de Primera Tira LEDS
    
    for(int x = 0; x < 61; x++){
      leds1[x] = CHSV( color[0], saturacion[8], brillo[16]);
    }
    
    for(int x = 0; x < 56; x++){
      leds4[x] = CHSV( color[0], saturacion[8], brillo[16]);
    }
    
    ////// Mapeo de Segunda Tira LEDS
    for(int x = 61; x < 117; x++){
        leds1[x] = CHSV( color[1], saturacion[9], brillo[17]);
    }
    
    ////// Mapeo de Tercera Tira LEDS
    for(int x = 117; x < 236; x++){
      //LEDS.setBrightness(luminosidad);
        leds1[x] = CHSV( color[2], saturacion[10], brillo[18]);
    }
    
    ////// Mapeo de Cuarta Tira LEDS
    for(int x = 0; x < 182; x++){
      //LEDS.setBrightness(luminosidad);
        leds2[x] = CHSV( color[3], saturacion[11], brillo[19]);
    }
    
    ////// Mapeo de Quinta Tira LEDS
    for(int x = 0; x < 59; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( color[4], saturacion[12], brillo[20]);
    }
    
    for(int x = 182; x < 241; x++){
      //LEDS.setBrightness(luminosidad);
       leds2[x] = CHSV( color[4], saturacion[12], brillo[20]);
    }
    
    ////// Mapeo de Sexta Tira LEDS
    for(int x = 59; x < 112; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( color[5], saturacion[13], brillo[21]);
    }
    
    ////// Mapeo de Septima Tira LEDS
    for(int x = 112; x < 241; x++){
      //LEDS.setBrightness(luminosidad);
        leds3[x] = CHSV( color[6], saturacion[14], brillo[22]);
    }
    
    ////// Mapeo de Octava Tira LEDS
    for(int x = 0; x < 257; x++){
      //LEDS.setBrightness(luminosidad);
        leds5[x] = CHSV( color[7], saturacion[15], brillo[23]);
    }
   FastLED.show();
    
    animation_change_timeout = millis() - loop_start;
    delay(50);
    check_for_input();
  }
} // Hasta aquí lampRandom()

///////////////////////--------------------SALVAR HSV de TODAS LAS TIRAS
void salvarHSV() {
    EEPROM.write(50, hue);
    EEPROM.write(51, saturation);
    EEPROM.write(52, value);
  }

  ////////////////////////------------------LEER HSV DE EEPROM PARA TODOS LEDS

  void leerHSV() { 
      hue = EEPROM.read(50);
      saturation = EEPROM.read(51);
      value = EEPROM.read(52);
  }

////////////////////////------------------LEER HSV DE EEPROM RANDOM

void leerHSVRandom(){
  for (int i = 0; i < 8; i++) {
    color[i] = EEPROM.read(i);
    saturacion[i] = EEPROM.read(i + 8);
    brillo[i] = EEPROM.read(i + 16);
    }
    
}
///////////////////////--------------------GRABAR HSV de TODAS LAS TIRAS RANDOM
  void salvarRandomHSV() {
    for (int i = 0; i < 8; i++) {
    EEPROM.write(i, color[i]);
    EEPROM.write(i + 8, saturacion[i]);
    EEPROM.write(i + 16, brillo[i]);
  }

  }

////////////////////----------------------VALORES RANDOM COLOR/ SATURACION/ BRILLO
  void RandomHsv(){
  for (int i = 0; i < 8; i++) {
    color[i] = random(0, 255);
    saturacion[i+8] = random(0, 255);
    brillo[i+16] = random(0, 255);
    } 
}


//--------------------------Animacion A----------------------------
void animationA() {                                             // running red stripe.
long loop_start = millis();
  while(animate) {
  for (int i = 0; i < NUM_LEDS1; i++) {
    uint8_t red = (millis() / 10) + (i * 12);                    // speed, length
    if (red > 128) red = 0;
    leds1[i] = CRGB(red, 0, 0);
    leds2[i] = CRGB(red, 0, 0);
    leds3[i] = CRGB(red, 0, 0);
    leds4[i] = CRGB(red, 0, 0);
    leds5[i] = CRGB(red, 0, 0);
  }
  FastLED.show();
  animation_change_timeout = millis() - loop_start;
  delay(50);
  check_for_input();
} 
}// animationA()

//--------------------------Animacion B----------------------------
void animationB() { 
  long loop_start = millis();
  while(animate) {// running green stripe in opposite direction.
  for (int i = 0; i < NUM_LEDS1; i++) {
    uint8_t green = (millis() / 5) - (i * 12);                    // speed, length
    if (green > 128) green = 0;
    leds1[i] = CRGB(0, green, 0);
    leds2[i] = CRGB(0, green, 0);
    leds3[i] = CRGB(0, green, 0);
    leds4[i] = CRGB(0, green, 0);
    leds5[i] = CRGB(0, green, 0);
  }
  FastLED.show();
  animation_change_timeout = millis() - loop_start;
  delay(50);
  check_for_input();
} 
}// animationB()

//--------------------------Animacion C----------------------------
void animationC() { 
  long loop_start = millis();
  while(animate) {// running green stripe in opposite direction.
  for (int i = 0; i < NUM_LEDS1; i++) {
    uint8_t blue = (millis() / 20) - (i * 12);                    // speed, length
    if (blue > 128) blue = 0;
    leds1[i] = CRGB(0, 0, blue);
    leds2[i] = CRGB(0, 0, blue);
    leds3[i] = CRGB(0, 0, blue);
    leds4[i] = CRGB(0, 0, blue);
    leds5[i] = CRGB(0, 0, blue);
  }
  FastLED.show();
  animation_change_timeout = millis() - loop_start;
  delay(50);
  check_for_input();
} 
}// animationC()
