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
 barra limpia la pantalla
 text
 
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
int[][] arrayImage = new int[columnas][filas];
//int arrayImage[columnas][filas];

color colorRGB = color(255);
color _colorRGB = color(0);
PImage imgOut;
int contadorColor = 0;
int nColor = 1; //1-7
color color1;
int colorColumna[] = { 0, 0, 0, 0, 0, 0, 0};
int contadores[] = { 0, 0, 0, 0, 0, 0, 0};

PrintWriter output;
int contador = 0;

void setup() {
  //fullScreen();
  size(601, 601);
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
    nH = mouseX/anchoPixel;
    nV = mouseY/altoPixel;
    if (mouseButton == LEFT) {
      //fill(1);
      fill(colorRGB);
      arrayImage[int(nH)][int(nV)] = 1;
    } else if (mouseButton == RIGHT) {
      fill(0);
      arrayImage[int(nH)][int(nV)] = 0;
      rect(nH * anchoPixel, nV * altoPixel, anchoPixel, altoPixel);
    }
    colorear();
    //rect(nH * anchoPixel, nV * altoPixel, anchoPixel, altoPixel);
    //println(arrayImage[0][0]);
  }
}

color chooseColor(int codColor) {
  if (codColor == 0) {
    _colorRGB = color(255, 255, 255);
  } 
  if (codColor == 1) {
    _colorRGB = color(255, 0, 0);
  }
  if (codColor == 2) {
    _colorRGB = color(0, 255, 0);
  }
  if (codColor == 3) {
    _colorRGB = color(0, 0, 255);
  }
  if (codColor == 4) {
    _colorRGB = color(255, 255, 0);
  }
  if (codColor == 5) {
    _colorRGB = color(0, 255, 255);
  }
  if (codColor == 6) {
    _colorRGB = color(255, 0, 255);
  }
  return _colorRGB;
}
void colorear() {
  //si quiero colorear la columna 4 de rojo
  //if (colorColumna[0] == 2) {

  for (int i = 0; i < columnas; i++) {//colorear columna
    color1 = chooseColor(colorColumna[i]);
    for (int j = 0; j < filas; j++) {//recorro todas las filas de esa columna
      if (arrayImage[i][j] != 0) {//si hay pixel activo
        //pintar del color q indica el colorColumna
        //color1 = color(255, 0, 0);
        fill(color1);
        rect(i * anchoPixel, j * altoPixel, anchoPixel, altoPixel);
      }
    }
  }
}


/*
  for (int i = 0; i < columnas; i++) {
 for (int j = 0; j < filas; j++) {
 
 arrayImage[i][j] = 0;
 }
 }  */


void actualizarContador(int tecla) {
  contadores[tecla]++;
  if (contadores[tecla] > columnas) {
    contadores[tecla] = 0;
  }
  colorColumna[tecla] = contadores[tecla];
  print(", " + contadores[tecla]);
  colorear();
}

void keyPressed() {

  //ELEGIR EL COLOR
  if (key=='1') {//columna 1
    actualizarContador(0);
  }
  if (key=='2') {
    actualizarContador(1);
  }
  if (key=='3') {
    actualizarContador(2);
  }
  if (key=='4') {
    actualizarContador(3);
  }
  if (key=='5') {
    actualizarContador(4);
  }
  if (key=='6') {
    actualizarContador(5);
  }
  if (key=='7') {
    actualizarContador(6);
  }
  println();

  //GUARDADO DEL ARCHIVO
  if (key==ENTER) {
    if ( guardado == false) {
      enviarTexto();
    } else {
      imgOut = get();
      saveFrame(nombre + contador + ".jpg");
      int mitadAnchoPixel = anchoPixel/2;
      int mitadAltoPixel = altoPixel/2;

      println("Dibujo nro " + contador + ": ");
      output.println("const boolean dibujo_" + contador + "[] PROGMEM = {" );

      for (int j =mitadAltoPixel; j<imgOut.height; j += altoPixel) {
        for (int i = mitadAnchoPixel; i<imgOut.width; i += anchoPixel) {
          color c = imgOut.get(i, j);
          float colR = red(c);
          float colG = green(c);
          float colB = blue(c);
          char charColor = 'W';
          // colores: W RGB YCM
          if (colR == 255 && colG == 255 && colB == 255) {
            charColor = 'W';
          }
          if (colR == 255 && colG == 0 && colB == 0) {
            charColor = 'R';
          }
          if (colR == 0 && colG == 255 && colB == 0) {
            charColor = 'G';
          }
          if (colR == 0 && colG == 0 && colB == 255) {
            charColor = 'B';
          }
          if (colR == 255 && colG == 255 && colB == 0) {
            charColor = 'Y';
          }
          if (colR == 0 && colG == 255 && colB == 255) {
            charColor = 'C';
          }
          if (colR == 255 && colG == 0 && colB == 255) {
            charColor = 'M';
          }
          if (colR == 0 && colG == 0 && colB == 0) {
            charColor = 'B';
          }

          if (columnas != 0) {
            columnas = 1;
          }
          int colInt = int(columnas);

          print(charColor + ", ");

          output.print(charColor + ", ");
        }
        println(", ");

        output.println(" ");
      }

      output.println(" ");
      output.println("};");
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
  }
}
