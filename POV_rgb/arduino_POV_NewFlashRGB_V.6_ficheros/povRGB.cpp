#include <Arduino.h>
#include <avr/pgmspace.h>
#include "povRGB.h"

String povtext = "HOLA";
//String povtext = " FOR THE FUN OF IT ";//PUT YOUR MESSAGE HERE!!- must be in all caps, spaces are fine, no punctuation
byte refreshrate = 1;//delay time for pixels to refresh in milliseconds- experiment with different values

//variable para setear los colores del texto
String povtext_color = "WMCY";

boolean invertir = false;

//get length of string povtext
int dimtext = povtext.length();

//incoming data storage
byte data2 = 0;//for portD

//pines a los transistores RGB
const byte pinR = 11;
const byte pinG = 10;
const byte pinB = 9;

//variables
byte n; //variable for loops
byte m; //variable for loops
byte t; //variable for loops
byte l; //variable for loops

int anchoLetra = 7;
int altoLetra = 8;

int delayInicio = 100;

//array para el patron de inicio
const boolean load[] = {
  1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 1, 0,
  0, 0, 0, 0, 0, 0, 0, 1
};

//--------------------------------------------------------------------------------------------------------
// REEMPLAZAR AQUI CON LOS DIBUJOS !!!

//------------------------------------------------------------------------------------------------------------------------------------------------------------

