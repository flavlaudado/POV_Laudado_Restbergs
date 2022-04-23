/*

 POV - Flavia Laudado _ Mayo 2019
 
 Dibujar en una cuadrícula
 y exportar los datos en un array 
 También guarda cada dibujo
 
 Para desarrollar dibujos respresentados
 con una varita POV
 
 //CONTROLES//
 click izq -> color
 click der -> negro
 1-7 -> colorear columnas
 enter -> guardar img y array de datos
 barra -> limpia la pantalla
 text
 
 TAREA
 CHECK-diferenciar dibus B&W de color, 1-0, WRGBCMYB
 CHECK-después de apretar enter no deja seguir dibujando,
 CHECK-solo dibuja en la primer columna y no deja colorear
 CHECK-cuando guarda en colores q mantenga los bits (0, 1)
 CHECK-colores: String, no un array de char, ej: "MCRBGYW"
 -que no te deje colorear la columna si no hay bit activo 
 -que cuando inicia no te deje dibujar tan de toque
 -al guardar la imagen que haga un flash
 -cambiar el negro a "k"
 -sacar la última coma del array de datos
 CHECK-dibujar numeros 0-9
 -si no hubo cambios  que no deje guardar
 -a la intro agregar una musiquita y unos gifs
 
 
 error: colorea bits inactivos, aunque no se vea
 
 */

import controlP5.*;
ControlP5 cp5;

float xTexto = 100;
float yTexto = 100;
float espaciado = 40;
String consigna = "Nombre:";
boolean guardado = false;
String nombre, nombreArchivo;

int columnas = 7;//19;
int filas = 8;
int anchoPixel, altoPixel;
float nH, nV;
color pixel;
int[][] arrayBits = new int[columnas][filas];
//int arrayBits[columnas][filas];

color colorRGB = color(255);
//color _colorRGB = color(0);
boolean dibujoColor = false;
PImage imgOut;
int contadorColor = 0;
int nColors = 8; //1-7
color color1;
int colorColumna[] = { 1, 1, 1, 1, 1, 1, 1};
int acumuladorColorColumna = 0;

PrintWriter output;
int contador = 0;
int framerate = 0;

void setup() {
  //fullScreen();
  size(700, 800);
  background(0);

  imgOut = createImage(width, height, ALPHA); 
  //inicializacion cuadricula
  anchoPixel = width/columnas;
  altoPixel = height/filas;

  cp5 = new ControlP5(this);

  PFont font = createFont("calibri", 20);

  cp5.addTextfield("input")
    .setPosition(xTexto, yTexto + espaciado)
    .setSize(200, 40)
    .setFont(font)
    .setFocus(true)
    .setColor(color(255))
    .setAutoClear(false)
    .setLabel(" ")
    ;

  cp5.addBang("Guardar")
    .setPosition( xTexto, yTexto + espaciado * 3)
    .setSize(50, 40)
    .getCaptionLabel().align(ControlP5.CENTER, ControlP5.CENTER)
    ;

  textFont(font);

  fill(255);
  text("POV RGB para dibujar", xTexto - espaciado, yTexto - espaciado);
  text(consigna, xTexto, yTexto);
}

public void controlEvent(ControlEvent theEvent) {
  if (theEvent.getController().getName().equals("Guardar")) {
    enviarTexto();
  } 
}

void enviarTexto() {
  nombre = cp5.get(Textfield.class, "input").getText();
  cp5.get(Textfield.class, "input").clear();
  nombreArchivo = nombre + ".txt";
  output = createWriter(nombreArchivo);
  guardado = true;
  cp5.remove("input");
  cp5.remove("Guardar");
  background(0);
}

void draw() {
  framerate++;
  //guardado = true;
  if (guardado) {
    dibujar();
    cuadricula();
  }
}

void cuadricula() {
  stroke(127);
  for (int i = 0; i <= columnas; i++) {
    int xcol = anchoPixel * i;
    line(xcol, 0, xcol, height);
  }

  for (int i = 0; i <= filas; i++) {
    int yFilas = altoPixel * i;
    line(0, yFilas, width, yFilas);
  }
}

void dibujar() { //dibuja en cada cuadrante que se hace click
  if (mousePressed == true) {
    nH = constrain(mouseX/anchoPixel, 0, columnas - 1);
    nV = constrain(mouseY/altoPixel, 0, filas - 1);
    if (mouseButton == LEFT) { 
      fill(1);
      arrayBits[int(nH)][int(nV)] = 1;
    } else if (mouseButton == RIGHT) {
      fill(0);
      arrayBits[int(nH)][int(nV)] = 0;
      rect(nH * anchoPixel, nV * altoPixel, anchoPixel, altoPixel);
    }
    colorear();
  }
}

void colorear() {
  dibujoColor = true;
  for (int i = 0; i < columnas; i++) {
    color1 = chooseColor(colorColumna[i]);//tomo el color de la columna
    for (int j = 0; j < filas; j++) {//recorro todas las filas de esa columna
      if (arrayBits[i][j] != 0) {//si hay pixel activo
        fill(color1);//pinto de ese color
        rect(i * anchoPixel, j * altoPixel, anchoPixel, altoPixel);
      }
    }
  }
}

