
//motor de passo
#include <Stepper.h>
#define STEPS 48

Stepper stepper(STEPS, 10, 12, 11, 13);

//lcd
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

//constantes pinos
int pinLedMotorPorta = 7;       //MOTOR PORTA
int pinLedMotorJanela = 6;       //MOTOR JANELA
int pinLedMotorCofre = 5;       //MOTOR COFRE

//variaveis
int estado = 0;                 //ESTADO = 0 -> EM ESPERA, ESTADO = 1 -> PORTA , ESTADO = 2 -> JANELA, ESTADO = 3 -> COFRE



void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    //PINOS DE SAIDA
    pinMode(pinLedMotorPorta, OUTPUT);
    pinMode(pinLedMotorJanela, OUTPUT);
    pinMode(pinLedMotorCofre, OUTPUT);

    //Motor de passo 
    stepper.setSpeed(30);
}

void loop() {
    if(estado < 3)
      estado++;
    else
      estado = 0;
      
    switch (estado){
      case 1:
        digitalWrite( pinLedMotorPorta, HIGH);
        digitalWrite( pinLedMotorJanela, LOW);
        digitalWrite( pinLedMotorCofre, LOW);
        stepper.step(48);
        lcd.clear();
        lcd.print("porta");
        delay(500);
        break;  
      case 2:
        digitalWrite( pinLedMotorPorta, LOW);
        digitalWrite( pinLedMotorJanela, HIGH);
        digitalWrite( pinLedMotorCofre, LOW);
        stepper.step(-48);
        lcd.clear();
        lcd.print("janela");
        delay(500);
        break;
      case 3:
        digitalWrite( pinLedMotorPorta, LOW);
        digitalWrite( pinLedMotorJanela, LOW);
        digitalWrite( pinLedMotorCofre, HIGH);
        stepper.step(48);
        lcd.clear();
        lcd.print("cofre");
        delay(500);
        break;
      default:
        digitalWrite( pinLedMotorPorta, LOW);
        digitalWrite( pinLedMotorJanela, LOW);
        digitalWrite( pinLedMotorCofre, LOW);
        lcd.clear();
        lcd.print("em espera");
        delay(500);
        break;
    }
    
}


