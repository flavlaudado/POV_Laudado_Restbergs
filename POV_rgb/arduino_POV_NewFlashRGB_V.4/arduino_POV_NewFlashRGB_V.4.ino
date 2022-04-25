/*
  TAREA
  CHECK actualizar a letras chicas
  CHECK borrar todo lo que no sirva:
        -port B y C -> data1 y data3
        -Boton q cambia color
  CHECK-agregar numeros
  -que los dibujos se guarden en letras minusculas
  CHECK -agregar funcion para colorear por columna
  separar el programa de los datos en dos archivos
  agregar boolean para invertir colores
*/

#include <avr/pgmspace.h>//need to store letter arrays in flash memory- or else we run out of space, more info here: http://arduino.cc/en/Reference/PROGMEM

String povtext = "0 1 2 3 4 5 6 7 8 9";//PUT YOUR MESSAGE HERE!!- must be in all caps, spaces are fine, no punctuation
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

const boolean dibujo_0[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 1,
  1, 0, 1, 1, 1, 1, 1,
  1, 1, 0, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 1,
  1, 1, 1, 1, 1, 0, 1,
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1
};

String dibujo_0_color = { "MCRBGYW"};
//repensar si los colores los guardo en un String o en un array de char

//incoming data storage
byte data2 = 0;//for portD

//variables
byte n; //variable for loops
byte m; //variable for loops
byte t; //variable for loops
byte l; //variable for loops

int anchoLetra = 7;
int altoLetra = 8;

int delayInicio = 50;

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
    delay(refreshrate);
    //clear data storage
    data2 = 0;
  }
}

void sendDrawToWand(const boolean letterArray[]) { //function to get array data

  //una funcion para mandar los colores en String asociado

  for (t = 0; t < anchoLetra; t++) { //for each time step
    // l es la fila del array

    //coloreo segun su String asociado
    colorSetup(dibujo_0_color.charAt(t));

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
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  else if ( _n == 'R') {
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
  else if ( _n == 'G' ) {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }
  else if  ( _n == 'B' ) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
  else if ( _n == 'Y') {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  else if ( _n == 'C' ) {
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }
  else if  ( _n == 'M' ) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
  else if  ( _n == 'M' ) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
  else if  ( _n == ' ') {
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
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

void setup() {
/*
  TAREA
  CHECK actualizar a letras chicas
  CHECK borrar todo lo que no sirva:
        -port B y C -> data1 y data3
        -Boton q cambia color
  CHECK-agregar numeros
  -que los dibujos se guarden en letras minusculas
  CHECK -agregar funcion para colorear por columna
  separar el programa de los datos en dos archivos
  agregar boolean para invertir
*/

#include <avr/pgmspace.h>//need to store letter arrays in flash memory- or else we run out of space, more info here: http://arduino.cc/en/Reference/PROGMEM

String povtext = "0 1 2 3 4 5 6 7 8 9";//PUT YOUR MESSAGE HERE!!- must be in all caps, spaces are fine, no punctuation
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

const boolean dibujo_0[] PROGMEM = {
  0, 1, 1, 1, 1, 1, 1,
  1, 0, 1, 1, 1, 1, 1,
  1, 1, 0, 1, 1, 1, 1,
  1, 1, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 1,
  1, 1, 1, 1, 1, 0, 1,
  1, 1, 1, 1, 1, 1, 0,
  1, 1, 1, 1, 1, 1, 1
};

String dibujo_0_color = { "MCRBGYW"};
//repensar si los colores los guardo en un String o en un array de char

//incoming data storage
byte data2 = 0;//for portD

//variables
byte n; //variable for loops
byte m; //variable for loops
byte t; //variable for loops
byte l; //variable for loops

int anchoLetra = 7;
int altoLetra = 8;

int delayInicio = 50;

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
    delay(refreshrate);
    //clear data storage
    data2 = 0;
  }
}

void sendDrawToWand(const boolean letterArray[]) { //function to get array data

  //una funcion para mandar los colores en String asociado

  for (t = 0; t < anchoLetra; t++) { //for each time step
    // l es la fila del array

    //coloreo segun su String asociado
    colorSetup(dibujo_0_color.charAt(t));

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
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  else if ( _n == 'R') {
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
  else if ( _n == 'G' ) {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }
  else if  ( _n == 'B' ) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
  }
  else if ( _n == 'Y') {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  else if ( _n == 'C' ) {
    digitalWrite(9, HIGH);
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }
  else if  ( _n == 'M' ) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
  else if  ( _n == 'M' ) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
  else if  ( _n == ' ') {
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);
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
      sendDrawToWand(dibujo_0);
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
  PORTD = 0; //probar medio raro
  //PORTD = B11111111;
//  digitalWrite(0, HIGH);
//  digitalWrite(1, HIGH);
//  digitalWrite(2, HIGH);
//  digitalWrite(3, HIGH);
//  digitalWrite(4, HIGH);
//  digitalWrite(5, HIGH);
//  digitalWrite(6, HIGH);
//  digitalWrite(7, HIGH);

  delay(refreshrate * tiempo);
}
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
      sendDrawToWand(dibujo_0);
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
  PORTD = 0; //probar medio raro
  //PORTD = B11111111;
//  digitalWrite(0, HIGH);
//  digitalWrite(1, HIGH);
//  digitalWrite(2, HIGH);
//  digitalWrite(3, HIGH);
//  digitalWrite(4, HIGH);
//  digitalWrite(5, HIGH);
//  digitalWrite(6, HIGH);
//  digitalWrite(7, HIGH);

  delay(refreshrate * tiempo);
}
