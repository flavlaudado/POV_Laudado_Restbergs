/*
  TAREA


  actualizar a letras chicas
  borrar todo lo que no sirva:
        -port B y D -> data1 y data3
        -Boton q cambia color
*/

#include <avr/pgmspace.h>//need to store letter arrays in flash memory- or else we run out of space, more info here: http://arduino.cc/en/Reference/PROGMEM

String povtext = "POV RGB";//PUT YOUR MESSAGE HERE!!- must be in all caps, spaces are fine, no punctuation
byte refreshrate = 1;//delay time for pixels to refresh in milliseconds- experiment with different values

//variable para setear los colores del texto
String povtext_color = "CMY RGB";

//get length of string povtext
int dimtext = povtext.length();

//array para el patron de inicio
const boolean load[] = {
  0, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 1,
  1, 1, 1, 1, 1, 1, 1, 0
};


//--------------------------------------------------------------------------------------------------------
// REEMPLAZAR AQUI CON LOS DIBUJOS !!!

//DIBUJO VARIABLE
const boolean dibujo_0[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_1[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_2[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_3[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_4[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_5[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_6[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_7[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_8[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

const boolean dibujo_9[] PROGMEM = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

};

//------------------------------------------------------------------------------------------------------------------------------------------------------------

//The letters of the alphabet- edit the look of these if you want, just make sure the letters m and w are 15 pixels wide and the rest are 12 pixels
const boolean letterA[] PROGMEM = {
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0
};

const boolean letterB[] PROGMEM = {
  0, 0, 0, 0, 0, 1,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 1,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1

};
const boolean letterC[] PROGMEM = {
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
};

const boolean letterD[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
};

const boolean letterE[] PROGMEM = {
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1,
  0, 0, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,

};

const boolean letterF[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
};
/*
  const boolean letterG[] PROGMEM = {
  0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0,
  };
*/
const boolean letterG[] PROGMEM = {
  1, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1,
  0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  1, 0, 0, 0, 0, 0

};

const boolean letterH[] PROGMEM = {
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0
};

const boolean letterI[] PROGMEM = {
  1, 1, 0, 0, 1, 1,
  1, 1, 1, 1, 1, 1,
  1, 1, 0, 0, 1, 1,
  1, 1, 0, 0, 1, 1,
  1, 1, 0, 0, 1, 1,
  1, 1, 0, 0, 1, 1,
  1, 1, 0, 0, 1, 1,
};

const boolean letterJ[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
};

const boolean letterK[] PROGMEM = {
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
};

const boolean letterL[] PROGMEM = {
  0, 0, 0, 1, 1, 1,
  0, 0, 0, 1, 1, 1,
  0, 0, 0, 1, 1, 1,
  0, 0, 0, 1, 1, 1,
  0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0
};

const boolean letterM[] PROGMEM = {
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
};

const boolean letterN[] PROGMEM = {
  0, 0, 1, 1, 0, 0,
  0, 0, 0, 1, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 0, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
};

const boolean letterO[] PROGMEM = {
  1, 0, 0, 0, 0, 1,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  1, 0, 0, 0, 0, 1

};
/*
  const boolean letterP[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
  };
*/
const boolean letterP[] PROGMEM = {
  0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 1,
  0, 0, 1, 1, 1, 1

};

const boolean letterQ[] PROGMEM = {
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1,
};

const boolean letterR[] PROGMEM = {
  0, 0, 0, 0, 0, 1,
  0, 0, 1, 1, 0, 0,
  0, 0, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1,
  0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 1, 1,
  0, 0, 1, 0, 0, 1,
  0, 0, 1, 1, 0, 0,

};

const boolean letterS[] PROGMEM = {
  0, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1,
  0, 0, 0, 1, 1, 1,
  0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 0, 0,
  1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 0,
};

const boolean letterT[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
};

const boolean letterU[] PROGMEM = {
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
};

const boolean letterV[] PROGMEM = {
  0, 1, 1, 1, 0, 1,
  0, 1, 1, 1, 0, 1,
  0, 0, 1, 0, 0, 1,
  0, 0, 1, 0, 0, 1,
  0, 0, 1, 0, 0, 1,
  0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 1,
  1, 0, 0, 0, 1, 1

};

/*
  const boolean letterV[] PROGMEM = {
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  };

*/
const boolean letterW[] PROGMEM = {
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
  0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 0,
};

const boolean letterX[] PROGMEM = {
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
};

const boolean letterY[] PROGMEM = {
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1,
  0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0,
  0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
};

const boolean letterZ[] PROGMEM = {
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0,
  0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0,
  0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
  0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0,
  0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};
//incoming data storage
byte data1 = 0;//for portB
byte data2 = 0;//for portD
byte data3 = 0;//for portC

//variables
byte n; //variable for loops
byte t; //variable for loops
byte l; //variable for loops

int anchoLetra = 6;
int altoLetra = 8;

//FUNCIONES-------------------------------------------------------------------------------------
void sendToWand(const boolean letterArray[]) { //function to get array data

  // USAR CIERTO ANCHO PARA LETRA Y PARA DIBUS
  //una funcion para mandar los colores en un array asociado o un String

  for (t = 0; t < anchoLetra; t++) { //for each time step
    //colorSetup( 'R');
    // l es la fila del array, que originalemente es de 20

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

void sendToWandMW(const boolean letterArray[]) { //M and W are extra wide- they have a special function to get array data (with 15 time steps instead of 12)

  //send data to leds via port/pin manipulation
  for (t = 0; t < 15; t++) { //for each time step

    for (l = 6; l < 14; l++) { //for next eight rows of data
      data2 = data2 << 1;//bitwise shift left
      data2 |= pgm_read_byte_near(letterArray + (l * 15 + t)); //add next value from dataset
    }

    //SET PINS:
    PORTD = data2;
    delay(refreshrate);
    //clear data storage
    data2 = 0;
  }
}

//funcion para pasarle los colores con las letras W,R,G,B,Y,C,M
void colorSetup(char n) {
  if  ( n == 'W') {
    digitalWrite(9, !HIGH);
    digitalWrite(10, !HIGH);
    digitalWrite(11, !HIGH);
  }
  else if ( n == 'R') {
    digitalWrite(9, !LOW);
    digitalWrite(10, !LOW);
    digitalWrite(11, !HIGH);
  }
  else if (n == 'G' ) {
    digitalWrite(9, !LOW);
    digitalWrite(10, !HIGH);
    digitalWrite(11, !LOW);
  }
  else if  ( n == 'B' ) {
    digitalWrite(9, !HIGH);
    digitalWrite(10, !LOW);
    digitalWrite(11, !LOW);
  }
  else if ( n == 'Y') {
    digitalWrite(9, !LOW);
    digitalWrite(10, !HIGH);
    digitalWrite(11, !HIGH);
  }
  else if (n == 'C' ) {
    digitalWrite(9, !HIGH);
    digitalWrite(10, !HIGH);
    digitalWrite(11, !LOW);
  }
  else if  ( n == 'M' ) {
    digitalWrite(9, !HIGH);
    digitalWrite(10, !LOW);
    digitalWrite(11, !HIGH);
  }

}

void patronInicio() {

  //run intialization so we know device is working- leds should light up in order from top of wand to bottom
  for (byte j = 0; j < 8; j++) { //for each time step

    for (byte i = 0; i < 8; i++) { //for next eight rows of data
      data2 = data2 << 1;//bitwise shift left
      data2 |= load[(i * 8 + j)]; //add next value from dataset
    }

    PORTD = data2;

    delay(200);
  }
  //clear data storage
  data2 = 0;
  //clear ports- set all arduino pins to 0Volts
  PORTD = data2;

}

void setup() {

  //port/pin assignments- set all pins to output- more info here: http://www.arduino.cc/en/Reference/PortManipulation

  DDRD = 0xFF;//port d- digital pins 0-7

  //para los pines que manejan el color
  pinMode (9, OUTPUT);
  pinMode (10, OUTPUT);
  pinMode (11, OUTPUT);

  //FLASHADAS EN EL SETUP PARA PROBAR COSAS
  //defino color
  //  digitalWrite (9, HIGH);
  //  digitalWrite (10, LOW);
  //  digitalWrite (11, LOW);
  colorSetup( 'W');
  patronInicio();
  colorSetup( 'R');
  patronInicio();
  colorSetup( 'G');
  patronInicio();
  colorSetup( 'B');
  patronInicio();

  //ESTO FUNCIONA ??
  //  colorSetup( 'R');
  //    PORTD = 0;
  //    delay(500);
  //    colorSetup( 'G');
  //    PORTD = 1;
  //    delay(500);
  //     PORTD = 0;
  //    delay(500);
  //     colorSetup( 'R');
  //  PORTD = 1;
  //    delay(500);

}

void loop() {

  //space at beginning of text
  //PORTD = 0;// aca apaga todo el PORTD

  //aca apago todo los leds para dejar espacio lo mismo que PORTD = 0 (esta en HIGH por que es catodo comun)
  //se podra poner todo el 1 con PORTD = 1
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  delay(refreshrate * 3);

  for (n = 0; n < dimtext; n++) { //go through each character of povtext and call function sendToWand to display letter

    //acá aplico el color, colores: WRGBYCM
    colorSetup(povtext_color.charAt(n));

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
      sendToWandMW(letterM);
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
      sendToWandMW(letterW);
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
    else if (povtext.charAt(n) == '0') {
      sendToWand(dibujo_0);
    }
    else if (povtext.charAt(n) == '1') {
      sendToWand(dibujo_1);
    }
    else if (povtext.charAt(n) == '2') {
      sendToWand(dibujo_2);
    }
    else if (povtext.charAt(n) == '3') {
      sendToWand(dibujo_3);
    }
    else if (povtext.charAt(n) == '4') {
      sendToWand(dibujo_4);
    }
    else if (povtext.charAt(n) == '5') {
      sendToWand(dibujo_5);
    }
    else if (povtext.charAt(n) == '6') {
      sendToWand(dibujo_6);
    }
    else if (povtext.charAt(n) == '7') {
      sendToWand(dibujo_7);
    }
    else if (povtext.charAt(n) == '8') {
      sendToWand(dibujo_8);
    }
    else if (povtext.charAt(n) == '9') {
      sendToWand(dibujo_9);
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

void apagarLEDs(int tiempo) {
  digitalWrite(0, HIGH);
  digitalWrite(1, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);

  delay(refreshrate * tiempo);
}