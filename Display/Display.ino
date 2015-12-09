
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 3);
    // Print a message to the LCD.
   
}

void loop() {
    // Turn off the display:
    lcd.print("texto1");
    delay(500);
    lcd.clear();
    lcd.print("texto2");
    // Turn on the display:
    lcd.display();
    delay(500);
    lcd.clear();
}


