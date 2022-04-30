/*
  TAREA
  CHECK actualizar a letras chicas
  CHECK borrar todo lo que no sirva:
        -port B y C -> data1 y data3
        -Boton q cambia color
  CHECK-agregar numeros
  CHECK-que los dibujos se guarden en letras minusculas
  CHECK -agregar funcion para colorear por columna
  separar el programa de los datos en dos archivos
  CHECK-agregar boolean para invertir
  CHECK-funcion para dibujar recibe el string
*/

#include <avr/pgmspace.h>//need to store letter arrays in flash memory- or else we run out of space, more info here: http://arduino.cc/en/Reference/PROGMEM

#include "povRGB.h"
#include "letrasydibus.cpp"


void setup() {

  setup_povRGB();
}

void loop() {

  loop_povRGB();
  colorSetup(charExample);

}
