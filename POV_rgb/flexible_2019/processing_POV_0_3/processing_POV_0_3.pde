/*

 POV - Flavia Laudado _ Mayo 2019
 
 Dibujar en una cuadrícula
 y exportar los datos en un array 
 También guarda cada dibujo
 
 Para desarrollar dibujos respresentados
 con una varita POV
 
 //CONTROLES//
 click izq -> negro
 click der -> blanco
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

int col = 12;//19;
int filas = 20;
int anchoPixel, altoPixel;
float nH, nV;
color pixel;

PImage imgOut;

PrintWriter output;
int contador = 0;

void setup() {
  //fullScreen();
  size(601, 601);
  background(0);

  imgOut = createImage(width, height, ALPHA); 
  //inicializacion cuadricula
  anchoPixel = width/col;
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
  text("FLEXIBLE - POV para dibujar", xTexto - espaciado, yTexto - espaciado);
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
  if (guardado) {
    dibujar();
    cuadricula();
  }
}

void dibujar() { //dibuja en cada cuadrante correspondiente
  if (mousePressed == true) {
    if (mouseButton == LEFT) {
      fill(255);
    } else if (mouseButton == RIGHT) {
      fill(0);
    }
    nH = mouseX/anchoPixel;
    nV = mouseY/altoPixel;
    rect(nH * anchoPixel, nV * altoPixel, anchoPixel, altoPixel);
  }
}

void cuadricula() {
  stroke(127);
  for (int i = 0; i <= col; i++) {
    int xcol = anchoPixel * i;
    line(xcol, 0, xcol, height);
  }

  for (int i = 0; i <= filas; i++) {
    int yFilas = altoPixel * i;
    line(0, yFilas, width, yFilas);
  }
}

void keyPressed() {
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
          float col = red(c);
          if (col != 0) {
            col = 1;
          }
          int colInt = int(col);

          print(colInt + ", ");

          output.print(colInt + ", ");
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
