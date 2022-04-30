
void setup_povRGB();
void loop_povRGB();

//patron de inicio
void patronInicio();

//colorear
void colorSetup(char _n); //colorTransis(), colorear()

//prender y paagar LEDs, mandandole datita
void sendToWand(const boolean letterArray[]);
void sendDrawToWand(const boolean letterArray[], String colorDibujo);
void apagarLEDs(int tiempo);