//The letters of the alphabet- edit the look of these if you want, just make sure the letters are 8 pixels wide
const boolean letterA[] PROGMEM = {
  0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterB[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterC[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterD[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterE[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterF[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterG[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterH[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterI[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterJ[] PROGMEM = {
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterK[] PROGMEM = {
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 0, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 1, 1, 1, 0,
  1, 1, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterL[] PROGMEM = {
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterM[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 1, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterN[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 0, 0, 1, 1,
  1, 1, 1, 1, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 1, 1, 1, 1,
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterO[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterP[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterQ[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 1, 0, 1, 1,
  1, 1, 0, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterR[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0,
  1, 1, 0, 1, 1, 1, 0,
  1, 1, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterS[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterT[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};


const boolean letterU[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterV[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 0, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterW[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 1, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1,
  1, 0, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterX[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 1, 0, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterY[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letterZ[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter33[] PROGMEM = {//signo de exclamacion !
0, 0, 0, 1, 0, 0, 0,  
0, 0, 0, 1, 0, 0, 0,  
0, 0, 0, 1, 0, 0, 0,  
0, 0, 0, 1, 0, 0, 0,  
0, 0, 0, 1, 0, 0, 0,  
0, 0, 0, 0, 0, 0, 0,  
0, 0, 0, 1, 0, 0, 0,  
0, 0, 0, 0, 0, 0, 0 
};

const boolean letter0[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter1[] PROGMEM = {
  0, 0, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter2[] PROGMEM = {
  0, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter3[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  0, 0, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter4[] PROGMEM = {
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter5[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter6[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter7[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1,
  0, 0, 0, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter8[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean letter9[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 0,
  1, 1, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 1, 1,
  1, 1, 0, 0, 0, 1, 1,
  0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 0
};

const boolean dibujo_a[] PROGMEM = {
0, 0, 0, 0, 0, 0, 0,  
0, 1, 0, 0, 0, 1, 0,  
1, 1, 1, 0, 1, 1, 1,  
1, 1, 1, 1, 1, 1, 1,  
1, 1, 1, 1, 1, 1, 1,  
0, 1, 1, 1, 1, 1, 0,  
0, 0, 1, 1, 1, 0, 0,  
0, 0, 0, 1, 0, 0, 0
};
 
String dibujo_a_color = { "MMMMMMM" };

////////////////////////////////////////////////////////////////////////

void setup_povRGB(){
  //port/pin assignments- set all pins to output- more info here: http://www.arduino.cc/en/Reference/PortManipulation

  DDRD = 0xFF;//port d- digital pins 0-7
  //para los pines que manejan el color
  pinMode (pinR, OUTPUT);
  pinMode (pinG, OUTPUT);
  pinMode (pinB, OUTPUT);

  //FLASHADAS EN EL SETUP PARA PROBAR COSAS
  //defino color
  //  digitalWrite (pinB, HIGH);
  //  digitalWrite (pinG, LOW);
  //  digitalWrite (pinR, LOW);
  colorSetup( 'W');
  patronInicio();
  colorSetup( 'R');
  patronInicio();
  colorSetup( 'G');
  patronInicio();
  colorSetup( 'B');
  patronInicio();

}

//FUNCIONES-------------------------------------------------------------------------------------
void sendToWand(const boolean letterArray[]) { //function to get array data

  //una funcion para mandar los colores en String asociado

  for (t = 0; t < anchoLetra; t++) { //for each time step
    // l es la fila del array

    //PINES 0-7 D
    for (l = 0; l < altoLetra; l++) { //for next eight rows of data
      data2 = data2 << 1;//bitwise shift left
      data2 |= pgm_read_byte_near(letterArray + (l * anchoLetra + t)); //add next value from dataset
    }

    //SET PINS:
    PORTD = data2; //0-7
    if (invertir == true) {
    PORTD = PORTD ^ B11111111;
    }
    delay(refreshrate);
    //clear data storage
    data2 = 0;
  }
}

void sendDrawToWand(const boolean letterArray[], String colorDibujo) { //function to get array data

  //una funcion para mandar los colores en String asociado

  for (t = 0; t < anchoLetra; t++) { //for each time step
    // l es la fila del array

    //coloreo segun su String asociado, falta recibir String
    colorSetup(colorDibujo.charAt(t));

    //PINES 0-7 D
    for (l = 0; l < altoLetra; l++) { //for next eight rows of data
      data2 = data2 << 1;//bitwise shift left
      data2 |= pgm_read_byte_near(letterArray + (l * anchoLetra + t)); //add next value from dataset
    }

    //SET PINS:
    PORTD = data2; //0-7
    delay(refreshrate);
    //clear data storage
    data2 = 0;
  }
}

//funcion para pasarle los colores con las letras W,R,G,B,Y,C,M
void colorSetup(char _n) { //que no se llama mas n
  if  ( _n == 'W') {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, HIGH);
  }
  else if ( _n == 'R') {
    digitalWrite(pinB, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
  }
  else if ( _n == 'G' ) {
    digitalWrite(pinB, LOW);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, LOW);
  }
  else if  ( _n == 'B' ) {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, LOW);
  }
  else if ( _n == 'Y') {
    digitalWrite(pinB, LOW);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, HIGH);
  }
  else if ( _n == 'C' ) {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, HIGH);
    digitalWrite(pinR, LOW);
  }
  else if  ( _n == 'M' ) {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
  }
  else if  ( _n == 'M' ) {
    digitalWrite(pinB, HIGH);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, HIGH);
  }
  else if  ( _n == ' ') {
    digitalWrite(pinB, LOW);
    digitalWrite(pinG, LOW);
    digitalWrite(pinR, LOW);
  }

}

void patronInicio() {

  //run intialization so we know device is working- leds should light up in order from top of wand to bottom
  for (byte j = 0; j < altoLetra; j++) { //for each time step

    for (byte i = 0; i < altoLetra; i++) { //for next eight rows of data
      data2 = data2 << 1;//bitwise shift left
      data2 |= load[(i * altoLetra + j)]; //add next value from dataset
    }

    PORTD = data2;

    delay(delayInicio);
  }
  //clear data storage
  data2 = 0;
  //clear ports- set all arduino pins to 0Volts
  PORTD = data2;

}

void apagarLEDs(int tiempo) {
  if (invertir == false) {
    PORTD = 0; //probar medio raro
  }
  if (invertir == true) {
    PORTD = B11111111;
  }

  delay(refreshrate * tiempo);
}

void loop_povRGB() {
 
  //space at beginning of text
  //PORTD = 0;// aca apaga todo el PORTD
  apagarLEDs(3);

  for (n = 0; n < dimtext; n++) { //go through each character of povtext and call function sendToWand to display letter

    //acá aplico el color, colores: WRGBYCM
    colorSetup(povtext_color.charAt(n));
    //colorSetup( 'W');

    if (povtext.charAt(n) == 'A') {
      sendToWand(letterA);
    }
    else if (povtext.charAt(n) == 'B') {
      sendToWand(letterB);
    }
    else if (povtext.charAt(n) == 'C') {
      sendToWand(letterC);
    }
    else if (povtext.charAt(n) == 'D') {
      sendToWand(letterD);
    }
    else if (povtext.charAt(n) == 'E') {
      sendToWand(letterE);
    }
    else if (povtext.charAt(n) == 'F') {
      sendToWand(letterF);
    }
    else if (povtext.charAt(n) == 'G') {
      sendToWand(letterG);
    }
    else if (povtext.charAt(n) == 'H') {
      sendToWand(letterH);
    }
    else if (povtext.charAt(n) == 'I') {
      sendToWand(letterI);
    }
    else if (povtext.charAt(n) == 'J') {
      sendToWand(letterJ);
    }
    else if (povtext.charAt(n) == 'K') {
      sendToWand(letterK);
    }
    else if (povtext.charAt(n) == 'L') {
      sendToWand(letterL);
    }
    else if (povtext.charAt(n) == 'M') {
      sendToWand(letterM);
    }
    else if (povtext.charAt(n) == 'N') {
      sendToWand(letterN);
    }
    else if (povtext.charAt(n) == 'O') {
      sendToWand(letterO);
    }
    else if (povtext.charAt(n) == 'P') {
      sendToWand(letterP);
    }
    else if (povtext.charAt(n) == 'Q') {
      sendToWand(letterQ);
    }
    else if (povtext.charAt(n) == 'R') {
      sendToWand(letterR);
    }
    else if (povtext.charAt(n) == 'S') {
      sendToWand(letterS);
    }
    else if (povtext.charAt(n) == 'T') {
      sendToWand(letterT);
    }
    else if (povtext.charAt(n) == 'U') {
      sendToWand(letterU);
    }
    else if (povtext.charAt(n) == 'V') {
      sendToWand(letterV);
    }
    else if (povtext.charAt(n) == 'W') {
      sendToWand(letterW);
    }
    else if (povtext.charAt(n) == 'X') {
      sendToWand(letterX);
    }
    else if (povtext.charAt(n) == 'Y') {
      sendToWand(letterY);
    }
    else if (povtext.charAt(n) == 'Z') {
      sendToWand(letterZ);
    }
    else if (povtext.charAt(n) == '!') {
      sendToWand(letter33);
    }
    else if (povtext.charAt(n) == '0') {
      sendToWand(letter0);
    }
    else if (povtext.charAt(n) == '1') {
      sendToWand(letter1);
    }
    else if (povtext.charAt(n) == '2') {
      sendToWand(letter2);
    }
    else if (povtext.charAt(n) == '3') {
      sendToWand(letter3);
    }
    else if (povtext.charAt(n) == '4') {
      sendToWand(letter4);
    }
    else if (povtext.charAt(n) == '5') {
      sendToWand(letter5);
    }
    else if (povtext.charAt(n) == '6') {
      sendToWand(letter6);
    }
    else if (povtext.charAt(n) == '7') {
      sendToWand(letter7);
    }
    else if (povtext.charAt(n) == '8') {
      sendToWand(letter8);
    }
    else if (povtext.charAt(n) == '9') {
      sendToWand(letter9);
    }
    else if (povtext.charAt(n) == 'a') {
      sendDrawToWand(dibujo_a, dibujo_a_color);
    }
    else if (povtext.charAt(n) == ' ') {
      //PORTD = 0;
      apagarLEDs(3); //off for 3 times
    }

    //space between each character
    //PORTD = 0 ;//apaga el PORTD
    apagarLEDs(1);
  }

  //space at end of text
  // PORTD = 0;//apaga PORTD

  //aca apago todo los leds
  apagarLEDs(3); 
}