color chooseColor(int codColor) {
  color _color1 = color(255);
  if (codColor == 0) {
    _color1 = color(0, 0, 0);
  } 
  if (codColor == 1) {
    _color1 = color(255, 255, 255);
  } 
  if (codColor == 2) {
    _color1 = color(255, 0, 0);
  }
  if (codColor == 3) {
    _color1 = color(0, 255, 0);
  }
  if (codColor == 4) {
    _color1 = color(0, 0, 255);
  }
  if (codColor == 5) {
    _color1 = color(0, 255, 255);
  }
  if (codColor == 6) {
    _color1 = color(255, 0, 255);
  }
  if (codColor == 7) {
    _color1 = color(255, 255, 0);
  }
  return _color1;
}

void actualizarColorColumna(int tecla) {
  colorColumna[tecla]++;
  if (colorColumna[tecla] >= nColors) {
    colorColumna[tecla] = 1;
  }
  //print(", " + colorColumna[tecla]);
  colorear();
}


void keyPressed() {
  //ELEGIR EL COLOR
  if (key=='1') {//columna 1
    actualizarColorColumna(0);
  }
  if (key=='2') {
    actualizarColorColumna(1);
  }
  if (key=='3') {
    actualizarColorColumna(2);
  }
  if (key=='4') {
    actualizarColorColumna(3);
  }
  if (key=='5') {
    actualizarColorColumna(4);
  }
  if (key=='6') {
    actualizarColorColumna(5);
  }
  if (key=='7') {
    actualizarColorColumna(6);
  }

  if (key=='p') { //PARA PRUEBAS
    print("colors: ");
    for (int n = 0; n < columnas; n++) {
      print("color: " + colorColumna[n] + ", ");
    }
    println("");
  }

  //GUARDADO DEL ARCHIVO
  if (key == ENTER) {
    if ( guardado == false) {
      enviarTexto();
    } else {
      imgOut = get();
      saveFrame(nombre + contador + ".jpg");
      int mitadAnchoPixel = anchoPixel/2;
      int mitadAltoPixel = altoPixel/2;

      //chequeo si el dibujo está en color o blanco y negro
      //esto no funciona !!
      for (int n = 0; n < columnas; n++) {
        acumuladorColorColumna += colorColumna[n];
        if (acumuladorColorColumna == 0) {
          dibujoColor = false;
        } else {
          dibujoColor = true;
        }
        fill(255);
        rect(0,0,width, height);
        colorear();
      }

      //println("Dibujo nro " + contador + ": ");
      //output.println("const boolean dibujo_" + contador + "[] PROGMEM = {" );
      char charNombre = 0;
      charNombre = char(contador + 97);
      println("Dibujo nro " + charNombre + ": ");
      output.println("const boolean dibujo_" + charNombre + "[] PROGMEM = {" );

      for (int j =mitadAltoPixel; j<imgOut.height; j += altoPixel) {
        for (int i = mitadAnchoPixel; i<imgOut.width; i += anchoPixel) {
          color c = imgOut.get(i, j);
          float colR = red(c);
          float colG = green(c);
          float colB = blue(c);

          char charBit = '0';

          if (colR == 0 && colG == 0 && colB == 0) {
            charBit = '0';
          } else {
            charBit = '1';
          }

          print(charBit+ ", ");
          output.print(charBit+ ", ");
        }
        println(", ");

        output.println(" ");
      }

      //output.println(" ");
      output.println("};");
      output.println(" ");
      
      print("colors: ");
      output.print("String povtext_color = { \"" ); //cambiar este nombre
      for (int n = 0; n < columnas; n++) {
        char charColor = ' ';
        if (colorColumna[n] == 0) {
          charColor = 'K';
        }
        if (colorColumna[n] == 1) {
          charColor = 'W';
        }
        if (colorColumna[n] == 2) {
          charColor = 'R';
        }
        if (colorColumna[n] == 3) {
          charColor = 'G';
        }
        if (colorColumna[n] == 4) {
          charColor = 'B';
        }
        if (colorColumna[n] == 5) {
          charColor = 'C';
        }
        if (colorColumna[n] == 6) {
          charColor = 'M';
        }
        if (colorColumna[n] == 7) {
          charColor = 'Y';
        }
        output.print(charColor);
        print( charColor);
        /*
        if (n != columnas - 1) {
          output.print(", ");
          print( ", ");
        } */
      }
      output.print("\" };");
      output.println(" ");
 
      output.flush(); 
      //output.close();

      println(" ");
      contador++;
    }
  }

  if (key==' ') {
    fill(0);
    rect(0, 0, width, height);
    for (int i = 0; i < columnas; i++) {
      colorColumna[i] = 1;
      for (int j = 0; j < filas; j++) {
        arrayBits[i][j] = 0;
      }
    }
  }
}
