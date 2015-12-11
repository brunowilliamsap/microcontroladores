#include<math.h>;

//lcd
#include <Wire.h>
#include "rgb_lcd.h"
rgb_lcd lcd;


//motor de passo
#include <Stepper.h>
#define STEPS 48
#define ITENS_CONTA_MAX 10
Stepper motor(STEPS, 10, 12, 11, 13);


//bluetooth
char estado;

//declarando pinos
int pinLedArCond = 9;
int pinLedPorta = 7;
int pinLedJanela = 6;
int pinLedLuz = 3;
int pinAnalogTemperatura;


//variaveis
float temperatura = 25;
int luzLigada;
int intensidade;
float resistance;
float leituraTemp;
int constTemperatura = 3975;

//controle da conta
String itensDescricao[10]={ "uno", "duo", "tri" };;
float itensPreco[10];
int itensConsumidos=0;
float total=0;

void setup(){

  //LCD
  lcd.begin(16, 2);
  
  //Motor de passo 
  motor.setSpeed(30);
  
  //portas analogicas
  Serial.begin(9600);

  //portas digitais
  pinMode(pinLedPorta, OUTPUT);
  pinMode(pinLedJanela, OUTPUT);
  
}
void loop() {

  
  //lcd
  String linha1 ="Hora:";
  int hora=2;
  linha1.concat(hora);
  linha1.concat("Conta:");
  linha1.concat(total);

  
  //controle de luz
  if(luzLigada == 0)
    intensidade = 0;
  analogWrite(pinLedLuz, intensidade); 

  //leitura do controle do ar condicionado
  pinAnalogTemperatura = analogRead(0);
  resistance=(float)(1023-pinAnalogTemperatura)*10000/pinAnalogTemperatura; //get the resistance of the sensor;
  leituraTemp=1/(log(resistance/10000)/constTemperatura+1/298.15)-273.15;//convert to temperature via datasheet ;

  //controle temperauta
  if(leituraTemp >= temperatura + 1)
    digitalWrite(pinLedArCond, HIGH);
  else
    if(leituraTemp <= temperatura - 1)
      digitalWrite(pinLedArCond, LOW);
  //lcd temperatura
  //Serial.println(leituraTemp);
  lcd.clear();
  lcd.print(leituraTemp);  
  
  
  
  if (Serial.available() > 0) {
    estado = Serial.read();
    switch (estado) {
      case 'a':                                 //abrir porta
        digitalWrite(pinLedPorta, HIGH);
        digitalWrite(pinLedJanela, LOW);
        
        //lcd porta
        lcd.clear();
        lcd.print("porta");
        
        motor.step(48);
        digitalWrite(pinLedPorta, LOW);
        break;
      
      case 'b':                                 //fechar porta
        digitalWrite(pinLedPorta, HIGH);
        digitalWrite(pinLedJanela, LOW);

        //lcd porta
        lcd.clear();
        lcd.print("porta");
        
        motor.step(-48);
        digitalWrite(pinLedPorta, LOW);
        break;
      
      case 'c':                                //abriando janela
        digitalWrite(pinLedPorta, LOW);
        digitalWrite(pinLedJanela, HIGH);

        //lcd janela
        lcd.clear();
        lcd.print("porta");
        
        motor.step(48);
        digitalWrite(pinLedJanela, LOW);
        break;

      case 'd':                                //fechando janela
        digitalWrite(pinLedPorta, LOW);
        digitalWrite(pinLedJanela, HIGH);

        //lcd janela
        lcd.clear();
        lcd.print("janela");
        
        motor.step(-48);
        digitalWrite(pinLedJanela, LOW);
        break;

      case 'e':                                //aumenta a temperatura
        
        //lcd temepratura
        lcd.clear();
        lcd.print(temperatura);
        delay(500);
        
        temperatura++;

        //lcd temperatura
        lcd.clear();
        lcd.print(temperatura);
        delay(500);
        break;

      case 'f':                                //diminui a temperatura
        //lcd temepratura
        lcd.clear();
        lcd.print(temperatura);
        delay(500);
        
        temperatura--;

        //lcd temperatura
        lcd.clear();
        lcd.print(temperatura);
        delay(500);
        break;

      case 'g':                                //liga a luz
        //lcd luz
        lcd.clear();
        lcd.print("ligar luz");
        
        luzLigada = 1;
        intensidade = 255;
        break;

      case 'h':                                 //desliga a luz
        //lcd luz
        lcd.clear();
        lcd.print("desligar luz");
        
        luzLigada = 0;
        break;

      case 'i':                                 //aumenta a intensidade da luz
        //lcd intensidade da luz
        lcd.clear();
        lcd.print(intensidade);
        delay(500);
        
        intensidade--;

        //lcd intensidade da luz
        lcd.clear();
        lcd.print(intensidade);
        delay(500);
        break;

      case 'j':                                //diminui a intensidade da luz
        //lcd intensidade da luz
        lcd.clear();
        lcd.print(intensidade);
        delay(500);
        
        intensidade--;

        //lcd intensidade da luz
        lcd.clear();
        lcd.print(intensidade);
        delay(500);
        break;
      
    }
  }
}


//led da luz não esta funcionando
//refazer o app
//instalar o sensor de presneça
//ar condicionado não esta funcionando mas acredito que seja pela falta do sensor
