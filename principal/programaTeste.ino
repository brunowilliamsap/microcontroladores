//motor de passo
#include <Stepper.h>
#define STEPS 48

#include <math.h>

Stepper stepper(STEPS, 10, 12, 11, 13);

//lcd
#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

//constantes pinos
int pinLedMotorPorta = 7;       //MOTOR PORTA
int pinLedMotorJanela = 6;       //MOTOR JANELA
int pinLedMotorCofre = 5;       //MOTOR COFRE
int pinLedArCond = 9;
int pinAnalogTemperatura;

//variaveis

float resistance;
float leituraTemp;

int b = 3975;                   //b value of the thermistor
int estado = 0;                 //ESTADO = 0 -> EM ESPERA, ESTADO = 1 -> PORTA , ESTADO = 2 -> JANELA, ESTADO = 3 -> COFRE
int abrirPorta = 1;
int fecharPorta = 0;
int abrirJanela = 1;
int fecharJanela = 0;
int abrirCofre = 1;
int fecharCofre = 0;
int segurancaCofre = 1;
int temperatura;



void setup() {
    // set up the LCD's number of columns and rows:
    lcd.begin(16, 2);

    //PINOS DE SAIDA
    pinMode(pinLedMotorPorta, OUTPUT);
    pinMode(pinLedMotorJanela, OUTPUT);
    pinMode(pinLedMotorCofre, OUTPUT);
    pinMode(pinLedArCond, OUTPUT);

    //Motor de passo 
    stepper.setSpeed(30);

    Serial.begin(9600);     
}

void loop() {
    //controle de temperatura
    pinAnalogTemperatura = analogRead(0);
    
    resistance=(float)(1023-pinAnalogTemperatura)*10000/pinAnalogTemperatura; //get the resistance of the sensor;
    leituraTemp=1/(log(resistance/10000)/b+1/298.15)-273.15;//convert to temperature via datasheet ;
    if(leituraTemp >= temperatura + 1)
      digitalWrite(pinLedArCond, HIGH);
    else
      if(leituraTemp <= temperatura - 1)
       digitalWrite(pinLedArCond, LOW);
    Serial.println(leituraTemp);
    lcd.clear();
    lcd.print(leituraTemp);
    delay(500);
     
    //controle de estado  
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

        //gerenciamento do motor
        if(abrirJanela == 1)
          stepper.step(48);
        if(fecharJanela == 1)
          stepper.step(-48);
        
        //gerencimento do display
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
