#include <Wire.h>
#include <OzOLED.h>
void setup(){
  OzOled.init();  //initialze Eduino OLED display
  OzOled.printString("Hello World!"); //Print the String
}
void loop(){
    OzOled.printString("Hello World!", 0, 0); //Print the String 
}
